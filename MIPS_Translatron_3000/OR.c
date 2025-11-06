/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/
// edited by Jonathan Panah
#include "Instruction.h"

void or_reg_assm(void) {
	// check to make sure OR operator was called
	if (strcmp(OP_CODE, "OR") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// verify parameters
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//  verify parameters are within range (less than 31)
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	setBits_str(31, "000000");		// changed from (31,0,6) -> (31, "000000") 
		                            // changed from setBits_num to setBits_str
									// reordered the the code so that it goes from bit 31 and
									// sequentially goes down to 5, rather than from 31 to 5 to 15 to 25 to 20
	setBits_num(25, PARAM2.value, 5);
	setBits_num(20, PARAM3.value, 5);
	setBits_num(15, PARAM1.value, 5);
	setBits_str(5, "100101");


	state = COMPLETE_ENCODE;
}

void or_reg_bin(void) {
	// check if opcode and function match for OR
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);		//reordered for organization
	uint32_t Rd = getBits(15, 5);

	setOp("OR");

	setParam(1, REGISTER, Rd); 
	setParam(2, REGISTER, Rs); 	
	setParam(3, REGISTER, Rt); 

	state = COMPLETE_DECODE;
}


