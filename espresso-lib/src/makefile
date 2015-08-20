#
# generic makefile 
#
# Usage make all | make clean
#



#---------------------------------------------------------------------------
# Declare vars

EXE = libespresso.a


CC		= gcc
CCFLAGS 	= -g
CCDEFINES 	= 
CCPATHS 	= -I../../include -I../../include/espresso

LD 		= gcc
LDPATHS		= -L.  -L../../lib/espresso
LDLIBS		= -lstdc++ -lespresso
LDFLAGS		= ${LDPATHS} ${LDLIBS}

AR		= ar
ARPATHS		=
ARLIBS		=
ARFLAGS		=


#---------------------------------------------------------------------------
# Build

OBJ = Args.o Arg.o StopWatch.o strings.o


all: ${OBJ}
	@echo Creating library...
	${AR} -r ${EXE} ${ARPATHS} ${OBJ} ${ARLIBS} 




#---------------------------------------------------------------------------
# Clean

clean: 
	@echo Cleaning... 
	rm -f *.o *.a core
	rm -f ${EXE}
	@echo Done! 





#---------------------------------------------------------------------------
# Build Instructions

.SUFFIXES: .C 

.C.o:
	@echo Compiling '$<'...
	$(CC) -c $< $(CCFLAGS) $(CCDEFINES) $(CCPATHS)

.SUFFIXES: .cxx
.cxx.o:
	@echo Compiling '$<'...
	$(CC) -c $< $(CCFLAGS) $(CCDEFINES) $(CCPATHS)

