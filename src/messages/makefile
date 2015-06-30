.PHONY:preobj 
preobj = $(LIBHOME)/messages.pre
LIB = $(LIBHOME)/libmessages.so
SRC =  messageInterface.cc messages.cc messageDef.cc procInfo.cc
include ../variables/makefile.base

preobj: messages.cc

messages.cc : messages.def messageGenerator.pl
	@( ./messageGenerator.pl $(LIVENASALHOME) ) 

.PHONY:postclean
postclean: 
	@rm -rf messages.cc  messages.h messagesMacros.h 
