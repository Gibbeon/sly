import os, subprocess, shutil, platform

if(not os.path.exists("build-x64")):
	os.makedirs("build-x64")

if(platform.system() == "Windows"):
	INIT_ENV_BAT = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64.bat"

	vars = subprocess.check_output([INIT_ENV_BAT, '&&', 'set'])
	for var in vars.splitlines():
		var = var.decode('cp1252')
		k, _, v = map(str.strip, var.strip().partition('='))
		if k.startswith('?'):
			continue
		os.environ[k] = v

	os.chdir("build-x64")
	os.system("cmake ../ -G \"Visual Studio 15 2017\" -A x64 -T host=x64")
	os.chdir("../")
	os.system("msbuild /nologo /v:m /p:Configuration=Debug /p:Platform=\"x64\" ./build-x64/" + os.path.basename(os.getcwd()) + ".sln")
else:
	os.chdir("build-x64")
	os.system("cmake ../ -DCMAKE_OSX_ARCHITECTURES=x86_64")
	os.system("make")
	os.chdir("../")
