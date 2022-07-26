#!/usr/bin/perl

# $Id: TReport.pl 182371 2017-03-29 07:45:40Z jurij_kuznecov $

use strict;
use warnings;
use File::Find;
use File::Path;
use File::Copy;
use Fcntl ':mode';

my $from_place;#used by callback of File::Find
my $to_place;

sub write_date($$) {
  my ($workdir, $append) = @_;

  my $date_name = 'date.txt';
  my $date_cmd  = 'date -u';
  my $mode      = $append ? '>>' : '>';

  open(FH, "$mode$workdir/$date_name") or
    die "Can't open file '$workdir/$date_name': $!";
  print FH `$date_cmd`;
  close(FH);
}

#callback of File::Find
sub wanted {
  if("$_" ne ".") {
    if (my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks) = lstat($File::Find::name)) {
      my $filetype = S_IFMT($mode);
      if($filetype == S_IFREG and (time - $mtime) < 172800) {
        (my $to = $File::Find::dir) =~ s/^$from_place/$to_place/;
        mkpath($to);
        copy($File::Find::name, $to);
      }
    }
  }
}

sub generate_basic_reports($$$) {
  my ($workdir, $config_root, $forosmgr_file_mask) = @_;
  print "Generating basic reports...\n";

  my $rpm_name      = 'rpm.txt';
  my $top_name      = 'top.txt';
  my $ps_name       = 'ps.txt';
  my $pstree_name   = 'pstree.txt';
  my $netstat_name  = 'netstat.txt';
  my $lsof_name     = 'lsof.txt';
  my $df_name       = 'df.txt';
  my $ifconfig_name = 'ifconfig.txt';

  my $rpm_cmd      = 'rpm -qa|grep foros';
  my $top_cmd      = 'top -b -n 1';
  my $ps_cmd       = 'ps aux';
  my $pstree_cmd   = 'pstree -p';
  my $netstat_cmd  = 'netstat -tn';
  my $lsof_cmd     = '/usr/sbin/lsof';
  my $df_cmd       = 'df -h';
  my $ifconfig_cmd = '/sbin/ifconfig -a';

  my %reports = ($rpm_name, $rpm_cmd, $top_name, $top_cmd, $ps_name, $ps_cmd,
                 $pstree_name, $pstree_cmd, $netstat_name, $netstat_cmd,
                 $lsof_name, $lsof_cmd, $df_name, $df_cmd,
                 $ifconfig_name, $ifconfig_cmd);

  foreach my $name (keys %reports) {
    open(FH, ">$workdir/$name") or die "Can't open file '$workdir/$name': $!";
    print FH `$reports{$name}`;
    close(FH);
  }
}

sub copy_logs($$) {
  my ($workdir, $logpath) = @_;
  print "Copying AdServer log files...\n";
  $from_place = $logpath;
  $to_place = "$workdir"."/log";
  find(\&wanted, ($from_place));
}

sub copy_out_files($$) {
  my ($workdir, $outpath) = @_;
  print "Copying AdServer stdout files...\n";
  system("mkdir $workdir/out && cp $outpath/*.out $workdir/out");
}

sub extract_app_name_from_core($) {
  my $core = shift @_;
  my $core_app_name;
  my $shcmd = "gdb -q -n -c $core </dev/null 2>&0";

  open(SH, "bash -c '$shcmd'|") or die "Can't start bash: $!";
  while (<SH>) {
    /^Core was generated by \`([^ ]+).*/ or next;
    $core_app_name = $1;
    last;
  }
  close(SH);
  return $core_app_name;
}

sub process_core_dumps($$$) {
  my ($workdir, $coredir, $bindir) = @_;
  my @cores = glob "$coredir/core*";

  print "Processing core dumps...\n";

  foreach my $core (@cores) {
    my $core_info = `file $core`;

    $core =~ /.*\/(core\.[0-9]+)$/ or next;
    my $core_name = $1;
    $core_info =~ /.*core file.*from \'.+\'$/ or next;
    my $core_app = extract_app_name_from_core($core);
    print "Found core dump: '$core_name', Application: '$core_app'\n";

    my $bin_path = "$bindir/$core_app";
    chomp($bin_path = `which $core_app`) unless -e $bin_path;
    $bin_path = "/usr/sbin/$core_app" unless -e $bin_path;

    my $gdboutdir = "$workdir/$core_name";
    mkdir $gdboutdir or die "Can't create directory '$gdboutdir': $!";

    if (-e $bin_path) {
      my $shcmd = "gdb -q -n $bin_path $core <<EOF 2>&1\n" .
                  "thread apply all bt\n" .
                  "thread apply all bt full\n" .
                  "EOF";

      open(SH, "bash -c '$shcmd'|") or die "Can't start bash: $!";
      open(FH, ">$gdboutdir/gdb.txt") or
        die "Can't open '$gdboutdir/gdb.txt': $!";
      while (<SH>) {
        print FH;
      }
      close(FH);
      close(SH);
    } else {
      print STDERR "Core dump '$core_name': Can't run GDB: " .
                   "Unable to locate the binary for '$core_app'!\n";
    }

    open(FH, ">$gdboutdir/file.txt") or
      die "Can't open file '$gdboutdir/file.txt': $!";
    print FH $core_info;
    close(FH);

    open(FH, ">$gdboutdir/ls.txt") or
      die "Can't open file '$gdboutdir/ls.txt': $!";
    print FH `ls -l $core`;
    close(FH);
  }
}

sub clean_up($) {
  my ($tmpdir) = @_;
  system("rm -rf $tmpdir");
}

use POSIX qw/strftime/;
use Getopt::Std;

use constant OUT_BASE_NAME => 'tr_report';

sub main() {
  my $script = (split /\//, $0)[-1];
  my $usage = "Usage: $script [OPTIONS]\n\n" .
              "Options are:\n" .
              "-w <PATH>\tSet workspace root to <PATH>\n" .
              "-c <PATH>\tSet configuration root to <PATH>\n" .
              "-b <PATH>\tSet binaries root to <PATH>\n" .
              "-m <FILE-MASK>\tSet config file mask for OIXMGR" .
              " (DEFAULT='adserver')\n" .
              "-o <FILENAME>\tSave output to <FILENAME>\n" .
              "-h\t\tPrint this information\n";

  print $usage and return 0 unless $#ARGV > 0;

  my $date = strftime("%F_%H-%M-%S", gmtime);
  chomp(my $hostname = `hostname`);

  my $workspace_root = "/opt/foros/server/var";
  my $config_root = "/opt/foros/server/etc";
  my $bin_root = undef;
  my $forosmgr_file_mask = "adserver";
  my $outfile = OUT_BASE_NAME . "_$hostname\_$date.tar.gz";

  my %opts;
  getopt("wcbmoh", \%opts);
  foreach (keys %opts) {
    if ($_ eq "w") {
      $workspace_root = $opts{$_};
    } elsif ($_ eq "c") {
      $config_root = $opts{$_};
    } elsif ($_ eq "b") {
      $bin_root = $opts{$_};
    } elsif ($_ eq "m") {
      $forosmgr_file_mask = $opts{$_};
    } elsif ($_ eq "o") {
      $outfile = $opts{$_};
    } elsif ($_ eq "h") {
      print $usage and return 0;
    } else {
      die "$script: Unknown option '$_'!\n";
    }
  }

  my $tmpdir = "$workspace_root/.#" . OUT_BASE_NAME . "#$$." . int(rand(1000));
  my $workdir = "$tmpdir/$hostname\_$date";

  $SIG{__DIE__} = sub { clean_up($tmpdir); die shift @_; };

  mkdir $tmpdir or die "Can't create temporary directory '$tmpdir': $!\n";
  mkdir $workdir or die "Can't create directory '$workdir': $!\n";

  my $stderrfile = "$workdir/stderr.txt";
  open(STDERR, '>', $stderrfile) or
    die "Can't redirect STDERR to '$stderrfile': $!";

  write_date($workdir, 0);
  generate_basic_reports($workdir, $config_root, $forosmgr_file_mask);
  copy_logs($workdir, "$workspace_root/log");
  copy_out_files($workdir, "$workspace_root/run");
  process_core_dumps($workdir, "$workspace_root/run", $bin_root) if
    defined($bin_root);
  write_date($workdir, 1);

  close(STDERR);

  system("tar -czf $outfile -C $tmpdir ./");
  clean_up($tmpdir);
}

main;

