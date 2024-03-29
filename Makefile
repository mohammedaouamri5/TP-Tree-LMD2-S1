# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x86
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x86)
  TP_config = debug_x86

else ifeq ($(config),debug_x86_64)
  TP_config = debug_x86_64

else ifeq ($(config),release_x86)
  TP_config = release_x86

else ifeq ($(config),release_x86_64)
  TP_config = release_x86_64

else ifeq ($(config),dist_x86)
  TP_config = dist_x86

else ifeq ($(config),dist_x86_64)
  TP_config = dist_x86_64

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := TP

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

TP:
ifneq (,$(TP_config))
	@echo "==== Building TP ($(TP_config)) ===="
	@${MAKE} --no-print-directory -C . -f TP.make config=$(TP_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f TP.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x86"
	@echo "  debug_x86_64"
	@echo "  release_x86"
	@echo "  release_x86_64"
	@echo "  dist_x86"
	@echo "  dist_x86_64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   TP"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"