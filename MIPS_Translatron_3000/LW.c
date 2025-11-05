/*
* Author: Ol' Jim
* Date: circa - 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edited By: Matt C. 
*/

#include "Instruction.h"

void lw_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {

		state = WRONG_COMMAND;
		return;
	}
	
	/*
		Checking the type of parameters
	*/
	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// Rs should be 31 or less
	if ( PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	// The immediate value is limited to 16 bits, this is 0xFFFF
	if ( PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	
	//encode instruction 
	setBits_str(31, "100011");
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM2.value, 5);
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {

	//check op code 
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instuciton values
	*/
	setOp("LW");
	setParam(1, REGISTER, Rt);
	setParam(2, REGISTER, Rs);
	setParam(3, IMMEDIATE, imm16);

	// tell the system the decoding is done
	state = COMPLETE_DECODE;

}
