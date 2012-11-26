CXX    = g++
CFLAGS = -Wall -g

ifeq ($(shell uname), Darwin)
    LIBS = -framework GLUT -framework OpenGL -framework Cocoa
else
    LIBS = -lglut -lGL -lGLU -lGLEW
endif

FREEGLUT = /afs/nd.edu/user37/ccl/software/external/freeglut
ifneq "$(wildcard $(FREEGLUT))" ""
    INCPATH += -I$(FREEGLUT)/include
    LIBPATH += -L$(FREEGLUT)/lib -Wl,--rpath -Wl,$(FREEGLUT)/lib
endif

GLEW = /afs/nd.edu/user37/ccl/software/external/glew
ifneq "$(wildcard $(GLEW))" ""
    INCPATH += -I$(GLEW)/include
    LIBPATH += -L$(GLEW)/lib -Wl,--rpath -Wl,$(GLEW)/lib
endif

all: hw6

clean:
	rm -f *.o hw6

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) -MM *.cpp >> Makefile

.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

hw6: main.o car.o porsche944.o police.o skybox.o camera.o moneyCrate.o
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

# DEPENDENCIES
main.o: main.cpp
car.o: car.cpp
porsche944.o: porsche944.cpp
police.o: police.cpp
skybox.o: skybox.cpp
camera.o: camera.cpp
moneyCrate.o: moneyCrate.cpp
