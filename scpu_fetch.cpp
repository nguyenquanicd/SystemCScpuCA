#include "scpu_fetch.h"
//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - body file
//Function:Read instruction and data from memory
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
//
//MEMORY
//
void scpu_fetch::IR_DR_INPUT () {
	//
	sc_uint<8> mem_sel;
	sc_uint<8> dr_tmp;
	//
	dr_tmp = fetch_dr_in.read();
	//
	mem_sel = (dc_imm.read() == 1)? dr_tmp: pc.read();
	//
	mem_dout = mem_array[mem_sel];
}
//

void scpu_fetch::MEM_OUTPUT () {
	fetch_mem_dout.write(mem_array[mem_addr.read()]);
}
//
void scpu_fetch::MEM_WRITE () {
	sc_uint<1> mem_wr;
	sc_uint<8> mem_din;
	//
	mem_wr  = dc_mem_wr.read();
	mem_din = dc_rd.read().range(7,0);
	//
	if (mem_wr == 1) {
		mem_array[mem_addr.read()] = mem_din;
	}
}
//
//FETCH
//
void scpu_fetch::INSTRUCTION_REG () {
	if (rst_n.read() == 0) {
		fetch_ir.write(0x70);
	}
	else if (dc_load_ir.read() == 1) {
		fetch_ir.write(mem_dout.read());
	}
}
//
void scpu_fetch::DATA_REG_IN () {
	if (dc_load_dr.read() == 1) {
		fetch_dr_in = mem_dout.read();
	}
}
void scpu_fetch::DATA_OUTPUT () {
	fetch_dr.write(fetch_dr_in.read());
}
//
void scpu_fetch::PROGRAM_COUNTER () {
	//
	if (rst_n.read() == 0) {
		pc = 0x00;
	}
	else if (dc_load_pc.read() == 1) {
		if (dc_imm.read() == 1) {
			pc = fetch_dr_in.read() + 0x1;
		}
		else {
			pc = pc.read() + 0x1;
		}
	}
}

//
void scpu_fetch::MEMORY_ADDR () {
	switch (dc_addr_sel.read()) {
		case 0x1:
			mem_addr = dc_rs.read().range(7,0);
		    break;
		case 0x2:
			mem_addr = fetch_dr_in.read();
		    break;
		default:
			mem_addr = pc.read();
		    break;
	}
}

//End
