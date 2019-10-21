import threading
from threading import Thread 
import time


def threadCode(cnt=0):
	while True:
		cnt=cnt+1
		time.sleep(1)
		print("in threadCode id="+str(threading.get_ident())+" cnt="+str(cnt))
		if cnt >= 5:
			print("threadCode break")
			break

t=Thread(target=threadCode)
t1=Thread(target=threadCode)
t.setDaemon(True)
t1.setDaemon(True)
t.start()
t1.start()
#t.join()
while True:
	time.sleep(1)
	print("in main id="+str(threading.get_ident()))
