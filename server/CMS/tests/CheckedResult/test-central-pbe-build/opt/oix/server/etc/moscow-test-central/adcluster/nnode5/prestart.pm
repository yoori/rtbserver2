

%CONFIG = ( %CONFIG,
  log_file => "/opt/foros/server/var/log/PreStart/PreStart.log",
);

  

%CHECK_CORBA_REFS = ( %CHECK_CORBA_REFS,
  CampaignManager => {
    ref => "corbaloc:iiop:localhost:10107/ProcessControl",
    status => "ready",
    required => 1},
  ChannelCluster => {
    ref => "corbaloc:iiop:nnode5:10104/ChannelClusterControl",
    status => "ready",
    required => 1},
  UserInfoCluster => {
    ref => "corbaloc:iiop:nnode4:10102/UserInfoClusterControl",
    status => "ready",
    required => 0},
);
  
