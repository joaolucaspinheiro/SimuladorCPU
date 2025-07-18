#include <stdint.h>
#include <stdbool.h>
#define MEM_SIZE 65536
#define NUM_REGISTERS 8

typedef struct
{
	uint16_t registrador[NUM_REGISTERS]; // Registradores da CPU
	uint16_t pc;					   // contador da instrução
	uint16_t instrucao;				   // Instrução atual.
	uint16_t operador1;				   // primeiro operando da instrução atual.
	uint16_t operador2;				   // segundo operando da instrução atual.
	uint16_t destino;				   // Registrador de destino da instrução atual.
	uint16_t opcode;				   // Operação da instrução atual.
	uint16_t formato;				   // Formato da instrução (R ou I)
	bool ativo;						   // Controla o loop principal da simulação.	
} Cpu;
void procurar(Cpu *cpu);	// Procurar uma nova instrução
void decodificar(Cpu *cpu); // Decodificar a instrução atual
void executar(Cpu *cpu);	// Executar a instrução atual
void cpu_iniciar(Cpu *cpu); // Inicializar a CPU
