CXX = g++
CXXFLAGS = -MMD -g --std=c++11
EXEC = quadris
X11FLAGS = -lX11
OBJECTS = main.o interpreter.o quadrisboard.o level.o block.o cell.o display.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${X11FLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
