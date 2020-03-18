# source object target
SRCS   = dllwrapper.c dllmain.cpp cluster_expansion.c complex.c \
normalizer.c operator_tree.c position_tree.c solver.c static_dtree.c
OBJS   = dllwrapper.o dllmain.o cluster_expansion.o complex.c \
normalizer.o operator_tree.o position_tree.o solver.o static_dtree.o
TARGET = dsdll.dll
	
CC       = gcc
LIBS     = -static -lgmp
LDFLAGS  =
DEFINES  =
INCLUDE  = -I.
CFLAGS   = -m64 -O2 -finput-charset=UTF-8 -fexec-charset=UTF-8
CXXFLAGS =

build: $(OBJS)
	$(CC) -shared -fPIC -o $(TARGET) $(OBJS) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ $(LIBS)
	
.PHONY: clean
clean:
	del *.o
	