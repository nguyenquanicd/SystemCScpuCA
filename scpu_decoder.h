//--------------------------------------
//Project:  Simple CPU
//Module:   Decoder
//Function: All declarations of decoder
//Author:   Truong Cong Hoang Viet - Le Hoang Van - Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#include "systemc.h"
#include "scpu_define.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

struct scpu_decoder: sc_module {
	//Input
	sc_in<bool> clk;
	sc_in<bool> rst_n;
	sc_signal<sc_uint<8> > fetch_ir;
	sc_signal<sc_uint<8> > fetch_dr;
	sc_signal<sc_uint<8> > fetch_mem_dout;
	sc_signal<sc_uint<9> > ex_dout; //Note: 9 bits
	//Output
    sc_uint<1>  dc_load_pc; //Not bool
    sc_uint<1>  dc_imm;
    sc_uint<1>  dc_mem_wr;
    sc_uint<1>  dc_load_dr;
    sc_uint<1>  dc_load_ir;
    sc_uint<2>   dc_addr_sel;
    sc_uint<9>    dc_rs; //Note: 9 bits
    sc_uint<9>    dc_rd; //Note: 9 bits
    sc_uint<2>    dc_op;
    //Internal signals
    sc_signal<sc_uint<2> > ctrl_counter_next;
    sc_signal<sc_uint<9> > reg_in; //Note: 9 bits
    sc_signal<sc_uint<9> > reg0;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg1;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg2;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg3;   //Note: 9 bits
	sc_signal<sc_uint<9> > dc_rs_reg; //Note: 9 bits
    sc_signal<sc_uint<9> > dc_rd_reg; //Note: 9 bits
    sc_signal<sc_uint<2> > ctrl_counter;
	sc_signal<sc_uint<4> > load_reg;
    sc_signal<bool>  clr_counter;
    sc_signal<bool>  jump_en;
    sc_signal<bool>  load_reg_en;
    sc_signal<bool>	  dc_load_dr_tmp;
    sc_signal<bool>   dc_load_ir_tmp;
    //
    //Sockets
    //
    //FETCH and DECODER
    //
    unsigned int fetch2dc_pkt_tmp;
    sc_uint<24> fetch2dc_pkt;
    // Use tagged sockets to be able to distinguish incoming backward path calls
    //tlm_utils::simple_initiator_socket_tagged<scpu_decoder>* dc_output_socket[2];
    tlm_utils::simple_initiator_socket<scpu_decoder>* dc_output_socket[2];
    void DC_OUTPUT_SOCKET();
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    //tlm_utils::simple_initiator_socket<scpu_decoder> dc2fetch_socket;
    //void DC2FETCH_SOCKET();
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<scpu_decoder> fetch2dc_socket;
    
    //
    //EXECUTE and DECODER
    //
    unsigned int ex2dc_pkt_tmp;
    sc_uint<9> ex2dc_pkt;
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    //tlm_utils::simple_initiator_socket<scpu_decoder> dc2ex_socket;
    void DC2EX_SOCKET();
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<scpu_decoder> ex2dc_socket;
    //
    //Method declaration
    //
    //Control counter
	void CLR_COUNTER_COMP();
	void CTRL_COUNTER_COMP();
	void CTRL_COUNTER_FF();
	void DC_LOAD_PC_COMP();
	// decoder block 3: dc_imm
	void JUMP_EN_COMP();
	void DC_IMM_COMP();
	// decoder block 4: dc_addr_sel
	void DC_ADDR_SEL_COMP();
	void RS_SEL();
	void RS_OUTPUT();
	void RD_SEL();
	void RD_OUTPUT();
	void REG_WE();
	void REG_WE_SEL();
	void REG_IN_SEL();
	void LOAD_DTA_TO_REG();
	// decoder block 6: dc_load_dr
	void DC_LOAD_DR_COMP();
    void DC_LOAD_DR_OUTPUT();
	// decoder block 7: dc_load_ir
	void DC_LOAD_IR_COMP();
	void DC_LOAD_IR_OUTPUT();
	// decoder block 8: dc_op
	void DC_OP_COMP();
	// decoder block 9: dc_mem_wr
	void DC_MEM_WR_COMP();

    //void DECODER_DATAIN();
    //
    //Constructor
    //

	SC_CTOR(scpu_decoder) : fetch2dc_socket("fetch2dc_socket"), ex2dc_socket("ex2dc_socket") {
        //Sockets
        //Create the initiator sockets
        for (unsigned int i = 0; i < 2; i++) {
        	char socket_name[20];
        	sprintf(socket_name, "dc_output_socket_%d", i);
        	dc_output_socket[i] = new tlm_utils::simple_initiator_socket<scpu_decoder>(socket_name);
        }
  	    SC_THREAD (DC_OUTPUT_SOCKET);
  	    //SC_THREAD (DC2EX_SOCKET);
  	    // Register callback for incoming b_transport interface method call
        fetch2dc_socket.register_b_transport(this, &scpu_decoder::fetch2dc_transport);
        ex2dc_socket.register_b_transport(this, &scpu_decoder::ex2dc_transport);
        //
  	    //
		SC_METHOD(RS_SEL);
		  sensitive << fetch_ir;
		  sensitive << reg0;
		  sensitive << reg1;
		  sensitive << reg2;
		  sensitive << reg3;
		SC_METHOD(RS_OUTPUT);
		  sensitive << dc_rs_reg;
		//
		SC_METHOD(RD_SEL);
		  sensitive << fetch_ir;
		  sensitive << reg0;
		  sensitive << reg1;
		  sensitive << reg2;
		  sensitive << reg3;
		SC_METHOD(RD_OUTPUT);
		  sensitive << dc_rd_reg;
		//
		SC_METHOD(REG_WE);
		  sensitive << fetch_ir;
		  sensitive << ctrl_counter;
		
		SC_METHOD(REG_WE_SEL);
		  sensitive << fetch_ir;
		  sensitive << load_reg_en;
		//
		SC_METHOD(REG_IN_SEL);
		  sensitive << fetch_ir;
		  sensitive << ex_dout;
		  sensitive << dc_rs_reg;
		  sensitive << fetch_dr;
		  sensitive << fetch_mem_dout;
		//
		SC_METHOD(LOAD_DTA_TO_REG);
		  sensitive << clk.pos();
        // decoder block 2: dc_load_pc
        SC_METHOD( CLR_COUNTER_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        //
        SC_METHOD( CTRL_COUNTER_COMP );
          sensitive << clr_counter;
          sensitive << ctrl_counter;
        //
        SC_METHOD( CTRL_COUNTER_FF );
          sensitive << clk.pos();
        //
        SC_METHOD( DC_LOAD_PC_COMP );
          sensitive << dc_load_ir_tmp;
          sensitive << dc_load_dr_tmp;
        // decoder block 3: dc_imm
        SC_METHOD( JUMP_EN_COMP );
          sensitive << fetch_ir;
          sensitive << dc_rd_reg;
        //
        SC_METHOD( DC_IMM_COMP );
          sensitive << jump_en;
          sensitive << ctrl_counter;
        // decoder block 4: dc_addr_sel
        SC_METHOD( DC_ADDR_SEL_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        // decoder block 6: dc_load_dr
        SC_METHOD( DC_LOAD_DR_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        //
        SC_METHOD (DC_LOAD_DR_OUTPUT);
          sensitive << dc_load_dr_tmp; 
        // decoder block 7: dc_load_ir
        SC_METHOD(DC_LOAD_IR_COMP);
          sensitive << clr_counter;
        //
        SC_METHOD(DC_LOAD_IR_OUTPUT);
          sensitive << dc_load_ir_tmp;
        // decoder block 8: dc_op
        SC_METHOD( DC_OP_COMP );
          sensitive << fetch_ir;
        // decoder block 9: dc_mem_wr
        SC_METHOD( DC_MEM_WR_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
	}
  //From FETCH
  virtual void fetch2dc_transport (tlm::tlm_generic_payload& fetch2dc_trans, sc_time &delay) {
    tlm::tlm_command dc_cmd = fetch2dc_trans.get_command();
    unsigned char*   dc_ptr = fetch2dc_trans.get_data_ptr();
    unsigned int     dc_len = fetch2dc_trans.get_data_length();
    unsigned char*   dc_byt = fetch2dc_trans.get_byte_enable_ptr();
    unsigned int     dc_wid = fetch2dc_trans.get_streaming_width();
    
    if (dc_cmd != tlm::TLM_WRITE_COMMAND)
      SC_REPORT_ERROR("TLM-2", "Target only support TLM_WRITE_COMMAND for the transaction from FETCH to DECODER");
    //
	memcpy (&fetch2dc_pkt_tmp, dc_ptr, dc_len);
    fetch2dc_pkt = fetch2dc_pkt_tmp;
	//
	fetch_ir   = fetch2dc_pkt.range(23,16);
	fetch_dr   = fetch2dc_pkt.range(15,8);
	fetch_mem_dout  = fetch2dc_pkt.range(7,0);
    // Set response status to indicate successful completion
    fetch2dc_trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }
  //From EXECUTE
  virtual void ex2dc_transport (tlm::tlm_generic_payload& ex2dc_trans, sc_time &delay) {
    tlm::tlm_command dc_cmd = ex2dc_trans.get_command();
    unsigned char*   dc_ptr = ex2dc_trans.get_data_ptr();
    unsigned int     dc_len = ex2dc_trans.get_data_length();
    unsigned char*   dc_byt = ex2dc_trans.get_byte_enable_ptr();
    unsigned int     dc_wid = ex2dc_trans.get_streaming_width();
    
    if (dc_cmd != tlm::TLM_WRITE_COMMAND)
      SC_REPORT_ERROR("TLM-2", "Target only support TLM_WRITE_COMMAND for the transaction from EXECUTE to DECODER");
    //
	memcpy (&ex2dc_pkt_tmp, dc_ptr, dc_len);
    ex2dc_pkt = ex2dc_pkt_tmp;
	//
	ex_dout   = ex2dc_pkt.range(8,0);
    // Set response status to indicate successful completion
    ex2dc_trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }
};
