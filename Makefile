AMP = @

GCC = ${AMP}gcc
INCLUDE_FLAG = -Iinclude
LINK_FLAG = -lpng

RM = ${AMP}rm -f

CPNG_NAMES = 
CPNG_NAMES += cpng_common

CPNG_OBJ_NAMES = ${addsuffix .o, ${CPNG_NAMES}}
CPNG_OBJS = ${addprefix build/, ${CPNG_OBJ_NAMES}}

MAIN_SRC = src/main.c
MAIN_OBJ = build/main.o

BIN = build/cpng

default: ${BIN}

debug:
	${eval AMP := }

${MAIN_OBJ}: ${MAIN_SRC}
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${CPNG_OBJS}: build/%.o: src/%.c include/%.h
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${BIN}: ${MAIN_OBJ} ${CPNG_OBJS}
	${GCC} $^ -o $@ ${LINK_FLAG}

redo: clean default

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${MAIN_OBJ}
	${RM} ${CPNG_OBJS}


