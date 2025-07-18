# Nome do compilador que será usado
CC = gcc

# Flags de compilação:
# -g   -> Inclui informações de debug no executável (para usar com um depurador)
# -Wall -> Mostra todos os avisos (warnings) de compilação, o que é uma boa prática
CFLAGS = -g -Wall

# Nome do arquivo executável que será gerado
TARGET = arq-sim

# Lista de todos os arquivos de código-fonte (.c) do seu projeto
SOURCES = arq-sim.c cpu.c lib.c

# Gera automaticamente a lista de arquivos objeto (.o) a partir da lista de fontes
OBJECTS = $(SOURCES:.c=.o)

# Regra principal: é executada quando você digita apenas "make" no terminal
# Ela diz que para criar "all", é preciso primeiro criar o TARGET
all: $(TARGET)

# Regra para criar o executável final (o TARGET)
# Ela diz que o TARGET depende dos arquivos .o
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra genérica para compilar qualquer arquivo .c em um arquivo .o
# Ela diz que um arquivo .o depende do seu arquivo .c correspondente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra "clean": usada para apagar os arquivos gerados pela compilação
# Você pode executá-la com o comando "make clean"
clean:
	rm -f $(TARGET) $(OBJECTS)