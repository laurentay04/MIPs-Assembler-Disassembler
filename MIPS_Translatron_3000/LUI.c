/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/
// edited by Jonathan Panah

#include "Instruction.h"

void lui_immd_assm(void) {
	// If op code does not match "LUI" operation, then give an error for wrong command
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
	Checking the type of parameters
	*/

	// PARAM 1 must be a register, or else throw error
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	
	// Removed extra PARAM type that corresponded with Rs, since LUI does not need Rs
	// PARAM 2 must be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}
	// PARAM 1 must be 31 or less to be within range
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//removed original PARAM2 value test
	// PARAM 2 must be limited to 16 bits / less than or equal to 0xFFFF
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
	Putting the binary together
	*/
	// set opcode
	setBits_str(31, "001111");
	// set Rt
	setBits_num(20, PARAM1.value, 5); 
	// set Rs to 0
	setBits_num(25, 0, 5);
	// Set immediate
	setBits_num(15, PARAM2.value, 16); //  changed from PARAM3 to PARAM2

	// tell system that encoding is finished
	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	// check if the op code bits match the required op code for the function LUI
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	// if op code bits match, then the rest will be read correct

	/*
	Finding values in the binary
	*/

	// removed uint32_t Rs since it is not used
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
	Setting instruction values
	*/

	setOp("LUI");
	// setCond_num(cond)
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); 			// destination
	setParam(2, IMMEDIATE, imm16); 		// first source register

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}
