Royale Python Samples
=====================

To use the Python samples you have to install numpy and matplotlib,
because they are used for the visualization of the data.
This version of the Royale Python wrapper was built against Python .
To use it you will need a Python version with the same major and minor version.
If you want to use the Python wrapper with a different Python version please refer to 
the steps in "Building the Python wrapper".

Python Dependencies
---------------------
The Python wrapper will only work with specific versions of Python : 

 Windows 10            - Python 3.10
 Ubuntu 20.04 64bit    - Python 3.8
 Linux ARM 32bit       - Python 3.7
 Linux ARM 64bit       - Python 3.8
 MacOs Arm 64bit       - Python 3.11

If you want to use a different Python version please have a look at
"Building the Python wrapper" in this document. 
 

Linux installation
------------------

On Ubuntu and Debian, install python3-matplotlib and its dependencies.

You also need the libpython3.x package for the same minor version of python3.x that the roypy
library was built for. In Debian and Ubuntu the libpython3.8, libpython3.9 and libpython3.10
libraries are all co-installable. For example, if running a sample fails with:

    ImportError: libpython3.8m.so.1.0: cannot open shared object file: No such file or directory

then the libpython3.8 package is required.


Windows installation
--------------------

There are several different python packages for Windows. The Royale
bindings work with the packages from www.python.org (e.g. version
3.10.9). The architecture (e.g. 32 bit vs. 64 bit) needs to match that
of the Royale installation.

If you are using cygwin on Windows, be advised that the python package
which can be installed as part of cygwin does not work with the Royale
bindings. Please make sure that the correct python binary is in the
path (e.g. by running ``which python``).

If you need to have different python versions, you can use
[pyenv-win](https://github.com/pyenv-win/pyenv-win)
to manage multiple python versions. If you want to us pyenv-win, install it
according to the installation instruction on the web site.

For a Windows install with python from python.org, you will need the
following additional packages:
- numpy
- matplotlib
- pywin32 (contains the pythoncom packages needed by royale)


These can be installed using "pip install &lt;package&gt;". Note that there
are issues when trying to set up virtual environments (described
below) when using the python.org python in a cygwin environment (it
doesn't seem to handle cygwin paths correctly and it produces shell
scripts (e.g. activate) which are unsuitable for the cygwin bash).


MacOs installation
------------------

MacOs comes with a Python3 installation. Unfortunatley some parts of this
standard installation are broken. To get a working Python on MacOs, you need to
install a new python, either from python.org, or with a MacOs package manager
like [brew](https://brew.sh/). For example, if you encounter errors like this:

    Terminating app due to uncaught exception NSInvalidArgumentException', reason: '-[NSApplication _setup:]: unrecognized selector sent to instance 0x7ffbcc2f3720'
Then you need to install a newer python version.

Virtual environments
--------------------

If you can't (or don't want to) modify your system python
installation, you may be able to make a local installation of numpy
and matplotlib in a virtual environment. For example, to install in
`~/bin/virtual_env_for_python`:

```
mkdir ~/bin/virtual_env_for_python
python -m venv ~/bin/virtual_env_for_python
. ~/bin/virtual_env_for_python/Scripts/activate
pip install numpy
pip install matplotlib
```

Then in any shell that you run the samples in, start with

```
. ~/bin/virtual_env_for_python/Scripts/activate
```

__Attention:__ Some python version on Windows have a bug that leads to problems
with virtual envionments. If you see errors like:
```
C:\Users\user\virttest>python3 -m venv env
Error: [WinError 2] The system cannot find the file specified
```
To fix this error, switch to your python installation directory, create a
directory, and move all executables named "python*3*.exe into this directory.
```
mv python*3*.exe backup_dir
```


Building the Python wrapper
---------------------------

To build the Python wrapper for Royale you have to install Python 3 libraries 
and SWIG (http://www.swig.org/) and make sure that they are found in CMake 
(PYTHON\_LIBRARY has to be found, but if you want to be able to debug 
PYTHON\_LIBRARY\_DEBUG has to be found too).
To enable the internal use of numpy to speed up the data retrieval you also have
download the numpy.i file from here :
https://github.com/numpy/numpy/tree/master/tools/swig and place it in the current folder.
Afterwards you can enable the royale\_USE\_NUMPY\_IN\_ROYPY option in CMake.

If no Python 3 debug library is found the debug wrapper will link against the
release library of Python 3.

All C++ functions that return CameraStatus are wrapped with code that throws an
exception if they return non-SUCCESS.

- Start the CMake GUI
- Select the python/swig subfolder as source and select a build folder
- Hit configure and select your compiler (also make sure that the bitness of the compiler
  corresponds to the Royale package you installed)
    - You may need to install the compiler first, on Linux, for example, you need GCC. In this example you would then select "Unix Makefiles" as generator with the default compiler option. But this may vary depending on your system. 
- Hit generate
- Use generated solution/makefile to build the wrapper

