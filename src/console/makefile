
.PHONY:preobj
preobj = $(LIBHOME)/console.pre
LIB = $(LIBHOME)/libconsole.so
SRC =  global.cc console.cc liveNasal.cc optionDef.cc options.cc performanceInfo.cc simulationController.cc performance.cc 

include ../variables/makefile.base

preobj: options.cc

options.cc: options.def optionGenerator.pl
	@( ./optionGenerator.pl $(LIVENASALHOME) ) 

.PHONY: postclean
postclean: 
	@rm -rf options.cc  options.h optionsMacros.h 
