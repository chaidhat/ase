# Aircraft Simulation Engine
### This is a private repository. © 2020 Chaidhat Chaimongkol
Platform: X-Plane 11.50\
Dependencies: XPLM 302 SDK, OpenGL32, GLEW32\
Start Date: 26-05-2020\
\
[company name]\
Dunman\
Chaidhat Chaimongkol

![](https://github.com/Chai112/ase/blob/master/ASE-flow-1.png)

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

### Build Process
1. build.bat invokes GNU make.
2. Makefile gives a recipe for how to build.
3. All .cpp are compiled their respective headers .hpp and include/%/CHeaders
4. All .cpp are compiled and linked with their respective .hpp to .o
5. .o is linked with include/%/libraries to create an .dll (.xpl) in bin(aries) directory

plugin is linked to `ase.hpp`\
`ase.hpp` links to everything in `src/ase/ase`\
`asepch.hpp` contains all of XPLM and GLEW headers.

### File structure
as of commit 8
```
TOP
│   .gitignore              for git
│   .ycm_extra_conf.py      for vim you-complete-me
│   build.bat               builds and installs once
│   buildforever.bat        builds and installs forever
│   clean.bat               clean directory
│   makefile                for makefile & build batches
│   README.md 
│
├───bin
│       win.xpl             output plugin
│
├───include                 contains all dependencies/vendors
│   ├───GLEW                vendor OpenGL GLEW
│   │       ...
│   │
│   └───SDK                 vendor X-Plane's 302 SDK
│           ...
│
└───src                     source files
    ├───ase                 engine-side code
    │   │   ase.hpp                 main header file for ase
    │   │   asepch.hpp              pre-compiled header
    │   │
    │   └───ase
    │       ├───core        main functionalities
    │       │       entryPoint.hpp  initialises the plugin with SDK
    │       │       data.cpp        manages data IO of X-Plane
    │       │       data.hpp        
    │       │       event.cpp       manages plugin events behaviour
    │       │       event.hpp        
    │       │       io.cpp          manages IO of the engine
    │       │       io.hpp        
    │       │       plugin.cpp      manages standard plugin behaviour
    │       │       plugin.hpp
    │       │
    │       ├───debug       debugging and reporting
    │       │       log.cpp         manages debug logging
    │       │       log.hpp    
    │       │
    │       └───graphics    visual graphical interaction
    │               graphics.cpp    manages graphics and drawing with GLEW
    │               graphics.hpp    
    │
    └───plugin              plugin-side code
            sample-plugin.cpp       sample plugin for initialisation
```

### Code convention
```
1. 4 spaces to a tab.
2. Allman brace placement, empty line between scope declarations
3. SNAKE_CASE for preprocessor statements
4. PascalCase for namespace, classes and functions
5. camelCase for variables
6. Naming convention (Hungarian type-specification)-
    g_  member of a global namespace, integer (e.g. g_path)
    m_  member of a structure/class, integer
    s_  static member of a structure/class
    c_  constansts
    f   booleans (e.g. bool m_fBegin)
    p   pointers or references (e.g. int* m_pRef)
    ...Interface interface (pure abstract) classes (e.g. class PluginInterface {};)
    ...Abstract abstract classes
    ...Manager static manager namespaces
7. Classes and vars should be nouns, functions should be verbs, keywords are adjectives.
8. For engine code, avoid 'using namespace' for clarity
9. Pointers and references should be put next to the type. (e.g. int* m_foo, NOT int *m_foo)
```

