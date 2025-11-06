/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edited By: Aliaksei Sapatsko
*/

#include "Instruction.h"

void sw_immd_assm(void) {
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// setBits_str(31, "101010");
	// setBits_num(15, PARAM1.value, 5);
	// setBits_num(25, PARAM2.value, 16);
	// setBits_num(20, PARAM3.value, 5);

	// I Format: op, rs, rt, immediate

	setBits_str(31, "101011"); //opcode
	setBits_num(20, PARAM1.value, 5); //rt (what we're storing)
	setBits_num(15, PARAM2.value, 16); //offset/immediate
	setBits_num(25, PARAM3.value, 5); //rs (target address)

	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {

	// check opcode bits
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find values in binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	// set instruction values 
	setOp("SW");
	setParam(1, REGISTER, Rt); 
	setParam(2, IMMEDIATE, offset); //offset is param 2
	setParam(3, REGISTER, Rs); 

	state = COMPLETE_DECODE;
}
