/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/


#include "Instruction.h"

void lui_immd_assm(void) {
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}											// Removed extra PARAM type that corresponded with Rs, since LUI does not need Rs
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//removed original PARAM2 value test
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	setBits_str(31, "001111");			// opcode
	setBits_num(20, PARAM1.value, 5); // rt
	setBits_num(25, 0, 5);			// changed PARAM2.value to 0 because Rs is 0 for LUI
	setBits_num(15, PARAM2.value, 16); // immediate (changed from PARAM3 to PARAM2)

	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	// removed uint32_t Rs since it is not used
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	setOp("LUI");

	setParam(1, REGISTER, Rt); 
	setParam(2, IMMEDIATE, imm16); 

	state = COMPLETE_DECODE;
}
