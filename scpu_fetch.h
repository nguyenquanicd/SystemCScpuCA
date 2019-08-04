//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - header file
//Function:Read instruction and data from memory
//Author:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
struct scpu_fetch: sc_module {
  //
  //Port declaration
  //
  //Input
  sc_in<bool> clk;
  sc_in<bool> rst_n;
  sc_signal<bool> dc_load_pc;
  sc_signal<bool> dc_imm;
  sc_signal<sc_uint<2> > dc_addr_sel;
  sc_signal<sc_uint<9> > dc_rs; //9 bits
  sc_signal<sc_uint<9> > dc_rd; //9 bits
  sc_signal<bool> dc_mem_wr;
  sc_signal<bool> dc_load_dr;
  sc_signal<bool> dc_load_ir;
  //Ouptut
  sc_uint<8>  fetch_ir;
  sc_uint<8>  fetch_dr;
  sc_uint<8>  fetch_mem_dout;
  //
  //Signal declaration
  //
  sc_signal<sc_uint<8> > mem_dout;
  sc_signal<sc_uint<8> > pc;
  sc_signal<sc_uint<8> > mem_addr;
  sc_signal<sc_uint<8> > fetch_dr_in;
  //
  //Variable declaration
  //
  sc_uint<8> mem_array [256];
  //
  //Sockets
  //
  //Intermedia data packet is received from DECODER
  unsigned int dc2fetch_pkt_tmp;
  //Data packet is showed as a vector to divide to bit field
  sc_uint<27> dc2fetch_pkt;
  // Initiator socket
  tlm_utils::simple_initiator_socket<scpu_fetch> fetch2dc_socket;
  // Target socket
  tlm_utils::simple_target_socket<scpu_fetch> dc2fetch_socket;
  // Method to send the data packet from FETCH to DECODER via the intiator socket
  void FETCH2DC_SOCKET();
  //
  //Process declaration
  //
  //memory
  void IR_DR_INPUT();
  void MEM_OUTPUT();
  void MEM_WRITE();
  //fetch
  void INSTRUCTION_REG();
  void DATA_REG_IN();
  void DATA_OUTPUT();
  void PROGRAM_COUNTER();
  void MEMORY_ADDR();
  //
  //Module Constructor
  //
  SC_CTOR (scpu_fetch): dc2fetch_socket("dc2fetch_socket"), fetch2dc_socket("fetch2dc_socket") {
    //
  	//Sockets
    //
  	SC_THREAD (FETCH2DC_SOCKET);
  	// Register callback for incoming b_transport interface method call
    dc2fetch_socket.register_b_transport(this, &scpu_fetch::dc2fetch_transport);
    //
    //
    //
    SC_METHOD (IR_DR_INPUT);
      sensitive << fetch_dr_in;
      sensitive << pc;
      sensitive << dc_imm;
    //
    SC_METHOD (MEM_OUTPUT);
      sensitive << mem_addr;
    //
    SC_METHOD (MEM_WRITE);
      sensitive << clk.pos();
    //
    SC_METHOD (INSTRUCTION_REG);
      sensitive << clk.pos();
    //
    SC_METHOD (DATA_REG_IN);
      sensitive << clk.pos();
      //
    SC_METHOD (DATA_OUTPUT);
      sensitive << fetch_dr_in;
    //
    SC_METHOD (PROGRAM_COUNTER);
      sensitive << clk.pos();
    //
    SC_METHOD (MEMORY_ADDR);
      sensitive << dc_addr_sel;
      sensitive << pc;
      sensitive << fetch_dr_in;
      sensitive << dc_rs;
  }
  virtual void dc2fetch_transport (tlm::tlm_generic_payload& dc2fetch_trans, sc_time &delay) {
    tlm::tlm_command dc_cmd = dc2fetch_trans.get_command();  //Get the command type
    unsigned char*   dc_ptr = dc2fetch_trans.get_data_ptr(); //Get the data pointer
    unsigned int     dc_len = dc2fetch_trans.get_data_length(); //Get the data length
    unsigned char*   dc_byt = dc2fetch_trans.get_byte_enable_ptr();
    unsigned int     dc_wid = dc2fetch_trans.get_streaming_width();
    //
    if (dc_cmd != tlm::TLM_WRITE_COMMAND)
      SC_REPORT_ERROR("TLM-2", "Target only support TLM_WRITE_COMMAND for the transaction from DECODER to FETCH");
    //Get the data packet from DECODER
	memcpy (&dc2fetch_pkt_tmp, dc_ptr, dc_len);
	dc2fetch_pkt = dc2fetch_pkt_tmp;
    //cout << "dc2fetch ..." << dc2fetch_pkt << endl;
	//Separate the data packet into the control signals
	dc_load_pc  = dc2fetch_pkt.range(26,26);
	dc_imm      = dc2fetch_pkt.range(25,25);
	dc_addr_sel = dc2fetch_pkt.range(21,20);
	dc_rs       = dc2fetch_pkt.range(19,11); //9 bits
	dc_rd       = dc2fetch_pkt.range(12,2);  //9 bits
	dc_mem_wr   = dc2fetch_pkt.range(24,24);
	dc_load_dr  = dc2fetch_pkt.range(23,23);
	dc_load_ir  = dc2fetch_pkt.range(22,22);
    //Set the response status to indicate successful completion
    dc2fetch_trans.set_response_status( tlm::TLM_OK_RESPONSE );
    //dc2fetch_trans.set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );
  }
};

