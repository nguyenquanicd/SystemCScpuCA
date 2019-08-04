//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - body file
//Function:Read instruction and data from memory
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
#include "scpu_execute.h"
//
//EX2DC_SOCKET
//
void scpu_execute::EX2DC_SOCKET() {
	//
    unsigned int ex_data_tmp;
	sc_uint<9> ex_data;
    // TLM-2 generic payload transaction, reused across calls to b_transport
    tlm::tlm_generic_payload* ex2dc_trans = new tlm::tlm_generic_payload;
    sc_time wire_delay = sc_time(0, SC_PS); //Delay of a transaction on socket
    sc_time trans_delay = sc_time(10, SC_PS); //Delay between 2 transaction
    // Generate a random sequence of reads and writes
    while (1) {
      tlm::tlm_command ex_cmd = tlm::TLM_WRITE_COMMAND;
      ex_data = ex_dout;
      ex_data_tmp = ex_data;
         // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
         ex2dc_trans->set_command( ex_cmd );
         ex2dc_trans->set_data_ptr( reinterpret_cast<unsigned char*>(&ex_data_tmp) );
         ex2dc_trans->set_data_length( 2 );
         ex2dc_trans->set_streaming_width( 2 ); // = data_length to indicate no streaming
         ex2dc_trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
         ex2dc_trans->set_dmi_allowed( false ); // Mandatory initial value
         ex2dc_trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
         ex2dc_socket->b_transport( *ex2dc_trans, wire_delay );  // Blocking transport call
      //Check response status and delay
      if ( ex2dc_trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      wait(trans_delay);
    }
};
//
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
			ex_dout = and_result;
		    break;
		case 0x1: //OR
		    ex_dout = or_result;
		    break;
		case 0x2: //ADD
		    ex_dout = add_result;
		    break;
		case 0x3: //SUB
		    ex_dout = sub_result;
		    break;
		default: break;
	}
}
