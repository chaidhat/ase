# https://stackoverflow.com/questions/40621451/makefile-automatically-compile-all-c-files-keeping-o-files-in-separate-folde
# written by Chaidhat Chaimongkol 15-05-2020 
# builds C++ for XP11 Windows

CC=gcc # use GCC as a compiler

# Directories
BDIR = bin# dir for binaries
ODIR := obj# dir for C++ objects
SDIR := src#dur for source

SRC := $(wildcard $(SDIR)/*.cpp)    # all C++ files

# Objects
_OBJ := $(SRC:.cpp=.o) # all C++, except suffix is .o
OBJ = $(patsubst $(SDIR)/%,$(ODIR)/%,$(_OBJ)) # append ODIR

# Dependencies
_DEPS = include/sdk/cheaders/xplm include/sdk/cheaders/widgets include/glew/cheaders
DEPS = $(addprefix -I,$(_DEPS)) # append -I

# Library Directories
_LDIRS = include/sdk/libraries/win include/glew/libraries
LDIRS = $(addprefix -L,$(_LDIRS)) # append -L

# Libraries
_LIBS = XPLM_64 XPWidgets_64 glew32 opengl32
LIBS = $(addprefix -l, $(_LIBS)) # append -l

# Definitions
_DEFS = IBM XPLM200 XPLM210 XPLM300 XPLM301 XPLM302							
DEFS = $(addprefix -D, $(_DEFS)) # append -D

# Flags
CXXFLAGS = -I$(SDIR) -m64 $(DEFS) $(DEPS) 
LDFLAGS = -shared $(LDIRS) $(LIBS) 

#%.cpp:
#	echo $@

$(ODIR)/%.o: $(SDIR)/%.cpp $(SDIR)/%.hpp
	@echo Compiling $<
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(BDIR)/win.xpl: $(OBJ)
	@echo Linking $@
	$(CC) -o $@ $^ $(LDFLAGS) 
