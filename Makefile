CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = chess
OBJECTS = king.o queen.o bishop.o knight.o rook.o pawn.o piece.o player.o human.o computer.o graphicsdisplay.o textdisplay.o subject.o xwindow.o board.o controller.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 

# Note that -X11 tag has been removed for now

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

