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
PRJ_ROOT_DIR := C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout
WS_ROOT_DIR := C:/Users/CHAOS/Documents/2010/Workspace



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
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 



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
PROJECT_TARGETS = Breakaway10SVNCheckout/$(MODE_DIR)/Breakaway10SVNCheckout.out


#Rules

# Breakaway10SVNCheckout
ifeq ($(DEBUG_MODE),1)
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
Breakaway10SVNCheckout/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
Breakaway10SVNCheckout/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
Breakaway10SVNCheckout/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Breakaway10SVNCheckout/$(MODE_DIR)/% : DEFINES = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : EXPAND_DBG = 0
Breakaway10SVNCheckout/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
Breakaway10SVNCheckout/$(MODE_DIR)/% : CPU = PPC603
Breakaway10SVNCheckout/$(MODE_DIR)/% : TOOL_FAMILY = gnu
Breakaway10SVNCheckout/$(MODE_DIR)/% : TOOL = gnu
Breakaway10SVNCheckout/$(MODE_DIR)/% : TOOL_PATH = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
Breakaway10SVNCheckout/$(MODE_DIR)/% : LIBPATH = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : LIBS = 
Breakaway10SVNCheckout/$(MODE_DIR)/% : OBJ_DIR := Breakaway10SVNCheckout/$(MODE_DIR)

Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Breakaway10.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Breakaway10.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/ChaosLinearPot.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/ChaosLinearPot.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/DashboardDataSender.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/DashboardDataSender.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Dribbler.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Dribbler.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Gamepad.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Gamepad.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Kicker.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Kicker.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Logger.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Logger.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SamplePIDOutput.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/SamplePIDOutput.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SoccerBall.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/SoccerBall.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Target.o : C:/Users/CHAOS/Documents/2010/Workspace/Breakaway10SVNCheckout/Target.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_Breakaway10SVNCheckout = Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Breakaway10.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/ChaosLinearPot.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/DashboardDataSender.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Dribbler.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Gamepad.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Kicker.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Logger.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SamplePIDOutput.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SoccerBall.o \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Target.o

Breakaway10SVNCheckout/$(MODE_DIR)/Breakaway10SVNCheckout.out : $(OBJECTS_Breakaway10SVNCheckout)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_Breakaway10SVNCheckout) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_Breakaway10SVNCheckout) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Breakaway10SVNCheckout/$(MODE_DIR)/Breakaway10SVNCheckout_compile_file : $(FILE) ;

_clean :: Breakaway10SVNCheckout/$(MODE_DIR)/Breakaway10SVNCheckout_clean

Breakaway10SVNCheckout/$(MODE_DIR)/Breakaway10SVNCheckout_clean : 
	$(TRACE_FLAG)if [ -d "Breakaway10SVNCheckout" ]; then cd "Breakaway10SVNCheckout"; rm -rf $(MODE_DIR); fi

DEP_FILES := Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Breakaway10.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/ChaosLinearPot.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/DashboardDataSender.d \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Dribbler.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Gamepad.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Kicker.d \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Logger.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SamplePIDOutput.d Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/SoccerBall.d \
	 Breakaway10SVNCheckout/$(MODE_DIR)/Objects/Breakaway10SVNCheckout/Target.d
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
