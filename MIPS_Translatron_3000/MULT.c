/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Implemented By: Aliaksei Sapatsko
*/

#include "Instruction.h"

void mult_reg_assm(void) {
	if (strcmp(OP_CODE, "MULT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check params rs and rt
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// create binary
	//R-type: op, rs, rt, shamt, funct

	// Set the opcode
	setBits_str(31, "000000"); //opcode

	// Set rs
	setBits_num(25, PARAM1.value, 5); //rs

	// Set rt
	setBits_num(20, PARAM2.value, 5); //rt

	// Set other bits to 0000000000 shamt
	setBits_num(15, 0, 10);

	// Set the funct
	setBits_str(5, "011000"); //funct

	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	// Check if opcode bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);


	/*
		Setting Instruciton values
	*/

	setOp("MULT");
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);
	
	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


