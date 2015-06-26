CC=g++
CFLAGS= -g -c -Wall -D__USE_FIXED_PROTOTYPES__ -lm -O3
#
# Compiler flags:
# -c -- Compile or assemble the source files, but do not link.
# -g -- Enable debugging
# -Wall -- Turn on all warnings 
# -D__USE_FIXED_PROTOTYPES__ -- Force the compiler to use the correct headers
# -ansi -- Don't use GNU extensions. Stick to ANSI C.
PROGRAM_NAME=tp_final_paa
CRIADOR=Vagner Clementino
PAA_LIB_PATH=./src/lib
SRC_FOLDER=./src/tp_final
BIN_DIR=./bin
IN_DIR=./inputs
OUT_DIR=./outputs
OBJS=$(SRC_FOLDER)/main.o \
	 $(PAA_LIB_PATH)/FileManager.o \
	 $(PAA_LIB_PATH)/PAAException.o \
	 $(PAA_LIB_PATH)/TrabalhoPratico.o \
	 $(SRC_FOLDER)/Edge.o \
	 $(SRC_FOLDER)/PAAGraph.o \
	 $(SRC_FOLDER)/TPFinal.o \
	 $(SRC_FOLDER)/Vertex.o
INPUTFILE=$(-i ../inputs/input.txt)
OUTPUTFILE=$(-o ../outputs/output.txt) 

all: app_structure msg_user linking $(BIN_DIR)/$(PROGRAM_NAME)
	@echo "Compilado com sucesso..."
	@rm -f $(OBJS) *.gch	
#@./$(BIN_DIR)/$(PROGRAM_NAME) $(INPUTFILE) $(OUTPUTFILE) -p all

app_structure:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(IN_DIR)
	@mkdir -p $(OUT_DIR)
	
msg_user:
	@echo "Compilando o programa " \
	 	  "$(PROGRAM_NAME) criado por $(CRIADOR)."
	
linking: $(OBJS)
	@$(CC) -o $(BIN_DIR)/$(PROGRAM_NAME) $(OBJS)
	@echo "Linking executado com sucesso."

main.o: $(SRC_FOLDER)/main.cpp
	@$(CC) $(CFLAGS) main.cpp

FileManager.o: $(PAA_LIB_PATH)/FileManager.h $(PAA_LIB_PATH)/FileManager.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/FileManager.cpp

PAAException.o: $(PAA_LIB_PATH)/PAAException.h $(PAA_LIB_PATH)/PAAException.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/PAAException.cpp

TrabalhoPratico.o: TrabalhoPratico.h TrabalhoPratico.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TrabalhoPratico.cpp

Edge.o: Edge.h Edge.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/Edge.cpp

Vertex.o: Vertex.h Vertex.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TPInstance.cpp

Graph.o: Graph.h
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/Graph.h
	
PAAGraph.o: PAAGraph.h PAAGraph.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/PAAGraph.cpp
	
TPFinal.o: TPGraph.h TPGraph.cpp
	@$(CC) $(CFLAGS) $(PAA_LIB_PATH)/TPFinal.cpp


	
clean:
	@echo "Removendo arquivos temporários e o executável..."
	@rm -f $(OBJS) *.gch $(PROGRAM_NAME)
	@echo "Arquivos removidos com sucesso."
