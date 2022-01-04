CC = gcc
EXE = p1
EXE_1 = p2
C_EXT =*.c
EXE_EXT =*.o
RMVER= rm -f

default:
	${CC} -o ${EXE} program_1${C_EXT}
	${CC} -o ${EXE_1} program_2${C_EXT}
clean:
	${RMVER} ${EXE} ${EXE_EXT}
	${RMVER} ${EXE_1} ${EXE_EXT}
	${RMVER} SOCKP1
	${RMVER} SOCKP2