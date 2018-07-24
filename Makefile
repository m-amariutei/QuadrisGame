CXX = g++
CXXFLAGS = -MMD -g --std=c++11
EXEC = quadris
X11FLAGS = -lX11
OBJECTS = main.o interpreter.o quadrisboard.o level.o block.o cell.o display.o window.o BlockClasses/Iblock.o BlockClasses/Jblock.o BlockClasses/Lblock.o BlockClasses/Oblock.o BlockClasses/Sblock.o BlockClasses/Tblock.o BlockClasses/Zblock.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${X11FLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
