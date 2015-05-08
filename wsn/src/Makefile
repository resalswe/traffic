#
# OMNeT++/OMNEST Makefile for wsn
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../mixim-veins/src/inet_stub/util -I../../mixim-veins/src/base/messages -I../../mixim-veins/src/inet_stub/linklayer/contract -I../../mixim-veins/src/inet_stub/mobility -I../../mixim-veins/src/base/modules -I../../mixim-veins/src/base/utils -I../../mixim-veins/src -I../../mixim-veins/src/inet_stub/mobility/models -I../../mixim-veins/src/base -I../../mixim-veins/src/inet_stub/base -I../../mixim-veins/src/base/phyLayer -I../../mixim-veins/src/base/connectionManager -I../../mixim-veins/src/inet_stub/networklayer/common -L../../mixim-veins/out/$$\(CONFIGNAME\)/src -lmixim -KMIXIM_VEINS_PROJ=../../mixim-veins
#

# Name of target to be created (-o option)
TARGET = wsn$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../mixim-veins/src/inet_stub/util \
    -I../../mixim-veins/src/base/messages \
    -I../../mixim-veins/src/inet_stub/linklayer/contract \
    -I../../mixim-veins/src/inet_stub/mobility \
    -I../../mixim-veins/src/base/modules \
    -I../../mixim-veins/src/base/utils \
    -I../../mixim-veins/src \
    -I../../mixim-veins/src/inet_stub/mobility/models \
    -I../../mixim-veins/src/base \
    -I../../mixim-veins/src/inet_stub/base \
    -I../../mixim-veins/src/base/phyLayer \
    -I../../mixim-veins/src/base/connectionManager \
    -I../../mixim-veins/src/inet_stub/networklayer/common \
    -I. \
    -Iapplications \
    -Ibase \
    -Inodes \
    -Isensors \
    -Iutils

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../mixim-veins/out/$(CONFIGNAME)/src  -lmixim
LIBS += -Wl,-rpath,`abspath ../../mixim-veins/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/base/BaseSensor.o $O/base/BaseSensorAppl.o $O/sensors/Proximity.o

# Message files
MSGFILES =

# Other makefile variables (-K)
MIXIM_VEINS_PROJ=../../mixim-veins

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f wsn wsn.exe libwsn.so libwsn.a libwsn.dll libwsn.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f applications/*_m.cc applications/*_m.h
	$(Q)-rm -f base/*_m.cc base/*_m.h
	$(Q)-rm -f nodes/*_m.cc nodes/*_m.h
	$(Q)-rm -f sensors/*_m.cc sensors/*_m.h
	$(Q)-rm -f utils/*_m.cc utils/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc applications/*.cc base/*.cc nodes/*.cc sensors/*.cc utils/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/base/BaseSensor.o: base/BaseSensor.cc \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/Move.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/util/FWMath.h \
	base/BaseSensor.h \
	base/ISensor.h \
	utils/ConstantsWsn.h
$O/base/BaseSensorAppl.o: base/BaseSensorAppl.cc \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/Move.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/util/FWMath.h \
	base/BaseSensor.h \
	base/BaseSensorAppl.h \
	base/ISensor.h \
	base/ISensorApp.h \
	utils/ConstantsWsn.h
$O/sensors/Proximity.o: sensors/Proximity.cc \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_VEINS_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/Move.h \
	$(MIXIM_VEINS_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_VEINS_PROJ)/src/inet_stub/util/FWMath.h \
	base/BaseSensor.h \
	base/ISensor.h \
	sensors/Proximity.h \
	utils/ConstantsWsn.h

