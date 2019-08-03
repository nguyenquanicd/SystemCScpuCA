#include "systemc.h"
//--------------------------------------
//Project: Simple CPU
//Module:  FETCH - header file
//Function:Read instruction and data from memory
//Author:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
SC_MODULE (scpu_fetch) {
  //
  //Port declaration
  //
  //Input
  sc_in<bool> clk;
  sc_in<bool> rst_n;
  sc_in<bool> dc_load_pc;
  sc_in<bool> dc_imm;
  sc_in<sc_uint<2> > dc_addr_sel;
  sc_in<sc_uint<9> > dc_rs; //9 bits
  sc_in<sc_uint<9> > dc_rd; //9 bits
  sc_in<bool> dc_mem_wr;
  sc_in<bool> dc_load_dr;
  sc_in<bool> dc_load_ir;
  //Ouptut
  sc_out<sc_uint<8> > fetch_ir;
  sc_out<sc_uint<8> > fetch_dr;
  sc_out<sc_uint<8> > fetch_mem_dout;
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
  SC_CTOR (scpu_fetch) {
	  //reset_signal_is(rst_n, false);
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
};

