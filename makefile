# Standard workflow makefile, a few notes on the build process

# This makefile is created to be compatible with the workflow environment
#
# This makefile only specifies rules for building the software, and thus does not handle external
# directories that are system specific as workflow understands each platform/developer has their own
# preferences for managing files. Developers who have downloaded workflow can use the programs provided
# to install their programs and libraries
#
# Workflow aims to keep developer libraries, headers, and executable scripts seperate from the system's
# for easier maintainability and generic, cross-platform install rules.

#*****************  Alias  ************************************************

STATIC :=-Wl,-Bstatic
DYNAMIC :=-Wl,-Bdynamic
LINKAGE :=
comma :=,

#*****************  User Config ********************************************

MAIN := ucurses

LIBRARIES := ctk ncurses boost
LIBFILES := -lctk -lboost_system -lboost_filesystem

CXX := g++
CXXFLAGS := -g -std=c++17 -O2 

#*****************  Pre-processor  ****************************************

INCDIR = -I include 

#*****************  Linux  ************************************************

ifeq ($(OS),Linux)
	CXX := g++
	TARGET := gcc
	ifeq ($(strip $(target)),)
		CXXFLAGS += -fPIC -flto
		LIBFILES += -lncurses
	endif
	LIBEXT := .so
	OBJEXT := .o
	LIBDIR := $(foreach l,$(LIBRARIES),-L$(WORKFLOW_LIB)/C++/$(l)/$(TARGET))
	RPATH :=$(subst -L,-Wl$(comma)-rpath=,$(LIBDIR))
endif

#*****************  Windows  ******************************************

ifeq ($(OS),Windows_NT)
	CXX := g++
	LIBEXT := .dll
	APPEXT := .exe
	OBJEXT := .obj
	TARGET := mingw64
	LIBFILES += $(WORKFLOW_LIB)/C++/$(TARGET)/pdcurses.a
	LIBDIR := -L$(WORKFLOW_LIB)\C++\$(TARGET)
endif

ifeq ($(target), w32)
	CXX := x86_64-w64-mingw32-g++-win32
	LIBEXT := .dll
	APPEXT := .exe
	OBJEXT := .obj
	TARGET := mingw32
	LIBFILES += $(STATIC) $(WORKFLOW_LIB)/C++/$(TARGET)/pdcurses.lib
	LIBDIR := -L$(WORKFLOW_LIB)/C++/$(TARGET)
endif
	
ifeq ($(target), w64)
	CXX := x86_64-w64-mingw32-g++
	LIBEXT := .dll
	APPEXT := .exe
	OBJEXT := .obj
	TARGET := mingw64
	LIBDIR := -L$(WORKFLOW_LIB)/C++/$(TARGET)
endif

#*****************  Build  ************************************************

LIBPATH :=lib/$(TARGET)
BUILDPATH :=bin/$(TARGET)

#*****************  Branching  ********************************************

BRANCHES := $(wildcard src/*)
ifeq ($(strip $(branch)),)
	SRC := $(foreach b, $(BRANCHES), $(wildcard $(b)/*.cpp))
	LIB := lib$(MAIN)
else
	SRC := $(wildcard src/$(branch)/*.cpp) # Pass $branch for linking objects from one branch only
	LIB := lib$(MAIN)$(branch)
endif

ifeq ($(strip $(isolate)),) # For compiling executables that do not require other objects
else
	SRC := 
endif

#*****************  Testing  ********************************************

ifeq ($(strip $(test)),)
else
	BUILDPATH :=$(BUILDPATH)/test
	SRC += src/test/$(test).cpp
	TARGETAPP :=$(test)
endif

#*****************  Release  **********************************************
	
ifeq ($(strip $(name)),)
else
	SRC += src/main/$(name).cpp
	TARGETAPP := $(name)
endif

#*****************  Build  *****************************************

OBJ := $(SRC:.cpp=$(OBJEXT)) # Objects used in linking differ on compiler/target

DEP := $(OBJS:$(OBJEXT)=.d)

LIBRARY := $(LIB)$(LIBEXT)$(ver)
ARCHIVE := $(LIB).a
APP := $(TARGETAPP)$(ver)$(APPEXT) # Isolate the executable and library filenames on their own

TARGETAPP := $(BUILDPATH)/$(APP)
TARGETARCHIVE := $(LIBPATH)/$(ARCHIVE)
TARGETLIB := $(LIBPATH)/$(LIBRARY)

#*****************  Rules *************************************************

.PHONY: depend clean cleandep \
		compile shared archive link \
		variables args help cleanbin \
		cleanlib

all:
	@printf "\nUse make help for a list of functions this makefile is capable of.\n\n"

compile: $(OBJ)
	@printf "\n$(MAIN) objects have been compiled successfully and are up to date.\n\n"

help:
	@printf "\nWelcome to the standard makefile for Roguelight C++ applications.\n"
	@printf "This program is capable of many functions to assist in the production,\n"
	@printf "installation and organisation of your libraries for your programs.\n\n"
	@printf "The list of functions is as follows:\n\n"
	@printf "make compile		| Compile objects without linking.\n"
	@printf "make link		| Link object files into executable. Default name is $(MAIN)\n"
	@printf "make shared		| Link object files into dynamic library\n"
	@printf "make variables		| Print out list of variables used in this makefile.\n"
	@printf "make clean 		| Removes object files for target\n"
	@printf "make cleanbin 		| Cleaning local binaries from $(BUILDPATH)\n"
	@printf "make cleanlib 		| Cleaning local libraries from $(LIBPATH)\n"
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
	@printf "\nSuccessful\n"

$(TARGETARCHIVE): $(OBJ)
	@printf "\nPackaging objects into executable static library $(LIB).a in dir $(BUILDPATH)\n"
	rm -f $(TARGETARCHIVE)
	ar -cvq $(TARGETARCHIVE) $(OBJ)
	@printf "\nSuccessful\n"

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

cleanbin:
	@printf "\nCleaning local binaries from $(BUILDPATH)\n"
	rm -f $(BUILDPATH)*$(APPEXT)
	@printf "\nSuccessful\n\n"

cleanlib:
	@printf "\nCleaning local libraries from $(LIBPATH)\n"
	rm -f $(LIBPATH)/*
	@printf "\nSuccessful\n\n"

$(TARGETLIB): $(OBJ) 
	@printf "\nLinking objects for shared library $(TARGETLIB)\n"
	$(CXX) $(LIBDIR) --shared -o $@ $(OBJ) $(LIBFILES)
	@printf "\nSuccessful\n"
