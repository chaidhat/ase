@ECHO OFF
"C:\Program Files (x86)\GnuWin32\bin\make.exe"

ECHO Installing...
REM add your plugin directories here for auto install

COPY bin\win.xpl "D:\Documents\programs\X-Plane 11\Aircraft\Chai112\b777-300er\plugins\test"
COPY bin\win.xpl "D:\Documents\programs\X-Plane 11\Aircraft\Chai112\xtest1\plugins\test"
COPY bin\win.xpl "D:\Documents\programs\X-Plane 11\Aircraft\Chai112\xtest2\plugins\test"

ECHO Finished.
PAUSE

