#include "MSC.h"

#include <stdio.h>

int sc_memory[SC_MEM_SIZE];
int sc_register;

int sc_memoryInit() {
    for (int i = 0; i < SC_MEM_SIZE; ++i) {
        sc_memory[i] = 0;
    }
    printf("\n *Memory init*  \n");
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address >= SC_MEM_SIZE) {
        sc_regSet(MEM_OUT, 1);
	printf("\n //ERROR MEM_OUT// \n");
        return 1;
    }
    sc_memory[address] = value;
    printf("\n *Memory set* \n");
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address < 0 || address >= SC_MEM_SIZE) {
        sc_regSet(MEM_OUT, 1);
		printf("\n //ERROR MEM_OUT// \n");
        return 1;
    }
    *value = sc_memory[address];
    printf("\n *Memory get* \n");
    return 0;
}

int sc_memorySave(char filename[]) {
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL) {
        return 1;
    }
    fwrite(&sc_memory, sizeof(sc_memory), 1, fp);
    fclose(fp);
    printf("\n *Memory save* \n");
    return 0;
}

int sc_memoryLoad(char filename[]) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        return 1;
    }
    fread(&sc_memory, sizeof(sc_memory), 1, fp);
    fclose(fp);
    printf("\n *Memory load* \n");
    return 0;
}

int sc_regInit() {
    sc_register = 0x0;
    printf("\n *Reg init* \n");
    return 0;
}

int sc_regSet(int reg, int value) {
    if (reg == MEM_OUT || reg == INVALID_REG || reg == WRONG_COMMAND) {
        if (value == 1) {
            sc_register |= reg;
        } else if (value == 0) {
            sc_register &= ~reg;
        } else {
            sc_register |= INVALID_REG;
            return 1;
        }
    }
    printf("\n *reg set* \n");
    return 0;
}

int sc_regGet(int reg, int *value) {
    if (reg < 1 || reg > REG_SIZE) {
        sc_regSet(INVALID_REG, 1);
	printf("\n ERROR INVALID_REG \n");
        return 1;
    }
    *value = (sc_register >> (reg - 1)) & 0x1;
    printf("\n *Reg get* \n");
    return 0;
}


int sc_commandEncode(int command, int operand, int *value) {
    if (command < 0x10 ||
        (command > 0x11 && command < 0x20) ||
        (command > 0x21 && command < 0x30) ||
        (command > 0x33 && command < 0x40) ||
        (command > 0x43 && command < 0x51) ||
        command > 0x76) {
        sc_regSet(WRONG_COMMAND, 1);
	printf("\n //ERROR WRONG_COMMAND// \n");
        return 1;
    }
    if (operand > 0x127 || operand < 0) {
        sc_regSet(WRONG_COMMAND, 1);
	printf("\n //ERROR WRONG_COMMAND// \n");
        return 1;
    }
    *value = (command << 7) | operand;
    	printf("\n *Command encode* \n");
    return 0;
}


int sc_commandDecode(int value, int *command, int *operand) {
    if ((value >> 14) != 0) {
        return 1;
    }
    *command = value >> 7;
    *operand = value & 0x7F;
    printf("\n *Command decode* \n");
    return 0;
}
