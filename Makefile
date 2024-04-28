# Nome do executável
EXECUTABLE = main

# Compilador
CC = g++

# Compilador flags
CFLAGS = -std=c++20 -Wall -Wextra -Ofast -MMD -flto -march=native -funroll-loops -fomit-frame-pointer -fprefetch-loop-arrays

# Diretório onde estão os arquivos-fonte
SRC_DIR = src

# Diretório para os arquivos-objeto
BUILD_DIR = build

# Diretório para o arquivo executável
BIN_DIR = bin

# Lista de pastas contendo arquivos-fonte
SOURCE_DIRS = buscasLocais estruturas guloso melhoria_servidor metaheuristicas perturbacoes problema servidor solucao

# Lista de arquivos-fonte em cada pasta
SOURCES = $(foreach dir,$(SOURCE_DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.cpp)) $(SRC_DIR)/main.cpp

# Nome dos arquivos-objeto gerados a partir dos arquivos-fonte
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Definições de cores
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# Compila os objetos e o executável
all: clean_dependencies create_build_dir $(OBJECTS)
	@printf "\nCompilando $(EXECUTABLE)...\n"
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/$(EXECUTABLE) $(OBJECTS)
	@printf "$(GREEN)Compilação concluída. O executável está em $(BIN_DIR)/$(EXECUTABLE)$(RESET)\n\n"

# Regra genérica para compilar arquivos-objeto a partir dos arquivos-fonte
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "Compilando $<...\n"
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -MM $< -MT $@ -MF $(BUILD_DIR)/$*.d > /dev/null 2>&1

# Executa o arquivo após a compilação
run:
	@if [ -f "$(BIN_DIR)/$(EXECUTABLE)" ]; then ./$(BIN_DIR)/$(EXECUTABLE); fi

# Cria a pasta build se não existir
# Cria todas as subpastas
create_build_dir:
	@mkdir -p $(BUILD_DIR)
	@$(foreach dir,$(SOURCE_DIRS),mkdir -p $(BUILD_DIR)/$(dir);)

# Limpa os arquivos de dependências
clean_dependencies:
	@printf "\nLimpando arquivos de dependências...\n"
	@rm -f $(OBJECTS:.o=.d)
	@printf "$(YELLOW)Limpeza de arquivos de dependências concluída. $(RESET)\n\n"

# Limpa tudo (objetos, arquivos de dependências e executável)
clean: clean_dependencies
	@printf "\nLimpando objetos...\n"
	@rm -f $(OBJECTS)
	@printf "$(YELLOW)Limpeza de objetos concluída. $(RESET)\n"
	@printf "\nLimpando o executável...\n"
	@rm -f $(BIN_DIR)/$(EXECUTABLE)
	@printf "$(YELLOW)Limpeza de executável concluída. $(RESET)\n"

# Limpa tudo e compila novamente
rebuild: clean all

# Compila e roda
i run: all run
