#*****************  Alias  ************************************************

STATIC :=-Wl,-Bstatic
DYNAMIC :=-Wl,-Bdynamic
LINKAGE :=
comma :=,

#*****************  User Config ********************************************

BRANCHES := algorithm application file log memory misc pattern random

LIBRARIES :=boost 
LIBFILES :=$(DYNAMIC) -lboost_system -lboost_filesystem -Wl,--as-needed

#*****************  Pre-processor  ****************************************

INCDIR = -I include/ -I src/

#*****************  Compiler  *********************************************

CXX := # 
CXXFLAGS := -g -std=c++17 -fpermissive 

ifeq ($(OS),Linux)
	ifeq ($(target), windows) # Cross compiler support
	endif
endif

#*****************  Commands  *********************************************

comma :=,

#*****************  Environment  ******************************************

APPEXT := # Depends on target OS

ifeq ($(OS),Linux)
	ifeq ($(target), windows) # Cross compiler support
		CXX := x86_64-w64-mingw32-g++
		CXXFLAGS += -static-libgcc -static-libstdc++ 
		LIBEXT := .dll
		APPEXT := .exe
		OBJEXT := .obj
	else
		CXX := g++
		CXXFLAGS += -fPIC
		LIBEXT := .so
		OBJEXT := .o
	endif
endif

ifeq ($(OS),Windows_NT)
	CXX := x86_64-w64-mingw32-g++
	LIBEXT := .dll
	APPEXT := .exe
	OBJEXT := .obj
endif

#*****************  Linker  ***********************************************

LIBDIR := $(foreach l,$(LIBRARIES),-L$(WORKFLOW_LIB)/C++/$(l)/$(CXX))
ifeq ($(OS),Linux)
	RPATH :=$(subst -L,-Wl$(comma)-rpath=,$(LIBDIR))
endif

ifeq ($(OS),Windows_NT)
	RPATH := Windows executables can not store rpath 
endif

#*****************  Build  ************************************************

MAIN := ctk

LIBPATH := lib/$(CXX)
BUILDPATH := #

ifeq ($(strip $(branch)),)
	SRC := $(foreach b, $(BRANCHES), $(wildcard src/$(b)/*.cpp))
	LIB := lib$(MAIN)
else
	SRC := $(wildcard src$(DIR)$(branch)$(DIR)*.cpp) # Pass $branch for linking objects from one branch only
	LIB := lib$(MAIN)$(branch)
endif

ifeq ($(strip $(isolate)),) # For compiling executables that do not require other objects
else
	SRC := 
endif

ifeq ($(strip $(test)),)
	ifeq ($(strip $(name)),)
		TARGETAPP := $(MAIN)
		BUILDPATH := ./
	else
		TARGETAPP := $(name)
		SRC += src$(DIR)main$(DIR)$(name).cpp
		BUILDPATH := bin/$(CXX)/
	endif
else
	BUILDPATH := bin/$(CXX)/test/
	SRC += src/test/$(test).cpp
	TARGETAPP :=$(test)
endif

OBJ := $(SRC:.cpp=$(OBJEXT)) # Objects used in linking differ on compiler/target

DEP := $(OBJS:$(OBJEXT)=.d)

LIBRARY := $(LIB)$(LIBEXT)$(ver)
ARCHIVE := $(LIB).a
APP := $(TARGETAPP)$(ver)$(APPEXT) # Isolate the executable and library filenames on their own

TARGETAPP := $(BUILDPATH)$(APP)
TARGETARCHIVE := $(LIBPATH)/$(ARCHIVE)
TARGETLIB := $(LIBPATH)/$(LIBRARY)

#*****************  Install  **********************************************

ifeq ($(OS),Windows_NT)
	LIBINSTALL := $(WORKFLOW_LIB)/C++/$(CXX) # All libraries are bundled together on windows
endif

ifeq ($(OS),Linux)
	LIBINSTALL := $(WORKFLOW_LIB)/C++/$(MAIN)
endif

INSTALLEDLIB:= $(LIBINSTALL)/$(CXX)/$(LIBRARY)
APPINSTALL := $(WORKFLOW)/bin

ifeq ($(strip $(dest)),)
	
else
	APPINSTALL :=$(APPINSTALL)/$(dest)
endif

#*****************  Rules *************************************************

.PHONY: depend clean cleandep \
		compile shared archive link \
		install uninstall \
		appinstall appuninstall \
		variables args help 

all:
	@printf "\nUse make help for a list of functions this makefile is capable of.\n\n"

compile: $(OBJ)
	@printf "\n$(MAIN) objects have been compiled successfully and are up to date.\n\n"

help:
	@printf "\nWelcome to the standard makefile for Roguelight C++ applications.\n"
	@printf "This program is capable of many functions to assist in the production of\n"
	@printf "and libraries for your programs.\n\n"
	@printf "The list of functions is as follows:\n\n"
	@printf "make compile		| Compile objects without linking.\n"
	@printf "make link		| Link object files into executable. Default name is $(MAIN)\n"
	@printf "make shared		| Link object files into dynamic library\n"
	@printf "make variables		| Print out list of variables used in this makefile.\n"
	@printf "make install		| Install project library files to $(WORKFLOW_LIB)\n"
	@printf "make uninstall		| Remove project library files from system\n"
	@printf "make appinstall		| Install project executable to $(APPINSTALL).\n"
	@printf "make appuninstall 	| Remove project executable from $(APPINSTALL)\n"
	@printf "make clean 		| Removes object files for target\n"
	@printf "make args 		| list all optional arguments that can be passed to this makefile for advanced functionality\n\n"
	@printf "Functions can be linked together, for example 'make clean compile program name=mario' is a valid command\n"
	@printf "that will remove all objects, re-compile them and then link the program named mario\n\n"

variables:
	@printf "\nOS:		| $(OS)\n\n"
	@printf "CXX: 		| $(CXX)\n"
	@printf "CXXFLAGS:	| $(CXXFLAGS)\n\n"
	@printf "BRANCHES:	| $(BRANCHES)\n"
	@printf "LIBRARIES:	| $(LIBRARIES)\n"
	@printf "LIBFILES:	| $(LIBFILES)\n\n"
	@printf "TARGETAPP: 	| $(TARGETAPP)\n"
	@printf "TARGETLIB: 	| $(TARGETLIB)\n"
	@printf "TARGETARCHIVE:	| $(TARGETARCHIVE)\n\n"
	@printf "APPINSTALL: 	| $(APPINSTALL)\n"
	@printf "LIBINSTALL: 	| $(LIBINSTALL)\n\n"
	@printf "INCDIR: 	| $(INCDIR)\n"
	@printf "LIBDIR:		| $(LIBDIR)\n"
	@printf "RPATH: 		| $(RPATH)\n\n"

args:
	@printf "\n name:		| Used to specify an name for generated executables other than $(MAIN)\n"
	@printf " test:		| Used to specify that a test executable is being built.\n"
	@printf " isolate: 	| Used to ignore objects in program compilation\n"
	@printf " branch: 	| Used to specify one branch as object dir instead of all. Provides modularity for linking libraries\n"
	@printf " dest:		| Used to specify a subdirectory of $(WORKFLOW)/bin to install an executable\n\n"
	@printf "Note that the difference between test and name is only the path of the build, this means test programs will not\n"
	@printf "will not be installed with 'make install'\n\n"

shared: $(TARGETLIB)
	@printf "\nLibrary $(TARGETLIB) is up to date.\n\n"

link: $(TARGETAPP)
	@printf "\nProgram $(TARGETAPP) is up to date.\n\n"

archive: $(TARGETARCHIVE)
	@printf "\nLibrary $(TARGETARCHIVE) is up to date.\n\n"

$(TARGETAPP): $(OBJ)
	@printf "\nLinking objects and dependencies into executable $(APP) in dir $(BUILDPATH)\n\n"
	$(CXX) $(CXXFLAGS) $(INCDIR) $(LIBDIR) -o $(TARGETAPP) $(OBJ) $(LIBFILES) $(RPATH)
	@printf "\nSuccessful\n\n"

$(TARGETARCHIVE): $(OBJ)
	@printf "\nPackaging objects into executable static library $(LIB).a in dir $(BUILDPATH)\n"
	rm -f $(TARGETARCHIVE)
	ar -cvq $(TARGETARCHIVE) $(OBJ)
	@printf "\nSuccessful\n\n"

%.obj:%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $<  -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $<  -o $@

%.d: %cpp
	$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

clean:
	rm -f $(OBJ)

cleandep:
	rm -f $(DEP)

$(TARGETLIB): $(OBJ) 
	@printf "\nLinking objects for shared library $(TARGETLIB)\n"
	$(CXX) $(LIBDIR) --shared -o $@ $(OBJ) $(LIBFILES)
	@printf "\nSuccessful\n\n"

install: # Consumers run scripts or executables, Devs use make install
	@printf "\nInstalling $(MAIN) header files to system path $(WORKFLOW)/include\n"
	cp -r include/$(MAIN) $(WORKFLOW)/include 
	@printf "\nInstalling $(LIBPATH) to $(LIBINSTALL)\n"
	cp -r $(LIBPATH) $(LIBINSTALL) 
	@printf "\nSuccessful\n\n"

appinstall:
	@printf "\nInstalling $(TARGETAPP) to directory $(APPINSTALL)\n"
	cp $(TARGETAPP) $(APPINSTALL)
	@printf "\nMake sure $(APPINSTALL) is include in PATH for execution from shell\n\n"

uninstall:
	@printf "\nRemoving $(MAIN) header files from system path $(SYSINC)\n"
	rm -r $(WORKFLOW)/include/$(MAIN)
	@printf "\nRemoving  $(LIB) from system path $(SYSLIB)\n"
	rm  $(LIBINSTALL)/$(LIBRARY)
	@printf "\nSuccessful\n\n"

appuninstall:
	@printf "\nRemoving $(APP) from $(APPINSTALL)\n"
	$(RM) $(APPINSTALL)/$(APP)
	@printf "\nSuccessful\n\n"
