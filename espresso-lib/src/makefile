#
# generic makefile 
#
# Usage make all | make clean
#



#---------------------------------------------------------------------------
# Declare vars

EXE = libespresso.a


CC			= gcc
CCFLAGS 	= -g
CCDEFINES 	= 
CCPATHS 	= -I./include -I./include/espresso
CCPATHS 	= -I../include -I../include/espresso

SRCDIR 		= src

LD 			= gcc
LDPATHS		= -L.  -L../../lib/espresso
LDLIBS		= -lstdc++ -lespresso
LDFLAGS		= ${LDPATHS} ${LDLIBS}

AR			= ar
ARPATHS		=
ARLIBS		=
ARFLAGS		=

OBJDIR		= ./obj 
OUTPUTDIR	= ./lib


#---------------------------------------------------------------------------
# source


OBJ =  Args.o stdhdr.o Arg.o IArgMgr.o ArgMgr.o ArgMgrCLI.o espresso.o StopWatch.o strings.o sys.o time.o 


# we expect to find our source code in a 'src' folder
#OBJS = $(patsubst %,$(OBJDIR)/%,$(OBJS))



#---------------------------------------------------------------------------
# Build targets


#all: ${SRCDIR}/${OBJ}
all: ${OBJ}
	@echo Creating library...
	${AR} -r ${EXE} ${ARPATHS} ${OBJ} ${ARLIBS} 
	#${AR} -r ${OUTPUTDIR}/${EXE} ${ARPATHS} ${OBJDIR}/${OBJS} ${ARLIBS} 


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



#---------------------------------------------------------------------------
# Clean

clean: 
	@echo Cleaning... 
	
	@echo Cleaning target output
	#rm -f ${OUTPUTDIR}/${EXE}
	#rm -f ${OBJDIR}/*.o
	@echo Cleaning object code...
	rm -f *.o *.a 
	@echo Remove any core dumps...
	rm -f core
	#rm -f ${OBJDIR}/*.o
	@echo Done! 



