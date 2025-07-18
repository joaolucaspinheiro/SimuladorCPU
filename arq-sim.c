#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
#include "lib.h"
extern uint16_t memoria[MEM_SIZE];
int main(int argc, char **argv)

// Verificando se o nome do arquivo foi passado como argumento
{
	if (argc != 2)
	{
		printf("usage: %s [bin_name]\n", argv[0]);
		exit(1);
	}
	// Carregando o programa na memoria
	load_binary_to_memory(argv[1], memoria, MEM_SIZE);
	// Inicializando a CPU
	Cpu cpu;
	cpu_iniciar(&cpu);
	while (cpu.ativo)
	{
		procurar(&cpu);
		decodificar(&cpu);
		executar(&cpu);
	}
	printf("Simulacao concluida.\n");

	for (int i = 0; i < NUM_REGISTERS; i++)
	{
		printf("O Valor final no R[%d] = %d\n", i, cpu.registrador[i]);
	}
	return 0;
}