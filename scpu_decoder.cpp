//--------------------------------------
//Project:  Simple CPU
//Module:   scpu_decoder
//Function: Decode the instruction to create the control signals
//Author:  Truong Cong Hoang Viet - Le Hoang Van
//Page:    VLSI Technology
//--------------------------------------

#include "scpu_decoder.h"

//Source register
void scpu_decoder::RS_SEL() {
	if (fetch_ir.read().range(1,0) == 0x0) {
		dc_rs_reg = reg0.read();
	}
	else if (fetch_ir.read().range(1,0) == 0x1) {
		dc_rs_reg = reg1.read();
	}
	else if (fetch_ir.read().range(1,0) == 0x2) {
		dc_rs_reg = reg2.read();
	}
	else if (fetch_ir.read().range(1,0) == 0x3) {
		dc_rs_reg = reg3.read();
	}
}
void scpu_decoder::RS_OUTPUT() {
	dc_rs.write(dc_rs_reg);
}
//Destination register
void scpu_decoder::RD_SEL() {
	//
	switch (fetch_ir.read().range(3,2)) {
	  case 0: dc_rd_reg = reg0.read();
		break;
	  case 1: dc_rd_reg = reg1.read();
		break;
	  case 2: dc_rd_reg = reg2.read();
		break;
	  case 3: dc_rd_reg = reg3.read();
		break;
	  default:
		break;
	}
}
void scpu_decoder::RD_OUTPUT() {
	dc_rd.write(dc_rd_reg.read());
}
//
void scpu_decoder::REG_WE() {
	//
	if (fetch_ir.read().range(7,4) == AND ||
		fetch_ir.read().range(7,4) == OR ||
		fetch_ir.read().range(7,4) == ADD ||
		fetch_ir.read().range(7,4) == SUB ||
		fetch_ir.read().range(7,4) == LWR ||
		fetch_ir.read().range(7,4) == MOV
		) {
		load_reg_en = ctrl_counter.read()[0];
	}
	else if (fetch_ir.read().range(7,4) == LWI || fetch_ir.read().range(7,4) == LI) {
		load_reg_en = ctrl_counter.read()[1];
	}
	else {
		load_reg_en = 0;
	}
}
void scpu_decoder::REG_WE_SEL() {
    //
    sc_uint<4> load_reg_tmp;
    load_reg_tmp = 0;
	if (fetch_ir.read().range(3,2) == 0) {
		load_reg_tmp[0] = load_reg_en;
	}
	else if (fetch_ir.read().range(3,2) == 1) {
		load_reg_tmp[1] = load_reg_en;
	}
	else if(fetch_ir.read().range(3,2) == 2) {
		load_reg_tmp[2] = load_reg_en;
	}
	else if (fetch_ir.read().range(3,2) == 3) {
		load_reg_tmp[3] = load_reg_en;
	}
	load_reg.write(load_reg_tmp);
}

void scpu_decoder::REG_IN_SEL () {
	bool fetch_dr_8;
	bool mem_out_8;
	//
	fetch_dr_8   = 0;
	mem_out_8    = 0;
	//
    if (fetch_ir.read().range(7,4) == AND ||
		fetch_ir.read().range(7,4) == OR  ||
		fetch_ir.read().range(7,4) == ADD ||
		fetch_ir.read().range(7,4) == SUB ) {
		reg_in = ex_dout.read();
	}
	else if (fetch_ir.read().range(7,4) == LI) {
		reg_in = (fetch_dr_8, fetch_dr.read());
	}
	else if (fetch_ir.read().range(7,4) == MOV) {
		reg_in = dc_rs_reg.read();
	}
	else if (fetch_ir.read().range(7,4) == LWR ||
			 fetch_ir.read().range(7,4) == LWI) {
		reg_in = (mem_out_8, fetch_mem_dout.read());
	}
	else {
		reg_in = 0;
	}	
}

void scpu_decoder::LOAD_DTA_TO_REG() {
	//
	sc_uint<4> write_en;
	write_en = load_reg.read();
	//
	if (write_en[0] == 1) {
		reg0 = reg_in.read();
	}
	//
	if (write_en[1] == 1) {
		reg1 = reg_in.read();
	}
	//
	if (write_en[2] == 1) {
		reg2 = reg_in.read();
	}
	//
	if (write_en[3] == 1) {
		reg3 = reg_in.read();
	}
}

void scpu_decoder::CLR_COUNTER_COMP() {
  switch (fetch_ir.read().range(7,4)) {
    case JEQ: case JNE: case JGT: case JLT: case LWI: case SWI: case LI: case JMP:
      clr_counter = ctrl_counter.read()[1];
      break;
    case AND: case OR: case ADD: case SUB: case LWR: case SWR: case MOV:
      clr_counter = ctrl_counter.read()[0];
      break;
    case NOP:
      clr_counter = 1;
      break;
    default:
      break;
  }
}

void scpu_decoder::CTRL_COUNTER_COMP() {
  if (clr_counter.read() == 1) {
    ctrl_counter_next = 0;
  }
  else {
    ctrl_counter_next = ctrl_counter.read() + 1;
  }
}

void scpu_decoder::CTRL_COUNTER_FF() {
  if (rst_n.read() == 0) {
    ctrl_counter = 0;
  }
  else {
    ctrl_counter = ctrl_counter_next.read();
  }
}

void scpu_decoder::DC_LOAD_PC_COMP() {
  dc_load_pc = (dc_load_ir_tmp.read() | dc_load_dr_tmp.read());
}

void scpu_decoder::JUMP_EN_COMP() {
  switch (fetch_ir.read().range(7,4)) {
    case JEQ:
      jump_en = (dc_rd_reg.read() == 0);
      break;
    case JNE:
      jump_en = (dc_rd_reg.read() != 0);
      break;
    case JGT:
      jump_en = (dc_rd_reg.read().range(7,0) != 0) & (dc_rd_reg.read()[8] == 0);
      break;
    case JLT:
      jump_en = dc_rd_reg.read()[8];
      break;
    case JMP:
      jump_en = 1;
      break;
    default:
      jump_en = 0;
      break;
  }
}

void scpu_decoder::DC_IMM_COMP() {
  dc_imm = jump_en.read() & ctrl_counter.read()[1];
}

void scpu_decoder::DC_ADDR_SEL_COMP() {
  switch (fetch_ir.read().range(7,4)) {
    case LWI: case SWI: case LWR: case SWR:
      dc_addr_sel = ctrl_counter.read();
      break;
    default: // other
      dc_addr_sel = 0;
      break;
  }
}

void scpu_decoder::DC_LOAD_DR_COMP(){
  switch (fetch_ir.read().range(7,4)) {
    case JEQ: case JNE: case JGT: case JLT: case LWI: case SWI: case LI: case JMP:
      dc_load_dr_tmp = ctrl_counter.read()[0];
      break;
    default: // other
      dc_load_dr_tmp = 0;
      break;
  }
}

void scpu_decoder::DC_LOAD_DR_OUTPUT() {
	dc_load_dr = dc_load_dr_tmp.read();
}

void scpu_decoder::DC_LOAD_IR_COMP() {
  dc_load_ir_tmp = clr_counter.read();
}

void scpu_decoder::DC_LOAD_IR_OUTPUT() {
  dc_load_ir = dc_load_ir_tmp.read();
}

void scpu_decoder::DC_OP_COMP() {
  dc_op = fetch_ir.read().range(5,4);
}

void scpu_decoder::DC_MEM_WR_COMP() {
  switch (fetch_ir.read().range(7,4)) {
    case SWR:
      dc_mem_wr = ctrl_counter.read()[0];
      break;
    case SWI:
      dc_mem_wr = ctrl_counter.read()[1];
      break;
    default: // other
      dc_mem_wr = 0;
      break;
  }
}
