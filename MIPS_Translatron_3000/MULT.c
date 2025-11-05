#include "Instruction.h"

/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edited By Aliaksei Sapatsko
*/

void mult_reg_assm(void) {
	if (strcmp(OP_CODE, "MULT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check params 
	// we only have 2 registers $rs and $rt as per the MIPS inctruction
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
	setBits_num(31, 0, 6);             // opcode = 000000
    setBits_num(25, PARAM1.value, 5);  // rs
    setBits_num(20, PARAM2.value, 5);  // rt
    setBits_num(15, 0, 5);             // rd = 0
    setBits_num(10, 0, 5);             // shamt = 0
    setBits_str(5, "011000");          // funct = MULT
	
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	// Check if the op code bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	//get values of rs and rt
	uint32_t Rs = getBits(25, 5); 
    uint32_t Rt = getBits(20, 5);

	//setParam(param_num, param_type, param_value)
	setOp("MULT");
	setParam(2, REGISTER, Rs);
	setParam(1, REGISTER, Rt);

	state = COMPLETE_DECODE;
}
