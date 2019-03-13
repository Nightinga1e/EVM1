#include "MSC.h"

#include <stdio.h>

int main() {
    sc_regInit();
    sc_memoryInit();
    sc_memorySet(10, 45);
    int cell;
    sc_memoryGet(10, &cell);
    printf("\n memory cell value = %d\n", cell);
    
    sc_memorySave("save.bin");
    sc_memoryLoad("save.bin");

    sc_regSet(MEM_OUT, 1);
    int val;
    sc_regGet(1, &val);
    printf("\n flag value - %d\n", val);
    
    sc_commandEncode(0x56, 0x60, &val);
    int command;
    int oper;
    sc_commandDecode(val, &command, &oper);
    printf("\n command - %x \n", command);
    printf("\n operand - %x \n", oper);
}
