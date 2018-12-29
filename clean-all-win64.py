import os, subprocess, shutil, sys, threading
from queue import Queue
from threading import Thread

from datetime import datetime
starttime = datetime.now()

class RemovePath(Thread):
	def __init__(self, queue):
		Thread.__init__(self)
		self.queue = queue
		
	def run(self):
		while True:
			link = self.queue.get()
			try:
				rmdir(link)
			finally:
				self.queue.task_done()


def rmdir(path):
	if(os.path.exists(path)):
		thread_print("Removing " + path)
		shutil.rmtree(path)

def clean_all(dir_list):
	# Create a queue to communicate with the worker threads
	queue = Queue()
    # Create 8 worker threads
	for x in range(8):
		worker = RemovePath(queue)
        # Setting daemon to True will let the main thread exit even though the workers are blocking
		worker.daemon = True
		worker.start()
    # Put the tasks into the queue as a tuple
	for link in dir_list:
		queue.put(os.path.join(os.path.abspath(link), "bin"))
		queue.put(os.path.join(os.path.abspath(link), "lib"))
		queue.put(os.path.join(os.path.abspath(link), "build"))
		queue.put(os.path.join(os.path.abspath(link), "tmp"))
    # Causes the main thread to wait for the queue to finish processing all the tasks
	queue.join()

def thread_print(data):
	print("[" + td_format(datetime.now() - starttime) + " " + str(threading.get_ident()).rjust(6) + "] " + data)

def td_format(delta):
	hours, remainder = divmod(delta.total_seconds(), 3600)
	minutes, seconds = divmod(remainder, 60) 
	return '{:02}:{:02}:{:04}'.format(int(minutes + hours * 60), int(seconds), int(remainder * 1000))

def main():
	dir_list = ['slyd3d11','slyd3d12','slygl4', 'slyengine', 'slywin32', 'slyedit']
		
	thread_print("Starting Clean All...")
	clean_all(dir_list)
	thread_print("Clean All Completed!")
	print("")
	
if __name__ == '__main__':
    main()
