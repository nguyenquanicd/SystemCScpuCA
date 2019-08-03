scpu_top_inst->scpu_fetch_inst.mem_array[0] = 0b11100000; //LI R0, haa;
scpu_top_inst->scpu_fetch_inst.mem_array[1] = 0b10101010; //haa 
scpu_top_inst->scpu_fetch_inst.mem_array[2] = 0b11100100; //LI R1, h55;
scpu_top_inst->scpu_fetch_inst.mem_array[3] = 0b01010101; //h55
scpu_top_inst->scpu_fetch_inst.mem_array[4] = 0b11101000; //LI R2, h88;
scpu_top_inst->scpu_fetch_inst.mem_array[5] = 0b10001000; //h88 
scpu_top_inst->scpu_fetch_inst.mem_array[6] = 0b11101100; //LI R3, h99;
scpu_top_inst->scpu_fetch_inst.mem_array[7] = 0b10011001; //h99

scpu_top_inst->scpu_fetch_inst.mem_array[8] = 0b01110000; //NOP
scpu_top_inst->scpu_fetch_inst.mem_array[9] = 0b01110000; //NOP
scpu_top_inst->scpu_fetch_inst.mem_array[10] = 0b01110000; //NOP

scpu_top_inst->scpu_fetch_inst.mem_array[11] = 0b00000001; //AND R0, R1 => R0 = h00

scpu_top_inst->scpu_fetch_inst.mem_array[12] = 0b00011011; //OR R2, R3 => R2 = h99 

scpu_top_inst->scpu_fetch_inst.mem_array[13] = 0b00100110; //ADD R1, R2 => R1 = hee

scpu_top_inst->scpu_fetch_inst.mem_array[14] = 0b00111011; //SUB R2, R3 => R2 = h99 - h99 = h00

scpu_top_inst->scpu_fetch_inst.mem_array[15] = 0b01000000; //LWR R0, R0 => R0 = mem[R0] = mem[h00] = he0

scpu_top_inst->scpu_fetch_inst.mem_array[16] = 0b01010111; //SW R1, R3 => mem[R3] = mem[h99] = mem[153] = R1 = hee 

scpu_top_inst->scpu_fetch_inst.mem_array[17] = 0b01101100; //MOV R3, R0 => R3 = R0 = he0
scpu_top_inst->scpu_fetch_inst.mem_array[18] = 0b01110000; //NOP

scpu_top_inst->scpu_fetch_inst.mem_array[19] = 0b10000100; //JEQ R1, IMM
scpu_top_inst->scpu_fetch_inst.mem_array[20] = 0b11110000; //IMM = hf0 => Do not jump because R1 = hee
scpu_top_inst->scpu_fetch_inst.mem_array[21] = 0b11100100; //LI R1, IMM => R1 = h00
scpu_top_inst->scpu_fetch_inst.mem_array[22] = 0b00000000; //IMM = h00
scpu_top_inst->scpu_fetch_inst.mem_array[23] = 0b10000100; //JEQ R1, IMM
scpu_top_inst->scpu_fetch_inst.mem_array[24] = 0b00011010; //IMM = h1a = 26 => jump to mem[26]
scpu_top_inst->scpu_fetch_inst.mem_array[25] = 0b01100010; //MOV R0, R2 (do not execute because JEQ)

scpu_top_inst->scpu_fetch_inst.mem_array[26] = 0b10011000; //JNE R2, IMM => Do not jump because R2 = 0
scpu_top_inst->scpu_fetch_inst.mem_array[27] = 0b00011111; //IMM = h1f = 31
scpu_top_inst->scpu_fetch_inst.mem_array[28] = 0b00000010; //AND R0, R1  => R0 = he0 & h00 = h00
scpu_top_inst->scpu_fetch_inst.mem_array[29] = 0b10011100; //JNE R3, IMM => jump because R3 != 0
scpu_top_inst->scpu_fetch_inst.mem_array[30] = 0b00100000; //IMM = h1f = 32 => jump to mem[32]
scpu_top_inst->scpu_fetch_inst.mem_array[31] = 0b01100010; //MOV R0, R2 (do not execute because JEQ)

scpu_top_inst->scpu_fetch_inst.mem_array[32] = 0b10100010; //JGT R0, IMM => Do not jump because R0 = 0
scpu_top_inst->scpu_fetch_inst.mem_array[33] = 0b00101101; //IMM = 45
scpu_top_inst->scpu_fetch_inst.mem_array[34] = 0b11100000; //LI R0, h88;
scpu_top_inst->scpu_fetch_inst.mem_array[35] = 0b10001000; //R0 = h88
scpu_top_inst->scpu_fetch_inst.mem_array[36] = 0b10100000; //JGT R0, IMM => jump because R0 = h88 > 0
scpu_top_inst->scpu_fetch_inst.mem_array[37] = 0b00101101; //IMM = 45
//From [38] to [43], they are executed when jumping from [43] by JLT
scpu_top_inst->scpu_fetch_inst.mem_array[38] = 0b11001000; //LWI R2, IMM =>R2 = mem[40] = hd8
scpu_top_inst->scpu_fetch_inst.mem_array[39] = 0b00101000; //IMM = 40 = h28
scpu_top_inst->scpu_fetch_inst.mem_array[40] = 0b11011000; //SWI R2, IMM => mem[IMM] = mem[h3c] = mem[60] = R2 = hd8
scpu_top_inst->scpu_fetch_inst.mem_array[41] = 0b00111100; //IMM = h3c
scpu_top_inst->scpu_fetch_inst.mem_array[42] = 0b11110000; //JMP IMM => Jump to the start of the program [0]
scpu_top_inst->scpu_fetch_inst.mem_array[43] = 0b00000000; // IMM = 0
//End of program
//
scpu_top_inst->scpu_fetch_inst.mem_array[45] = 0b10110000; //JLT R0, IMM => Do not jump because R0 = h88 > 0
scpu_top_inst->scpu_fetch_inst.mem_array[46] = 0b11110000; //IMM = hf0
scpu_top_inst->scpu_fetch_inst.mem_array[47] = 0b00110100; //SUB R1, R0 => R1 = R1 - R0 = h00 - h88 = -h88 (R1[8] == 1)
scpu_top_inst->scpu_fetch_inst.mem_array[48] = 0b01100001; //MOV R0, R1 => R0 = R1 = -h88
scpu_top_inst->scpu_fetch_inst.mem_array[49] = 0b10110000; //JLT R0, IMM => Do not jump because R0 = -h88 < 0
scpu_top_inst->scpu_fetch_inst.mem_array[50] = 0b00100110; //IMM = 38 => jump to [38]
//END