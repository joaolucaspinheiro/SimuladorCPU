#include <stdio.h>
#include "cpu.h"
#include "lib.h"

uint16_t memoria[MEM_SIZE];

void procurar(Cpu *cpu)
{
	cpu->instrucao = memoria[cpu->pc];
	printf("\n[FETCH] PC: %d, Instrucao lida: 0x%X\n", cpu->pc, cpu->instrucao);
	cpu->pc++;
}
void decodificar(Cpu *cpu)
{
	cpu->formato = extract_bits(cpu->instrucao, 15, 1);
	// Para instruções do tipo R
	if (cpu->formato == 0)
	{
		cpu->opcode = extract_bits(cpu->instrucao, 9, 6);
		cpu->destino = extract_bits(cpu->instrucao, 6, 3);
		cpu->operador1 = extract_bits(cpu->instrucao, 3, 3);
		cpu->operador2 = extract_bits(cpu->instrucao, 0, 3);
	}
	// Para instruções do tipo I
	else
	{
		cpu->opcode = extract_bits(cpu->instrucao, 13, 2);
		cpu->destino = extract_bits(cpu->instrucao, 10, 3);
		cpu->operador1 = extract_bits(cpu->instrucao, 0, 10);
		cpu->operador2 = 0;
	}
}

void executar(Cpu *cpu)
{
	switch (cpu->formato)
	{
	case 0: // Formato R
		printf("FORMATO R\n");
		{
			switch (cpu->opcode)
			{

			case 0:
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] + cpu->registrador[cpu->operador2]; // Adição
				printf("Adicao: R[%d] = R[%d] + R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 1:
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] - cpu->registrador[cpu->operador2]; // Subtração
				printf("Subtracao: R[%d] = R[%d] - R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 2:
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] * cpu->registrador[cpu->operador2]; // Multiplicação
				printf("Multiplicacao: R[%d] = R[%d] * R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 3:
				if (cpu->registrador[cpu->operador2] == 0)
				{
					printf("Erro: Divisao por zero\n");
					cpu->ativo = false; // Parar a CPU em caso de divisão por zero
					return;
				}
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] / cpu->registrador[cpu->operador2]; // Divisão
				printf("Divisao: R[%d] = R[%d] / R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 4:
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] == cpu->registrador[cpu->operador2]; // Comparação de igualdade
				printf("Comparacao de Igualdade: R[%d] = R[%d] == R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 5:
				cpu->registrador[cpu->destino] = cpu->registrador[cpu->operador1] != cpu->registrador[cpu->operador2]; // Comparação de desigualdade
				printf("Comparacao de Desigualdade: R[%d] = R[%d] != R[%d] = %d\n", cpu->destino, cpu->operador1, cpu->operador2, cpu->registrador[cpu->destino]);
				break;
			case 15:
				cpu->registrador[cpu->destino] = memoria[cpu->registrador[cpu->operador1]];
				printf("LOAD: R[%d] = M[R[%d]] = %d\n", cpu->destino, cpu->operador1, cpu->registrador[cpu->destino]);
				break;
			case 16:
				memoria[cpu->registrador[cpu->operador1]] = cpu->registrador[cpu->operador2];
				printf("STORE: M[R[%d]] = R[%d] = %d\n", cpu->operador1, cpu->operador2, cpu->registrador[cpu->operador2]);

				break;
			case 63:
				if (cpu->registrador[cpu->operador1] == 0)
				{
					cpu->ativo = false; // Instrução de parada
					printf("Instrucao para parada.\n");
				}
				break;
			default:
				printf("Instrucao desconhecida: %u\n", cpu->opcode);
				cpu->ativo = false; // Parar a CPU em caso de instrução desconhecida
				break;
			}
			break;
		}

	case 1: // Formato I
		printf("FORMATO I\n");
		switch (cpu->opcode)
		{
		case 0:						  // JUMP
			cpu->pc = cpu->operador1; // Pular para o endereço especificado
			printf("JUMP para o endereco: %d\n", cpu->pc);
			break;

		case 1: // // Jump Condicional
			switch (cpu->registrador[cpu->destino])
			{
			case 0:
				printf("Condição para JUMP nao atendida");
				break;
			case 1:
	
					cpu->pc = cpu->operador1; // Pular para o endereço especificado
					printf("JUMP condicional para o endereco: %d\n", cpu->pc);
					break;
			}
			break;
		case 2:
			cpu->ativo = false; // HALT
			printf("CPU parada.\n");
			break;
		case 3: // MOV
			cpu->registrador[cpu->destino] = cpu->operador1;
			printf("MOV: R[%d] = %d\n", cpu->destino, cpu->registrador[cpu->destino]);
			break;
		default:
			printf("Erro: Opcode do tipo I desconhecido: %u\n", cpu->opcode);
			cpu->ativo = false;
			break;
		}
	}
}
void cpu_iniciar(Cpu *cpu)
{
	for (int i = 0; i < NUM_REGISTERS; i++)
	{
		cpu->registrador[i] = 0;
	}
	cpu->pc = 0;
	cpu->instrucao = 0;
	cpu->operador1 = 0;
	cpu->operador2 = 0;
	cpu->destino = 0;
	cpu->opcode = 0;
	cpu->formato = 0;
	cpu->ativo = true; // True para iniciar o loop principal da simulação
}
