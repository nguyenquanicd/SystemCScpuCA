//--------------------------------------
//Project: Simple CPU
//Module:  EXECUTE - header file
//Function:Read instruction and data from memory
//Author:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
struct scpu_execute: sc_module {
  //Input
  sc_signal<sc_uint<9> > dc_rs;
  sc_signal<sc_uint<9> > dc_rd;
  sc_signal<sc_uint<2> > dc_op;
  //Output
  sc_uint<9> ex_dout;
  //
  //Signal declaration
  //
  //
  //Variable declaration 
  //
  //
  //Sockets
  //
  unsigned int dc2ex_pkt_tmp;
  sc_uint<27> dc2ex_pkt;
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<scpu_execute> ex2dc_socket;
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<scpu_execute> dc2ex_socket;
  void EX2DC_SOCKET();
  //
  //Process declaration
  //
  //memory
  void ALU();
  //
  //Constructor
  //
  SC_CTOR (scpu_execute): ex2dc_socket("ex2dc_socket"), dc2ex_socket("dc2ex_socket")  {
  	//Sockets
  	SC_THREAD (EX2DC_SOCKET);
  	// Register callback for incoming b_transport interface method call
    dc2ex_socket.register_b_transport(this, &scpu_execute::dc2ex_transport);
    //
    SC_METHOD (ALU);
      sensitive << dc_rs;
      sensitive << dc_rd;
      sensitive << dc_op;
  }
  virtual void dc2ex_transport (tlm::tlm_generic_payload& dc2ex_trans, sc_time &delay) {
    tlm::tlm_command dc_cmd = dc2ex_trans.get_command();
    unsigned char*   dc_ptr = dc2ex_trans.get_data_ptr();
    unsigned int     dc_len = dc2ex_trans.get_data_length();
    unsigned char*   dc_byt = dc2ex_trans.get_byte_enable_ptr();
    unsigned int     dc_wid = dc2ex_trans.get_streaming_width();
    
    if (dc_cmd != tlm::TLM_WRITE_COMMAND)
      SC_REPORT_ERROR("TLM-2", "Target only support TLM_WRITE_COMMAND for the transaction from DECODER to EXECUTE");
    //
	memcpy (&dc2ex_pkt_tmp, dc_ptr, dc_len);
    dc2ex_pkt = dc2ex_pkt_tmp;
	//
	dc_rs       = dc2ex_pkt.range(19,11); //9 bits
	dc_rd       = dc2ex_pkt.range(10,2); //9 bits
	dc_op       = dc2ex_pkt.range(1,0);
    // Set response status to indicate successful completion
    dc2ex_trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }
};
