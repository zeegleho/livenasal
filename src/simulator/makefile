
.PHONY:$(preobj)
preobj = $(LIBHOME)/simulator.pre

LIB = $(LIBHOME)/libsimulator.so
SRC =  simulator.cc simulatorEngine.cc SDBAccessor.cc createSpaceParticles.cc SDB.cc spaceParticle.cc SDBCreator.cc
LFLAGS +=  -L/usr/include/octave-3.8.1/octave -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -loctave -loctinterp -lutil -lm  -llapack -lblas -lreadline  -fPIC -Wl,-Bsymbolic-functions -Wl,-z,relro -g -O2 -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security -pthread -fopenmp  -shared -Wl,-Bsymbolic -D_FORTIFY_SOURCE=2 -M 

OCTSRC = octaveInterface.cc

$(OCTOBJ): $(OCTSRC)
	     mkoctfile $(OCTSRC) 

include ../variables/makefile.base

preobj:

