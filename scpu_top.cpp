#include "scpu_fetch.h"
#include "scpu_decoder.h"
#include "scpu_execute.h"

//--------------------------------------
//Project: Simple CPU
//Module:  TOP module
//Function:Connect all sub-modules (FETCH, DECODER, EXECUTE)
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------

SC_MODULE (scpu_top) {
	sc_in<bool> clk;
	sc_in<bool> rst_n;
	//
	//Internal connection
	//
	sc_signal<bool> dc_load_pc;
	sc_signal<bool> dc_imm;
	sc_signal<sc_uint<2> > dc_addr_sel;
	sc_signal<sc_uint<9> > dc_rs; //9 bits
	sc_signal<sc_uint<9> > dc_rd; //9 bits
	sc_signal<bool> dc_mem_wr;
	sc_signal<bool> dc_load_dr;
	sc_signal<bool> dc_load_ir;
	//
	sc_signal<sc_uint<8> > fetch_ir;
	sc_signal<sc_uint<8> > fetch_dr;
	sc_signal<sc_uint<8> > fetch_mem_dout;
	sc_signal<sc_uint<9> > ex_dout;
	//
	sc_signal<sc_uint<2> > dc_op; //9 bits
	//
	//Instance declaration
	scpu_fetch   scpu_fetch_inst;
	scpu_decoder scpu_decoder_inst;
	scpu_execute scpu_execute_inst;
	
	//
	//SC_CTOR (scpu_top)
	SC_CTOR (scpu_top) : scpu_fetch_inst("scpu_fetch_inst"), 
		scpu_decoder_inst("scpu_decoder_inst"), 
		scpu_execute_inst("scpu_execute_inst")
		{
	   //Output bind Input
	   scpu_decoder_inst.dc_output_socket[0]->bind(scpu_fetch_inst.dc2fetch_socket);
	   scpu_decoder_inst.dc_output_socket[1]->bind(scpu_execute_inst.dc2ex_socket);
	   scpu_decoder_inst.ex2dc_socket.bind(scpu_execute_inst.ex2dc_socket);
	   scpu_decoder_inst.fetch2dc_socket.bind(scpu_fetch_inst.fetch2dc_socket);   
	   
      scpu_fetch_inst.clk(clk);
      scpu_fetch_inst.rst_n(rst_n);

	  scpu_decoder_inst.clk(clk);
	  scpu_decoder_inst.rst_n(rst_n);
	}
};
