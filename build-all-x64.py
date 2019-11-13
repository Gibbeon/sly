import os, subprocess, shutil, sys, threading, platform
from queue import Queue
from threading import Thread
from datetime import datetime
starttime = datetime.now()

errors = dict()

files = os.listdir(os.getcwd())
for file in files:
    if file.endswith(".tlog"):
        os.remove(os.path.join(os.getcwd(),file))

PLATFORM = platform.system()
USE_MSVC = PLATFORM == "Windows"
USE_MAKE = not USE_MSVC

if(USE_MSVC):
	INIT_ENV_BAT = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64.bat"
	vars = subprocess.check_output([INIT_ENV_BAT, '&&', 'set'])
	for var in vars.splitlines():
		var = var.decode('cp1252')
		k, _, v = map(str.strip, var.strip().partition('='))
		if k.startswith('?'):
			continue
		os.environ[k] = v

class CMakeWorker(Thread):
	def __init__(self, queue):
		Thread.__init__(self)
		self.queue = queue
		
	def run(self):
		while True:
			link = self.queue.get()
			try:
				if "sly" in link:
					cmake(link)
				else:
					print(link + " is not valid")
			finally:
				self.queue.task_done()

class BuildWorker(Thread):
	def __init__(self, queue):
		Thread.__init__(self)
		self.queue = queue
		
	def run(self):
		while True:
			link = self.queue.get()
			try:
				if "sly" in link:
					build(link)
				else:
					print(link + " is not valid")
			finally:
				self.queue.task_done()

def cmake(path):	
	thread_print("Starting cmake of " + os.path.basename(path) + "...")

	log = open("cmake_" + os.path.basename(path) + '.tlog', 'w')

	if not os.path.exists(os.path.join(path, "build-x64")):
		os.makedirs(os.path.join(path, "build-x64"))
		
	abspath = os.path.join(path, "build-x64")
	if(USE_MSVC):
		p = subprocess.Popen(["cmake", "../","-G", "Visual Studio 15 2017","-A","x64","-T","host=x64"], cwd=abspath, shell=True, stdout=log, stderr=log, stdin=log)
	else:
		thread_print(abspath)
		p = subprocess.Popen(["cmake", "../","-DCMAKE_OSX_ARCHITECTURES=x86_64"], cwd=abspath, stdout=log, stderr=log, stdin=log)
	p.wait()
	if not p.returncode == 0:
		thread_print("A cmake error code=" + str(p.returncode) + " has occurred while building " + os.path.basename(path))
		errors[os.path.basename(path)] = p.returncode
	else:
		thread_print("Completed cmake " + os.path.basename(path) + " successfully.")
	
	log.close()

def build(path):		
	thread_print("Starting msbuild of " + os.path.basename(path) + "...")

	log = open("msbuild_" + os.path.basename(path) + '.tlog', 'w')

	if(USE_MSVC):
		p = subprocess.Popen(["msbuild", "/nologo","/p:Configuration=Debug","/p:Platform=x64","/m:8","/v:m",os.path.join(os.path.abspath(path), "build-x64/" + os.path.basename(path) + ".vcxproj")], cwd=path, shell=True, stdout=log, stderr=log, stdin=log, )
	else:
		p = subprocess.Popen(["make"], cwd=os.path.join(os.path.abspath(path), "build-x64/"), stdout=log, stderr=log, stdin=log, )
	p.wait()
	if not p.returncode == 0:
		thread_print("A msbuild error code=" + str(p.returncode) + " has occurred while building " + os.path.basename(path))
		errors[os.path.basename(path)] = p.returncode 
	else:
		thread_print("Completed msbuild " + os.path.basename(path) + " successfully.")
	
	log.close()

def thread_print(data):
	print("[" + td_format(datetime.now() - starttime) + " " + str(threading.get_ident()).rjust(6) + "] " + data)

def td_format(delta):
	hours, remainder = divmod(delta.total_seconds(), 3600)
	minutes, seconds = divmod(remainder, 60) 
	return '{:02}:{:02}:{:04}'.format(int(minutes + hours * 60), int(seconds), int(remainder * 1000))


def cmake_all(dir_list):
	# Create a queue to communicate with the worker threads
	queue = Queue()
    # Create 8 worker threads
	for x in range(8):
		worker = CMakeWorker(queue)
        # Setting daemon to True will let the main thread exit even though the workers are blocking
		worker.daemon = True
		worker.start()
    # Put the tasks into the queue as a tuple
	for link in dir_list:
		queue.put(os.path.abspath(link))
    # Causes the main thread to wait for the queue to finish processing all the tasks
	queue.join()

def build_all(dir_list):
	# Create a queue to communicate with the worker threads
	queue = Queue()
    # Create 8 worker threads
	for x in range(8):
		worker = BuildWorker(queue)
        # Setting daemon to True will let the main thread exit even though the workers are blocking
		worker.daemon = True
		worker.start()
    # Put the tasks into the queue as a tuple
	for link in dir_list:
		queue.put(os.path.abspath(link))
    # Causes the main thread to wait for the queue to finish processing all the tasks
	queue.join()

def stop_on_error():
	if(len(errors) > 0):
		clean_up_and_halt()

def clean_up_and_halt():
	files = os.listdir(os.getcwd())
	for file in files:
		if file.endswith(".tlog"):
			remove_file = True
			for key in errors.keys():
				if(key in os.path.basename(file)):
					flog = open(file, 'r')
					print(flog.read())
					flog.close()
					remove_file = False
			if(remove_file):
				os.remove(file)
				
					
	sys.exit()

def main(): #dir_list = ['slyd3d11','slyd3d12','slygl4', 'slycore', 'slyengine', 'slywin32', 'slyedit']
	dir_list = ['slycore', 'slyengine']
	if(PLATFORM == "Windows"):
		dir_list.append('slywin32')
	if(PLATFORM == "Darwin"):
		dir_list.append('slymacos')

	cmake_all(dir_list)
	stop_on_error()

	for proj_name in dir_list:
		build(os.path.abspath(proj_name))
		stop_on_error()

	dir_list = ['slyedit']#, 'slygl4']
	if(PLATFORM == "Windows"):
		dir_list.extend(['slyd3d12']) #'slyd3d11',

	cmake_all(dir_list)
	stop_on_error()

	for proj_name in dir_list:
		build(os.path.abspath(proj_name))
		stop_on_error()

	clean_up_and_halt()
	
	
if __name__ == '__main__':
    main()
