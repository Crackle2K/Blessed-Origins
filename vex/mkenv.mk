# VEXcode mkenv.mk 2019_06_06_01

# macros to help with windows paths that include spaces
sp :=
sp +=
qs = $(subst ?,$(sp),$1)
sq = $(subst $(sp),?,$1)

# default platform and build location
PLATFORM  = vexv5
BUILD     = build

# version for clang headers
ifneq ("$(origin HEADERS)", "command line")
HEADERS = 8.0.0
endif

# Project name passed from app
ifeq ("$(origin P)", "command line")
PROJECT  = $(P)
else
PROJECT  = $(notdir $(call sq,$(abspath ${CURDIR})))
endif

# check if the PROJECT name contains any whitespace
ifneq (1,$(words $(PROJECT)))
$(error Project name cannot contain whitespace: $(PROJECT))
endif

# SDK path passed from app
ifeq ("$(origin T)", "command line")
VEX_SDK_PATH = $(T)
endif

# printf_float flag name passed from app
ifeq ("$(origin PRINTF_FLOAT)", "command line")
PRINTF_FLAG = -u_printf_float
endif

# Verbose flag passed from app
ifeq ("$(origin V)", "command line")
VERBOSE = $(V)
endif

# Allow suppression of warnings via environment variable
ifneq ("$(origin SUPPRESS_WARNINGS)", "undefined")
WFLAG = -w
endif

# SDK version - set default if not provided by build environment
ifeq ("$(origin SDK_VERSION)", "undefined")
SDK_VERSION = latest
endif

# Get the SDK path for the current platform
VEX_SDK_HOME = $(HOME)/vex-sdks
VEX_SDK = $(VEX_SDK_HOME)/$(PLATFORM)/$(SDK_VERSION)

# Verify SDK exists
ifeq ("$(wildcard $(VEX_SDK))","")
$(error VEX SDK path not found: $(VEX_SDK))
endif

# include toolchain options
include $(VEX_SDK)/mkspec.mk

# Project name passed from app
PROJECT_NAME := $(PROJECT)

# Set to 1 to enable verbose mode
ifeq ($(VERBOSE),1)
V :=
else
V := @
endif
