/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/
// edited by Jonathan Panah

#include "Instruction.h"


void div_reg_assm(void) {

    // Checks if entered MIPS code corresponds with DIV operation
    if (strcmp(OP_CODE, "DIV") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
    Checking the type of parameters
    */

    // first paramter must be a register
    if (PARAM1.type != REGISTER) {  
        state = MISSING_REG;
        return;
    }
    // second parameter must be a register
    if(PARAM2.type != REGISTER){
        state = MISSING_REG;
        return;
    }
    
    /*
    Checking the value of parameters
    */

    // first parameter must be 31 or less 
    if (PARAM1.value > 31) { 
        state = INVALID_REG;  
        return;
    }
    // second parameter should be 31 or less
    if(PARAM2.value > 31){
        state = INVALID_REG; 
        return;
    }


    /*
    Putting the binary together
    */

    // create binary
    // R-type operation, so the layout is:
    // opcode, rs, rt, rd, shamt, funct
    // original code had setBits_str and setBits_num in wrong order
    setBits_str(31, "000000");          // op
    setBits_num(20, PARAM1.value, 5);   // rs
    setBits_num(25, PARAM2.value, 5);   // rt
    setBits_num(15, 0, 10);             // rd + shamt
    setBits_str(5, "011010");           // funct = 0x1A
   
    // tell system encoding is complete
    state = COMPLETE_ENCODE;
}


void div_reg_bin(void) {
    // check the op/funct match for DIV
    if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
    Finding values in binary
    */

    // getBits(startBit, width)
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);


    /*
    Setting instruction values
    */

    // set tokens
    setOp("DIV");
    setParam(2, REGISTER, Rs); 
    setParam(1, REGISTER, Rt);  

    // tell the system decoding is complete
    state = COMPLETE_DECODE;
}






