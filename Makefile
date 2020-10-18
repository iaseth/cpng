AMP = @

AR = ${AMP}ar

CC = ${AMP}gcc
CC_FLAGS = -fPIC -Wall

INCLUDE_FLAG = -Iinclude
LINK_FLAG = -lpng

RM = ${AMP}rm -f

CPNG_MODULE_NAMES = 
CPNG_MODULE_NAMES += cpng_common
CPNG_MODULE_NAMES += cpng
CPNG_MODULE_NAMES += cpng_color
CPNG_MODULE_NAMES += cpng_cursor
CPNG_MODULE_NAMES += cpng_env
CPNG_MODULE_NAMES += cpng_image

CPNG_OBJ_NAMES = ${addsuffix .o, ${CPNG_MODULE_NAMES}}
CPNG_OBJS = ${addprefix build/obj/, ${CPNG_OBJ_NAMES}}

CPNG_STATIC_LIB = build/libcpng.a
CPNG_DYNAMIC_LIB = build/libcpng.so

CPNG_APP_NAMES = 
CPNG_APP_NAMES += quad
CPNG_APP_NAMES += tiles

CPNG_APP_EXE_PATHS = ${addsuffix .out, ${CPNG_APP_NAMES}}
CPNG_APP_EXES = ${addprefix build/app/, ${CPNG_APP_EXE_PATHS}}

MAIN_SRC = src/main.c
MAIN_OBJ = build/main.o

BIN = build/cpng

default: ${BIN}

debug:
	${eval AMP := }

${MAIN_OBJ}: ${MAIN_SRC}
	${CC} -c $< -o $@ ${INCLUDE_FLAG}

${CPNG_OBJS}: build/obj/%.o: lib/%.c include/%.h
	${CC} -c ${CC_FLAGS} $< -o $@ ${INCLUDE_FLAG}

${CPNG_STATIC_LIB}: ${CPNG_OBJS}
	${AR} rcs $@ $^

${CPNG_DYNAMIC_LIB}: ${CPNG_OBJS}
	${CC} -shared $^ -o $@

${BIN}: ${MAIN_OBJ} ${CPNG_STATIC_LIB}
	${CC} $^ -o $@ ${LINK_FLAG}

${CPNG_APP_EXES}: build/app/%.out: app/%.c ${CPNG_STATIC_LIB}
	${CC} $^ -o $@ ${INCLUDE_FLAG} ${LINK_FLAG}

app: ${CPNG_APP_EXES}

lib: ${CPNG_STATIC_LIB} ${CPNG_DYNAMIC_LIB}

redo: clean default

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${CPNG_STATIC_LIB}
	${RM} ${CPNG_DYNAMIC_LIB}
	${RM} ${MAIN_OBJ}
	${RM} ${CPNG_OBJS}


