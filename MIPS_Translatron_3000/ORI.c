/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edited by Lauren Taylor
*/

#include "Instruction.h"

void ori_immd_assm(void) {
	// Checking that the opcode matches
	// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "ORI") != 0) {
		// If the result is not 0, the opcode is not ORI
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking types of parameters
		ORI has two registers and one immediate field
	*/

	// First parameter is the destination register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Second parameter is the source register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Last parameter is an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of the parameters
		The registers are 32-bit fields and the immediate is 16-bits
	*/

	// Rd should be 31 or less 
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, so 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001101");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set immediate
	setBits_num(15, PARAM3.value, 16);

	// Let the system know that the encoding is done
	state = COMPLETE_ENCODE;
}

void ori_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "001101") != 0) {
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
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instruction values
	*/

	setOp("ORI");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, IMMEDIATE, imm16); //immediate operand


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}




