/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/
// edited by Jonathan Panah
#include "Instruction.h"

void slt_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "SLT") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters 
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is AND register, so param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is AND register, so param 3 needs to be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
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

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/
	// order before changes was, opcode funct Rd Rs Rt, so I fixed the order of them to the correct opcode Rs Rt Rd funct
	// I also changed the bit # from 20 for Rd to 15 and Rt from 15 to 20

	// Set the opcode
	setBits_num(31, 0, 6);		

	// Set the funct 
	setBits_str(5, "101010");

	// set Rd
	setBits_num(15, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM2.value, 5);

	// set Rt
	setBits_num(20, PARAM3.value, 5);

	// added in shamt
	setBits_num(10,0,5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void slt_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
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
	uint32_t Rd = getBits(15, 5);

	/*
		Setting Instuciton values
	*/

	setOp("SLT");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(2, REGISTER, Rs); //destination
	setParam(3, REGISTER, Rt); //first source register operand
	setParam(1, REGISTER, Rd); //second source register operand

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


	
