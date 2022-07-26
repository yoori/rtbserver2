
import time, string, types, os, random, hashlib

def userError( msg ):
  raise UserError(msg)

# obsoleted by kutil.time.get
def currentTime():
  sec = time.time()
  mcs = int(sec * 1000000 % 1000000)
  return (int(sec), mcs)


# count of days for given month
_dayOfs = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]

# convert UTC time struct (year, mon, day, hour, min, sec) to unix seconds
def mkgmtime( tm ):
  year = tm[0] - 1970
  mon  = tm[1] - 1
  day  = tm[2] - 1
  hour, min, sec = tm[3:6]
  day += year * 365
  day += (year + 1)/4        # leap are every fourth
  day += _dayOfs[mon]
  if mon > 1 and (year + 2) % 4 == 0:
    day += 1  # leap year
  return ((day * 24 + hour) * 60 + min) * 60 + sec


def getDayOfMonth(days,ofset):
  assert days <= 366, "days: %d, year: %d" % (days,year)
  daysMonth = _dayOfs + [365]
  for i in range(1,len(daysMonth)):
    if i > 1: ofs = ofset
    else: ofs = 0
    if days < daysMonth[i]+ofs:
      if i == 2: ofs = 0
      return (i,days-daysMonth[i-1]-ofs+1)

#sec -> gmtime struct 
def pygmtime(sec):
  days = int(sec / (24 * 60 * 60)) # Days from 01 Jan 1970
  dayOfWeek = (days+3) % 7 #days+3 because 01 Jan 1970 is Wednesday 
  sec  = sec % (24 * 60 * 60)
  year = 1970
  while True:
    if year % 4 == 0: ofs = 1
    else: ofs = 0
    if days >= 365+ofs:
        days-=365+ofs
        year+=1
    else:
      mon, day = getDayOfMonth(days,ofs)
      break
  hour = int(sec / (60 * 60))
  min  = int((sec % (60 * 60)) / 60)
  sec  = int((sec % 60))
  return year, mon, day, hour, min, sec, dayOfWeek , days+1, 0

      
def time2float( time ):
  if time is None: return None
  sec, mcs = time
  return float(sec + mcs / 1000000)

def secs2str( sec ):
  if sec == 0: return '0'
  return time.strftime('%Y-%m-%d %H:%M:%S', pygmtime(sec))

def secs2localStr( sec ):
  if sec == 0: return '0'
  return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(sec))

def time2str( t ):
  if t is None: return '0'
  sec, mcs = t
  assert (sec <> 0 or mcs <> 0), 'unknown time must be represented as None'
  return '%s.%06u' % (secs2str(sec), mcs)

def time2localStr( t ):
  if t is None: return '0'
  sec, mcs = t
  assert (sec <> 0 or mcs <> 0), 'unknown time must be represented as None'
  return '%s.%06u' % (secs2localStr(sec), mcs)

def timeInt2str( (from_, to_) ):
  return '[%s|%s]' % (time2str(from_), time2str(to_))

def str2time( str ):
  if str == '' or str == '0': return None
  l = string.split(str, '.')
  if len(l) != 2: raise Exception('Invalid time: "%s"' % str)
  try:
    mcsec = int(l[1])
    r = time.strptime(l[0], '%Y-%m-%d %H:%M:%S')
    sec = mkgmtime(r)
  except Exception, x:
    raise Exception('Invalid time: "%s" (%s)' % (str, x))
  return (sec, mcsec)


def addr2str( (host, port) ):
  return '%s:%d' % (host or '*', port)

def str2addr( str ):
  l = string.split(str, ':')
  if len(l) != 2: raise Exception('Invalid address "%s", it must have form <host:port>' % str)
  host = l[0]
  if host == '*': host = ''
  try:
    port = int(l[1])
  except ValueError:
    raise Exception('Invalid address "%s", it must have form <host:port>' % str)
  return (host, port)


# split string by spaces with respect to single and double quotes
def qsplit( str ):
  s = string.rstrip(str)
  list = []
  while True:
    s = string.lstrip(s)
    if len(s) > 0 and s[0] == '"':
      p = string.find(s, '"', 1)
      if p == -1: raise Exception('Unclosed double quote in "%s"' % str)
      list.append(s[1:p])
      s = s[p + 1:]
    elif len(s) > 0 and s[0] == "'":
      p = string.find(s, "'", 1)
      if p == -1: raise Exception('Unclosed quote in "%s"' % str)
      list.append(s[1:p])
      s = s[p + 1:]
    else:
      p = string.find(s, ' ')
      if p == -1:
        if s: list.append(s)
        return list
      list.append(s[0:p])
      s = s[p + 1:]


def bool2str( val, falseStr = 'false', trueStr = 'true' ):
  if val: return trueStr
  else: return falseStr


def withIndex( list ):
  result = []
  for i in range(len(list)):
    result.append((i, list[i]))
  return result

def withLastTag( list ):
  result = []
  for i in range(len(list)):
    lastTag = i == len(list) - 1
    result.append((lastTag, list[i]))
  return result

def withFirstTag( list ):
  result = []
  for i in range(len(list)):
    firstTag = i == 0
    result.append((firstTag, list[i]))
  return result

def withFirstLastTag( list ):
  result = []
  for i in range(len(list)):
    firstTag = i == 0
    lastTag  = i == len(list) - 1
    result.append((firstTag, lastTag, list[i]))
  return result


def struct2str( r, maxLen = None, deep = False ):
  s = _struct2str(r, deep)
  if maxLen and len(s) > maxLen: s = '%s...' % s[:maxLen - 3]
  return s

def _struct2str( r, deep = False ):
  def toStr( r ):
    return _struct2str(r, deep)
  def namedVal( (name, v) ):
    return '%s=%s' % (name, _struct2str(v, deep))
  def dictVal( (name, v) ):
    return '%s: %s' % (name, _struct2str(v, deep))
  if deep:
    #following causes infinite loop sometimes
    if type(r) is types.InstanceType:
      cls = r.__class__.__name__
      return '%s(%s)' % (cls, string.join(map(namedVal, r.__dict__.items()), ', '))
  if type(r) is types.DictType:
    return '{%s}' % string.join(map(dictVal, r.items()), ', ')
  elif type(r) is types.ListType:
    return '[%s]' % string.join(map(toStr, r), ', ')
  elif type(r) is types.TupleType:
    return '(%s)' % string.join(map(toStr, r), ', ')
  else:
    return str(r)


def methodNotImplemented( obj = None ):
  raise Exception('(%s) Abstract method call: method is not implemented' % obj)

def assertList( val ):
  assert type(val) == type([]), str(val)

def assertListOrNone( val ):
  if val is None: return
  assert type(val) == type([]), str(val)

# assert all list member are instances of 'cls'
def assertListInst( l, cls ):
  assert type(l) is list
  for val in l:
    assert isinstance(val, cls), val

assertIsListInstance = assertListInst

# assert v is time value; tuple (sec, mcs)
def assertIsTime( v ):
  msg = '%s is not a time' % str(v)
  assert type(v) is tuple, msg
  assert len(v) == 2, msg
  assert type(v[0]) in [int, long], msg
  assert type(v[1]) in [int, long], msg

def assertIsTimeOrNone( v ):
  if v is None: return
  assertIsTime(v)

def assertIsString( v ):
  assert type(v) is str

def assertIsStringOrNone( v ):
  if v is None: return
  assertIsString(v)

def assertIsInt( v ):
  assert type(v) is int, '"%s"/%s' % (str(v), type(v))

def assertIsIntOrNone( v ):
  if v is None: return
  assertIsInt(v)

def assertIsBool( v ):
  assert v in [False, True]

def assertIsBoolOrNone( v ):
  if v is None: return
  assertIsBool(v)

def assertIsAddr( v ):
  assert type(v) is tuple
  assert len(v) == 2
  assertIsString(v[0])
  assertIsInt(v[1])


# rm -rf path
def removeDirTree( path ):
  for name in os.listdir(path):
    p = os.path.join(path, name)
    if os.path.isdir(p):
      removeDirTree(p)
    else:
      os.remove(p)
  os.rmdir(path)


# make absolute path1 relative to path2
def relativePath(path1, path2):
  if not path1[0] == '/': return path1
  dirs1 = path1.split('/')
  dirs2 = path2.split('/')
  unEqualIndex = 0
  for i in range(len(dirs2)):
    if dirs1[i] != dirs2[i]:
      unEqualIndex = i
      break
  def parent_path(x): return ".."
  result = map(parent_path, dirs2[unEqualIndex:])
  result += dirs1[unEqualIndex:]
  return string.join(result, '/')
  

# sort a list in functional style
def sort( list ):
  list = list[:]  # make a copy
  list.sort()
  return list

# same as d.items() but in sorted keys order
def sortedItems( d ):
  def cvt( key ):
    return (key, d[key])
  return map(cvt, sort(d.keys()))


def withMutex( mutex, fn, *args, **kw ):
  mutex.acquire()
  try:
    return fn(*args, **kw)
  finally:
    mutex.release()

# method decorator
def abstract( method ):
  def f( self, *args, **kw ):
    raise Exception('Abstract method call; method "%s.%s" is not implemented' %
                    (self.__class__, method.__name__))
  return f

# generate guid
def guid( *args ):
    """
    Generates a universally unique ID.
    Any arguments only create more randomness.
    """
    t = long( time.time() * 1000 )
    r = long( random.random()*100000000000000000L )
    try:
        a = socket.gethostbyname( socket.gethostname() )
    except:
        # if we can't get a network address, just imagine one
        a = random.random()*100000000000000000L
    data = str(t)+' '+str(r)+' '+str(a)+' '+str(args)
    return hashlib.md5(data).hexdigest()


