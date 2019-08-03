#include "systemc.h"
#include "scpu_fetch.cpp"
#include "scpu_decoder.cpp"
#include "scpu_execute.cpp"

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
	SC_CTOR (scpu_top) : scpu_fetch_inst("scpu_fetch_inst"), 
		scpu_decoder_inst("scpu_decoder_inst"), 
		scpu_execute_inst("scpu_execute_inst")
		{
	  //Create the instance FETCH
	  //scpu_fetch_inst = new scpu_fetch("FETCH");
      scpu_fetch_inst.clk(clk);
      scpu_fetch_inst.rst_n(rst_n);
      scpu_fetch_inst.dc_load_pc(dc_load_pc);
      scpu_fetch_inst.dc_imm(dc_imm);
      scpu_fetch_inst.dc_addr_sel(dc_addr_sel);
      scpu_fetch_inst.dc_rs(dc_rs);
      scpu_fetch_inst.dc_rd(dc_rd);
      scpu_fetch_inst.dc_mem_wr(dc_mem_wr);
      scpu_fetch_inst.dc_load_dr(dc_load_dr);
      scpu_fetch_inst.dc_load_ir(dc_load_ir);
      scpu_fetch_inst.fetch_ir(fetch_ir);
      scpu_fetch_inst.fetch_dr(fetch_dr);
      scpu_fetch_inst.fetch_mem_dout(fetch_mem_dout);
	  //Create the instance DECODER
	  //scpu_decoder_inst = new scpu_decoder("DECODER");
	  scpu_decoder_inst.clk(clk);
	  scpu_decoder_inst.rst_n(rst_n);
	  scpu_decoder_inst.fetch_ir(fetch_ir);
	  scpu_decoder_inst.fetch_dr(fetch_dr);
	  scpu_decoder_inst.fetch_mem_dout(fetch_mem_dout);
	  scpu_decoder_inst.ex_dout(ex_dout);
	  scpu_decoder_inst.dc_load_pc(dc_load_pc);
	  scpu_decoder_inst.dc_imm(dc_imm);
	  scpu_decoder_inst.dc_addr_sel(dc_addr_sel);
	  scpu_decoder_inst.dc_rs(dc_rs);
	  scpu_decoder_inst.dc_rd(dc_rd);
	  scpu_decoder_inst.dc_mem_wr(dc_mem_wr);
	  scpu_decoder_inst.dc_load_dr(dc_load_dr);
	  scpu_decoder_inst.dc_load_ir(dc_load_ir);
	  scpu_decoder_inst.dc_op(dc_op);
	 //Create the instance EXECUTE
	 //scpu_execute_inst = new scpu_execute("EXECUTE");
     scpu_execute_inst.dc_rs(dc_rs);
     scpu_execute_inst.dc_rd(dc_rd);
     scpu_execute_inst.dc_op(dc_op);
     scpu_execute_inst.ex_dout(ex_dout);
	}
};