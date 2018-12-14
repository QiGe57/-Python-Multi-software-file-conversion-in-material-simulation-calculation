# Standard makefile for OpenPhase executable

.PHONY : all clean cleanall

DEPTH = ../..

# ---------------------------------------------------------------------
# Exclude list, i.e. a.cpp b.cpp x.cpp. Will be passed to submakefiles
export EXCLUDE = MultiGrainPlasticStraining.cpp
# ---------------------------------------------------------------------

SRC := $(wildcard *.cpp)
SRC := $(filter-out $(EXCLUDE), $(SRC))
PROGS := $(basename $(SRC))

include ../Makefile.defs

all: $(PROGS)

%: %.cpp $(SRC) $(LIBSRC) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LDFLAGS) $(LIBSOP) $(STDLIBS)

clean:
	rm -f *.bak *.o .g* .d* $(PROGS)

cleanall:
	rm -f *.bak *.o .g* .d* $(PROGS)
	rm -r VTK/
	rm -r RawData/