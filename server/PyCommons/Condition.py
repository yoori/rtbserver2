
from Shutdown import shutdown
from Logger import log
from Util import *
import threading, time


class Condition:

  def __init__( self, lock = None ):
    self.cond = threading.Condition(lock)
    self.hadNotify = False  # I hope it will be protected by our own mutex (lock)

  def acquire( self ):
    self.cond.acquire()

  def release( self ):
    self.cond.release()


  def notifyAll( self ):
    self.cond.notifyAll()
    self.hadNotify = True

  # timeout is in seconds
  def wait( self, timeOut = None ):
    assert timeOut != 0, 'zero timeouts are not supported'
    shutdown.regCondition(self.cond)
    try:
      self.hadNotify = False
      shutdown.check()
      self.cond.wait(timeOut)
      shutdown.check()
      # unfortunately, we have no other way to check if condition.wait quitted on timeOut or not
      return timeOut is None or self.hadNotify
    finally:
      shutdown.unregCondition(self.cond)
