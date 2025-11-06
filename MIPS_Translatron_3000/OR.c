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

	/*
	Checking the type of parameters
	*/

	// First parameter must be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// Second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// Third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
	Checking value of parameters
	*/

	//  verify parameters are within range (less than 31)
	if (PARAM1.value > 31) {		// rd must be 31 or less
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {		// rs must be 31 or less
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 31) {		// rt must be 31 or less
		state = INVALID_REG;
		return;
	}

	/*
	Putting the binary together
	*/

	// set op code
	setBits_str(31, "000000");		// changed from (31,0,6) -> (31, "000000") 
		                            // changed from setBits_num to setBits_str
									// reordered the the code so that it goes from bit 31 and
									// sequentially goes down to 5, rather than from 31 to 5 to 15 to 25 to 20
	// set the rs
	setBits_num(25, PARAM2.value, 5);
	// set the rt
	setBits_num(20, PARAM3.value, 5);
	//set the rd
	setBits_num(15, PARAM1.value, 5);
	// set the funct
	setBits_str(5, "100101");

	// tell the system encoding is done
	state = COMPLETE_ENCODE;
}

void or_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
	Finding values in the binary
	*/
	// getBits(start_bit,width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);		//reordered for organization
	uint32_t Rd = getBits(15, 5);


	/*
	Setting Instruction values
	*/
	setOp("OR");
	// setCond_num(Cond)
	// setParam(param_num,param_type,param_value)
	setParam(1, REGISTER, Rd); 
	setParam(2, REGISTER, Rs); 	
	setParam(3, REGISTER, Rt); 

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


