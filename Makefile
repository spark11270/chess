CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = chess
OBJECTS = king.o queen.o bishop.o knight.o rook.o pawn.o piece.o textdisplay.o subject.o board.o cell.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

# Note that -X11 tag has been removed for now

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

