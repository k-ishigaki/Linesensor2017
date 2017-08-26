# commands depend on OS
ifeq ($(OS),Windows_NT)
# /Q option is force remove (no confirmation)
	RM = del /Q
	MKDIR = mkdir
	FixPath = $(subst /,\,$1)
# microchip mdb script file location
	MDB = "C:\Program Files (x86)\Microchip\MPLABX\v3.00\mplab_ide\bin\mdb.bat"
# TEMP redirect target
	TEMP_TARGET = $(TEMP)\microchip_mdb.log
# source files
	SRCS = $(shell dir /s /b)
	SRCS := $(patsubst $(shell cd)\\%,%,$(SRCS))
	SRCS := $(subst \,/,$(SRCS))
	SRCS := $(filter %.c,$(SRCS))
else
# -f option is force remove (no confirmation)
	RM = rm -f
	MKDIR = mkdir -p
	FixPath = $1
# microchip mdb script file location
	MDB = /opt/microchip/mplabx/mplab_ide/bin/mdb.sh
# TEMP redirect target
	TEMP_TARGET = /tmp/microchip_mdb.log
# source files
	SRCS = $(shell find  * -name *.c)
endif

# processor name
PROSESSOR_NAME := 16F1825
# include paths
INCLUDE_DIRS := ./src/application ./src/hardware
# compiler command
CC := xc8
# compiler options
CFLAGS := --chip=$(PROSESSOR_NAME) \
	$(addprefix -I,$(INCLUDE_DIRS)) \
	--stack=hybrid --asmlist --opt=default --ext=cci\
	--errformat="%f:%l:%c:%n:%s" --warnformat="%f:%l:%c:%n:%s" --msgdisable=1273
# target directory
TARGET_DIR := bin
# target file
TARGET := $(TARGET_DIR)/release.hex
# Link options
LDFLAGS := 
# library paths
LIBS := 
# object files
OBJS := $(addprefix $(TARGET_DIR)/,$(SRCS:%.c=%.p1))
# intermediate files directory
OBJ_DIRS := $(dir $(OBJS))
# dependency
DEPS := $(OBJS:%.p1=%.d)
# MDB script file
MDB_SCRIPT := ./mdb.prog

# additional suffixes
.SUFFIXES: .p1

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) --outdir=$(TARGET_DIR) -O$(call FixPath,$@) $(call FixPath,$^)

$(TARGET_DIR)/%.p1:%.c
ifeq ($(OS),Windows_NT)
	@if not exist $(call FixPath,$(@D))\ ($(MKDIR) $(call FixPath,$(@D)))
else
	@[ -d $(@D) ] || $(MKDIR) $(@D)
endif
	$(CC) $(CFLAGS) --outdir=$(call FixPath,$(@D)) --pass1 $(call FixPath,$<)

.PHONY: all
all: clean $(TARGET)

.PHONY: clean
clean:
# remove intermediate files
	$(RM) $(call FixPath,$(OBJS))
	$(RM) $(call FixPath,$(DEPS))
	$(RM) $(call FixPath,$(OBJS:%.p1=%.pre))
	$(RM) $(call FixPath,$(TARGET_DIR)/release.*)
	$(RM) $(call FixPath,$(TARGET_DIR)/startup.*)
	$(RM) $(call FixPath,$(TARGET_DIR)/doprnt.*)
	$(RM) $(call FixPath,MPLABXLog.*)
	$(RM) funclist l.obj

.PHONY: prog
prog: $(TARGET)
# it is nesessary to press Enter for MDB programing(windows MDB bug)
	$(info prease press Enter to program to device!!!)
	@$(MDB) $(call FixPath,$(MDB_SCRIPT)) > $(TEMP_TARGET) 2>&1
# remove unuse intermediate files
	$(RM) MPLABXLog.*

.PHONY: debug
debug:
	echo $(SRCS)

-include $(DEPS)
