
.PHONY:$(preobj)
preobj = $(LIBHOME)/algorithm.pre
include ../variables/makefile.variables

LIB = $(LIBHOME)/libalgorithm.so
SRC =  algorithmInterface.cc  

#CFLAGS += -I/usr/include/octave-3.8.1/ -I/usr/include/octave-3.8.1/octave/
#LFLAGS += -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -L/usr/include/octave-3.8.1/octave -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -loctave -loctinterp -lutil 
#LFLAGS +=  -L/usr/include/octave-3.8.1/octave -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -loctave -loctinterp -lutil -lm  -llapack -lblas -lreadline  -fPIC -Wl,-Bsymbolic-functions -Wl,-z,relro -g -O2 -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security -pthread -fopenmp  -shared -Wl,-Bsymbolic -D_FORTIFY_SOURCE=2 -M  

OCTSRC = interP.cc curveFitting.cc 
OCTOBJ =  $(patsubst %.cc,%.oct, $(OCTSRC) )
TEMP1 =  $(addprefix algorithm/, $(OCTOBJ) ) 
OCTOBJ1 =  $(addprefix $(SRCHOME), $(TEMP1) ) 
#we should never move or rename the oct file after generated


CC = g++
CFLAGS = -g -c -Wall -fPIC  -std=c++11 -pthread -I/usr/include/octave-3.8.1/ -I/usr/include/octave-3.8.1/octave/
LFLAGS = -shared -lc  -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -L/usr/include/octave-3.8.1/octave -L/usr/lib/x86_64-linux-gnu/octave/3.8.1 -L/usr/lib/x86_64-linux-gnu -loctave -loctinterp -lutil -lm  -llapack -lblas -lreadline -fPIC 

OBJ =  $(patsubst %.cc,%.o, $(SRC) )
#OBJ =  $(addprefix $(LIBHOME), $(TEMP) )

$(LIB): $(OBJ) $(OCTOBJ)
	( cd $(OBJHOME);   \
	$(CC) $(LFLAGS) -o $(LIB) $(OBJ) $(OCTOBJ1); \
	)
$(OBJ): %.o: %.cc
	( $(CC) $(CFLAGS) $< -o $@;  \
	cp $@ $(OBJHOME);   \
	)
$(OCTOBJ): %.oct:%.cc 
	( mkoctfile $< ; \
	#cp $@ $(OBJHOME);  \
	)	
preobj:
	
clean: 
	@rm -rf *.o *.oct $(LIB)

