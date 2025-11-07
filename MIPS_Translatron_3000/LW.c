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
	// Param 1 should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// Param 2 needs to be a register	// Parameters were not in the correct Order, 
	if (PARAM2.type != REGISTER) {		// Now Register field parameter is checked accordingly
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
	if ( PARAM2.value > 31) {			// Because Param 1 and 2 are the register fields (5 bits) they need to be less then 32
		state = INVALID_REG;
		return;
	}
	// The immediate value is limited to 16 bits, this is 0xFFFF
	if ( PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;			// Because Param 3 is an immediate field, it needs to be less than 65535 or "1111 1111 1111 1111" 
		return;							// 0x7FFF != 65535 			0xFFFF = 65535
	}
	
	//encode instruction 
	setBits_str(31, "100011");
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM2.value, 5);		// Param 2 is the reg field, therefore 2 and 3 needed to be swapped
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
	setParam(2, REGISTER, Rs);			// Param 2 is the reg field, therefore 2 and 3 needed to be swapped
	setParam(3, IMMEDIATE, imm16);

	// tell the system the decoding is done
	state = COMPLETE_DECODE;

}
