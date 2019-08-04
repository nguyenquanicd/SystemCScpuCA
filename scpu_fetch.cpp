//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - body file
//Function:Read instruction and data from memory
//Author:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
#include "scpu_fetch.h"
//
//FETCH2DC_SOCKET
//
void scpu_fetch::FETCH2DC_SOCKET() {
	//Data packet collect all outputs
    unsigned int fetch_data_tmp;
	sc_uint<24> fetch_data;
    // TLM-2 generic payload transaction, reused across calls to b_transport
    tlm::tlm_generic_payload* fetch2dc_trans = new tlm::tlm_generic_payload;
    sc_time wire_delay = sc_time(0, SC_PS);
    sc_time trans_delay = sc_time(10, SC_PS);
    while (1) {
      //Set the command type
      tlm::tlm_command fetch_cmd = tlm::TLM_WRITE_COMMAND;
      //Wrap all outputs to the data packet
         fetch_data = (fetch_ir, fetch_dr, fetch_mem_dout);
         fetch_data_tmp = fetch_data;
         // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
         fetch2dc_trans->set_command( fetch_cmd );
         fetch2dc_trans->set_data_ptr( reinterpret_cast<unsigned char*>(&fetch_data_tmp) );
         fetch2dc_trans->set_data_length( 3 );
         fetch2dc_trans->set_streaming_width( 3 ); // = data_length to indicate no streaming
         fetch2dc_trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
         fetch2dc_trans->set_dmi_allowed( false ); // Mandatory initial value
         fetch2dc_trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
         fetch2dc_socket->b_transport( *fetch2dc_trans, wire_delay );  // Blocking transport call
      // Check response status from DECODER
      if ( fetch2dc_trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      // Realize the delay annotated onto the transport call
      wait(trans_delay);
    }
};
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
	if (dc_imm == 1) {
	  mem_sel = dr_tmp;
	  mem_dout = mem_array[mem_sel];
	}
	else {
	  mem_sel = pc.read();
	  mem_dout = mem_array[mem_sel];
	}
}
//

void scpu_fetch::MEM_OUTPUT () {
	fetch_mem_dout = mem_array[mem_addr.read()];
}
//
void scpu_fetch::MEM_WRITE () {
	sc_uint<1> mem_wr;
	sc_uint<8> mem_din;
	//
	mem_wr  = dc_mem_wr;
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
		fetch_ir = 0x70;
	}
	else if (dc_load_ir == 1) {
		fetch_ir = mem_dout.read();
	}
}
//
void scpu_fetch::DATA_REG_IN () {
	if (dc_load_dr == 1) {
		fetch_dr_in = mem_dout.read();
	}
}
void scpu_fetch::DATA_OUTPUT () {
	fetch_dr = fetch_dr_in.read();
}
//
void scpu_fetch::PROGRAM_COUNTER () {
	//
	if (rst_n.read() == 0) {
		pc = 0x00;
	}
	else if (dc_load_pc == 1) {
		if (dc_imm == 1) {
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
