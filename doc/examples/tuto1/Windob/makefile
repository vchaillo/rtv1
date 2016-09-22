#######################################
# Makefile Raytracing pour cygwin     #  
# avec librairies opengl32            #
#                                     #
# Dav Vador 10 Dec 2k++               #
#######################################

.PHONY: clean
.SUFFIXES:


#######################################
# constantes 
# librairies standards
LIBS =  -lm
# librairie opengl
LIBS += -lglut32 -lglu32 -lopengl32
# compilateur/editeur de liens
CC        =  gcc
CFLAGS    =  -O4 -W -g -Wall
LD        =  gcc
LDFLAGS   =  -g -s 
#######################################

#######################################
# cible principale
all: raytracing

# edition de liens du programme Raytracing
raytracing: main.o raytracing.o 3d.o import.o util.o
	$(LD) $(LDFLAGS) -o $@.exe $^ $(LIBS)

# compilation du programme main.c
main.o: main.c raytracing.o 3d.o import.o util.o infos_compilation.h
	$(CC) -c $(CFLAGS) -o $@ $<	

# compilation des differents modules
raytracing.o: raytracing.c raytracing.h infos_compilation.h 3d.o import.o util.o
	$(CC) -c $(CFLAGS) -o $@ $<
3d.o: 3d.c 3d.h infos_compilation.h util.o
	$(CC) -c $(CFLAGS) -o $@ $<
import.o: import.c import.h infos_compilation.h 3d.o
	$(CC) -c $(CFLAGS) -o $@ $<
util.o: util.c util.h
	$(CC) -c $(CFLAGS) -o $@ $<
#######################################

#######################################
clean:
	\rm -f *.o
	\rm -f *.exe
cl~:
	\rm -f *~
#######################################

