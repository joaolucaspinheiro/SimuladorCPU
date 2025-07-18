# Simulador de CPU em C - Trabalho de Arquitetura de Computadores

## 💻 Sobre o Projeto

Este repositório contém o código-fonte de um simulador para uma arquitetura de CPU hipotética de 16-bits. O projeto foi desenvolvido em C para o componente curricular de **Arquitetura de Computadores**, ministrado pelo professor Eduardo Henrique Molina da Cruz.

O objetivo do trabalho é aplicar os conceitos teóricos de funcionamento de um processador, implementando o ciclo completo de busca, decodificação e execução de instruções. O simulador é capaz de executar um código de máquina customizado, fornecido em formato binário.

A implementação atual do processador segue o modelo **monociclo**, onde cada instrução é completada em um único ciclo de clock, separando as diferentes etapas de processamento de forma funcional.

---

## 🛠️ Conjunto de Instruções (ISA)

O simulador implementa o seguinte conjunto de instruções, conforme especificado nos requisitos do trabalho:

| Instrução | Descrição |
| :--- | :--- |
| `add` | Soma o valor de dois registradores. |
| `sub` | Subtrai o valor de dois registradores. |
| `mul` | Multiplica o valor de dois registradores. |
| `div` | Divide o valor de dois registradores. |
| `cmp_equal` | Compara se dois registradores são iguais, armazena 1 se verdadeiro. |
| `cmp_neq` | Compara se dois registradores são diferentes, armazena 1 se verdadeiro. |
| `load` | Carrega um valor da memória para um registrador. |
| `store` | Armazena um valor de um registrador na memória. |
| `jump` | Pula incondicionalmente para um endereço de memória. |
| `jump_cond` | Pula para um endereço se o valor no registrador de condição for 1. |
| `mov` | Move um valor imediato para um registrador. |
| `syscall` | Chama um serviço do sistema (Opcode 63, Tipo R). O serviço 0 (r0=0) encerra o programa. |

---

## 🚀 Como Compilar e Executar

### Ferramentas Necessárias
* **Assembler (`pasm`)**: Fornecido pelo professor para converter código `.asm` em `.bin`.
* **Compilador C (GCC)**: Necessário para compilar o código do simulador.
* **Make**: Utilizado para automatizar o processo de compilação.

### Passo a Passo

1.  **Montar o código Assembly:**
    Use o assembler `pasm` para gerar o arquivo binário a partir do seu código-fonte assembly.
    ```bash
    ./pasm seu_codigo.asm seu_codigo.bin
    ```
   

2.  **Compilar o Simulador:**
    Na pasta do simulador, utilize o `make` para compilar o projeto em C.
    ```bash
    make
    ```
   

3.  **Executar o Simulador:**
    Execute o simulador passando o arquivo binário gerado como argumento.
    ```bash
    ./arq-sim seu_codigo.bin
    ```
   

---

## 👥 Autores

* Brayan Mateus da Silva de Souza
* Giovana Lopes Eberle
* João Lucas Pinheiro de Oliveira
