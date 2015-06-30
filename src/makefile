
include variables/makefile.variables
DIRS = console input simulator algorithm output messages utils debug
#OBJS = $(patsubst %,%.so, $(DIRS) )
OBJS = $(addsuffix .so, $(DIRS) )
#OBJS = console.so input.so simulator.so output.so messages.so utils.so
.PHONY:$(PREOBJS)
PREOBJS = $(addsuffix .pre, $(DIRS) )
BIN = $(BINHOME)/livenasal
MAIN = main.o

CC = g++
CFLAGS = -g -c -Wall -fPIC -I/usr/include/octave-3.8.1/ 
LFLAGS = -shared -lc
BINLFLAGS = -L/usr/include/octave-3.8.1/octave -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -loctave -loctinterp -lutil -lm  -llapack -lblas -lreadline -fPIC   

$(BIN): $(PREOBJS) $(OBJS) $(MAIN)
	@( echo "-------------link bin----------------";	    \
	)
	@( cd $(OBJHOME); )
	g++ -o $(BIN)  $(OBJHOME)/main.o $(BINLFLAGS) \
	-L$(LIBHOME) -lconsole \
	-L$(LIBHOME) -linput \
	-L$(LIBHOME) -lsimulator \
	-L$(LIBHOME) -lalgorithm \
	-L$(LIBHOME) -loutput \
	-L$(LIBHOME) -lutils \
	-L$(LIBHOME) -ldebug \
	-L$(LIBHOME) -lmessages  
	

$(MAIN): main.cc
	@(echo "-------------compile main-------------"; \
	$(CC) $(CFLAGS) main.cc -o main.o; \
	mv main.o $(OBJHOME) \
	)
$(PREOBJS): %.pre: %
	@(echo "-------------pre compile $<-------------"; \
	cd $<; \
	make preobj \
	)

$(OBJS): %.so: %
	@(echo "-------------compile $<-------------"; \
	cd $<; \
	make  \
	)
    

clean:
	@(  \
	cd $(SRCHOME)/console; make clean;make postclean;	\
	cd $(SRCHOME)/input; make clean;	\
	cd $(SRCHOME)/simulator; make clean;	\
	cd $(SRCHOME)/algorithm; make clean;	\
	cd $(SRCHOME)/output; make clean;	\
	cd $(SRCHOME)/messages; make clean;make postclean;	\
	cd $(SRCHOME)/utils; make clean;	\
	cd $(SRCHOME)/debug; make clean;	\
	cd $(SRCHOME)/; rm -rf $(MAIN);	\
	cd $(LIBHOME)/; rm -rf lib*.so *.o;	\
	cd $(OBJHOME)/; rm -rf *.o;	\
	cd $(OBJHOME)/; rm -rf *.cc;	\
	cd $(BINHOME)/; rm -rf livenasal;	\
	)



#g++ -o prog prog.o -L/path/to/my/library/folder -ldllname
