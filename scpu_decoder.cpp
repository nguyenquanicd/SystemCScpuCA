//--------------------------------------
//Project:  Simple CPU
//Module:   scpu_decoder
//Function: Decode the instruction to create the control signals
//Author:  Truong Cong Hoang Viet - Le Hoang Van
//Page:    VLSI Technology
//--------------------------------------
#include "scpu_decoder.h"
//
//DC_OUTPUT_SOCKET
//
void scpu_decoder::DC_OUTPUT_SOCKET() {
	//
    unsigned int decoder_data_tmp;
	sc_uint<27> decoder_data;
    // TLM-2 generic payload transaction, reused across calls to b_transport
    // Create the transaction
    tlm::tlm_generic_payload* dc_output_trans = new tlm::tlm_generic_payload;
    sc_time wire_delay = sc_time(0, SC_PS);
    sc_time trans_delay = sc_time(10, SC_PS);
    //Forever run
    while (1) {
      //Set the command attribute
      //TLM_WRITE_COMMAND is set because this packet only output data from DECODER
      tlm::tlm_command dc_cmd = tlm::TLM_WRITE_COMMAND;
      //Create the write data which is sent from DECODER
      //They are all outputs of DECODER
      decoder_data = (dc_load_pc, dc_imm, dc_mem_wr, dc_load_dr, dc_load_ir, dc_addr_sel, dc_rs, dc_rd, dc_op);
      decoder_data_tmp = decoder_data;
      // Set up the attribute of a payload
      // Set the command type - WRITE
      dc_output_trans->set_command( dc_cmd );
      // Data pointer
      dc_output_trans->set_data_ptr( reinterpret_cast<unsigned char*>(&decoder_data_tmp) );
      // Number of data bytes. It is equal or larger than the number of transfered bits 
      dc_output_trans->set_data_length( 4 ); //4 bytes which can cover 27 bits
      dc_output_trans->set_streaming_width( 4 ); // = the value of set_data_length to indicate "no streaming"
      dc_output_trans->set_byte_enable_ptr( 0 ); // 0 indicates "Do not use the byte enable to control the transaction"
      dc_output_trans->set_dmi_allowed( false ); // Mandatory initial value to clear DMI hint
      dc_output_trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
      for (unsigned int i = 0; i < 2; i++) {
        (dc_output_socket[i])->b_transport( *dc_output_trans, wire_delay );  // Blocking transport call
        //Check response status and delay
        if ( dc_output_trans->is_response_error() ) {
          cout << "---------------------------" << endl;
          cout << "--- Socket num: " << i << endl;
          cout << "   " << 0 << "- from FETCH" << endl;
          cout << "   " << 1 << "- from EXECUTE" << endl;
          SC_REPORT_ERROR("[DECODER]", "Response error from b_transport");
        }  
      }
      // Realize the delay annotated onto the transport call
      wait(trans_delay);
    }
}
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
	dc_rs = dc_rs_reg;
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
	dc_rd = dc_rd_reg.read();
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
	load_reg = load_reg_tmp;
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

  
 
  
