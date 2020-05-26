# Aircraft Simulation Engine
Platform: X-Plane 11.50\
Dependencies: XPLM 302 SDK and OpenGL32, GLEW32 APIs\
Start Date: 26-05-2020

### This is a private repository. Source code is protected.

### Usage Instructions
Instructions for Windows.\
For Mac and Linux, installation should involve homebrew.\
Please feel free to study, edit or remix the boilerplate source code.
1. Please install [MinGW-w64](https://sourceforge.net/projects/mingw-w64/), make sure it is x86_64 architecture
2. Please install [Make](http://gnuwin32.sourceforge.net/downlinks/make.php) for Windows
3. Click and run `build.bat` to compile and link the program

Violá! - find the `win.xpl` DLL plugin in the bin(aries) folder.\
\
Alternatively, if `build.bat` fails or if you are not using Windows, try using a CLI, cd into the directory and compile by running `make.exe`, normally installed at `C:\Program Files (x86)\GnuWin32\bin\make.exe` or with Mac/Linux, can be installed with `brew install make` and `brew install gcc` and change dependencies in the `makefile`.

### Installed Dependencies
Theses are already come with the Github clone. If they are out of date or errors occur, please find downloads here.\
Please find the latest X-Plane SDK [here](https://developer.x-plane.com/sdk/plugin-sdk-downloads/) and replace everything in`include/SDK`.\
Please find the latest GLEW [here](http://glew.sourceforge.net/install.html) and manually replace everything in `include/GLEW`. Install the `.exe` to `%systemroot%\system32` folder too.
