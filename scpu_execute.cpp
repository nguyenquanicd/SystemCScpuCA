//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - body file
//Function:Read instruction and data from memory
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
#include "scpu_execute.h"
void scpu_execute::ALU () {
	sc_uint<9> and_result;
	sc_uint<9> or_result;
	sc_uint<9> add_result;
	sc_uint<9> sub_result;
	//
	and_result = dc_rd.read() & dc_rs.read();
	or_result  = dc_rd.read() | dc_rs.read();
	add_result = dc_rd.read() + dc_rs.read();
	sub_result = dc_rd.read() - dc_rs.read();
	switch (dc_op.read()) {
		case 0x0: //AND
			ex_dout.write(and_result);
		    break;
		case 0x1: //OR
		    ex_dout.write(or_result);
		    break;
		case 0x2: //ADD
		    ex_dout.write(add_result);
		    break;
		case 0x3: //SUB
		    ex_dout.write(sub_result);
		    break;
		default: break;
	}
}