CXX = g++
CFLAGS = -g -O2 -DDEBUG -std=c++0x #-Wall

LFLAGS = -lm

OBJS = Registro.o Utils.o Dados.o

MKDIR_P = mkdir -p
OUT_DIR=bin
PREFIX_OBJS = $(patsubst %.o,${OUT_DIR}/%.o,$(OBJS)) ${OUT_DIR}/main.o

EXEC = programa

all: ${OUT_DIR} $(EXEC)

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

%.o: src/%.cpp
	@echo "Compilando $@"
	@$(CXX) $(CFLAGS) -c $< -o ${OUT_DIR}/$@

main.o: main.cpp
	@echo "Compilando $@"
	@$(CXX) $(CFLAGS) -c $< -o ${OUT_DIR}/$@


$(EXEC): $(OBJS) main.o
	@echo "\nLinkando $(EXEC)\n"
	@$(CXX) -o ${OUT_DIR}/$(EXEC) $(PREFIX_OBJS)  $(LFLAGS)

clean:
	@echo "Limpando..."
	@rm -f $(PREFIX_OBJS) ${OUT_DIR}/$(EXEC) *~

