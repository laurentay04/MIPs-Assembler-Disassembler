/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edited by Lauren Taylor
*/

 #include "Instruction.h"

void andi_immd_assm(void) {
	// Checking the opcode matches
	// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "ANDI") != 0) {
		// If they do not match, this is the wrong command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking type of parameters
	*/

	// The first parameter is usually a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is ANDI so the second parameter should also be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is ANDI so the last parameter is an immediate value
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less since it is a 32 bit register
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rd should be 31 or less since it is a 32 bit register
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
	setBits_str(31, "001100");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rd
	setBits_num(25, PARAM2.value, 5);

	// Set immediate
	setBits_num(15, PARAM3.value, 16);

	// Let the system know that the encoding is done
	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// Check if the opcode bits match
	// checkBits(start_bit, bit_string) returns 0 if the bit_string matches
	// 	any x will be skipped
	// If the manual shows (0), then the value of that bit doesn't matter
	if (checkBits(31, "001100") != 0 ) {
		// If the bits do not match then it is the wrong command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in binary
	*/

	// get binary values with getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("ANDI");
	// setCond_num(cond)
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination register
	setParam(2, REGISTER, Rs); // source register operand
	setParam(3, IMMEDIATE, imm16); // immediate value operand
	
	// Tell the system that the decoding is done
	state = COMPLETE_DECODE;
}




