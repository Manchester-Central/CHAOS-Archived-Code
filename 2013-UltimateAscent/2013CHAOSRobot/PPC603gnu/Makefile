# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace2013
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/2013CHAOSRobot



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = OriginalDefaultCode/$(MODE_DIR)/OriginalDefaultCode.out \
	 2013CHAOSRobot/$(MODE_DIR)/2013CHAOSRobot.out


#Rules

# OriginalDefaultCode
ifeq ($(DEBUG_MODE),1)
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
OriginalDefaultCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
OriginalDefaultCode/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
OriginalDefaultCode/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
OriginalDefaultCode/$(MODE_DIR)/% : IDE_DEFINES = 
OriginalDefaultCode/$(MODE_DIR)/% : PROJECT_TYPE = DKM
OriginalDefaultCode/$(MODE_DIR)/% : DEFINES = 
OriginalDefaultCode/$(MODE_DIR)/% : EXPAND_DBG = 0
OriginalDefaultCode/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
OriginalDefaultCode/$(MODE_DIR)/% : CPU = PPC603
OriginalDefaultCode/$(MODE_DIR)/% : TOOL_FAMILY = gnu
OriginalDefaultCode/$(MODE_DIR)/% : TOOL = gnu
OriginalDefaultCode/$(MODE_DIR)/% : TOOL_PATH = 
OriginalDefaultCode/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
OriginalDefaultCode/$(MODE_DIR)/% : LIBPATH = 
OriginalDefaultCode/$(MODE_DIR)/% : LIBS = 
OriginalDefaultCode/$(MODE_DIR)/% : OBJ_DIR := OriginalDefaultCode/$(MODE_DIR)

OBJECTS_OriginalDefaultCode =

OriginalDefaultCode/$(MODE_DIR)/OriginalDefaultCode.out : $(OBJECTS_OriginalDefaultCode)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_OriginalDefaultCode) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_OriginalDefaultCode) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

OriginalDefaultCode/$(MODE_DIR)/OriginalDefaultCode_compile_file : $(FILE) ;

_clean :: OriginalDefaultCode/$(MODE_DIR)/OriginalDefaultCode_clean

OriginalDefaultCode/$(MODE_DIR)/OriginalDefaultCode_clean : 
	$(TRACE_FLAG)if [ -d "OriginalDefaultCode" ]; then cd "OriginalDefaultCode"; rm -rf $(MODE_DIR); fi


# 2013CHAOSRobot
ifeq ($(DEBUG_MODE),1)
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013CHAOSRobot/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
2013CHAOSRobot/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
2013CHAOSRobot/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
2013CHAOSRobot/$(MODE_DIR)/% : IDE_DEFINES = 
2013CHAOSRobot/$(MODE_DIR)/% : PROJECT_TYPE = DKM
2013CHAOSRobot/$(MODE_DIR)/% : DEFINES = 
2013CHAOSRobot/$(MODE_DIR)/% : EXPAND_DBG = 0
2013CHAOSRobot/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
2013CHAOSRobot/$(MODE_DIR)/% : CPU = PPC603
2013CHAOSRobot/$(MODE_DIR)/% : TOOL_FAMILY = gnu
2013CHAOSRobot/$(MODE_DIR)/% : TOOL = gnu
2013CHAOSRobot/$(MODE_DIR)/% : TOOL_PATH = 
2013CHAOSRobot/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp  -mlongcall
2013CHAOSRobot/$(MODE_DIR)/% : LIBPATH = 
2013CHAOSRobot/$(MODE_DIR)/% : LIBS = 
2013CHAOSRobot/$(MODE_DIR)/% : OBJ_DIR := 2013CHAOSRobot/$(MODE_DIR)

2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/CHAOSDebug.o : $(PRJ_ROOT_DIR)/CHAOSDebug.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Chassis.o : $(PRJ_ROOT_DIR)/Chassis.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Climb.o : $(PRJ_ROOT_DIR)/Climb.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Conveyor.o : $(PRJ_ROOT_DIR)/Conveyor.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Gamepad.o : $(PRJ_ROOT_DIR)/Gamepad.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/HPRoller.o : $(PRJ_ROOT_DIR)/HPRoller.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Intake.o : $(PRJ_ROOT_DIR)/Intake.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Main.o : $(PRJ_ROOT_DIR)/Main.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Manipulator.o : $(PRJ_ROOT_DIR)/Manipulator.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Misc.o : $(PRJ_ROOT_DIR)/Misc.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Shooter.o : $(PRJ_ROOT_DIR)/Shooter.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_2013CHAOSRobot = 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/CHAOSDebug.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Chassis.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Climb.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Conveyor.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Gamepad.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/HPRoller.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Intake.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Main.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Manipulator.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Misc.o \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Shooter.o

2013CHAOSRobot/$(MODE_DIR)/2013CHAOSRobot.out : $(OBJECTS_2013CHAOSRobot)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_2013CHAOSRobot) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_2013CHAOSRobot) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

2013CHAOSRobot/$(MODE_DIR)/2013CHAOSRobot_compile_file : $(FILE) ;

_clean :: 2013CHAOSRobot/$(MODE_DIR)/2013CHAOSRobot_clean

2013CHAOSRobot/$(MODE_DIR)/2013CHAOSRobot_clean : 
	$(TRACE_FLAG)if [ -d "2013CHAOSRobot" ]; then cd "2013CHAOSRobot"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/CHAOSDebug.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Chassis.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Climb.d \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Conveyor.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Gamepad.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/HPRoller.d \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Intake.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Main.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Manipulator.d \
	 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Misc.d 2013CHAOSRobot/$(MODE_DIR)/Objects/2013CHAOSRobot/Shooter.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
