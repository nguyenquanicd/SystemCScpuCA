#include "systemc.h"
//--------------------------------------
//Project: Simple CPU
//Module:  EXECUTE - header file
//Function:Read instruction and data from memory
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
SC_MODULE (scpu_execute) {
  //Input
  sc_in<sc_uint<9> > dc_rs;
  sc_in<sc_uint<9> > dc_rd;
  sc_in<sc_uint<2> > dc_op;
  //Output
  sc_out<sc_uint<9> > ex_dout;
  //
  //Signal declaration
  //
  //
  //Variable declaration 
  //
  //
  //Process declaration
  //
  //memory
  void ALU();
  //
  //Constructor
  //
  SC_CTOR (scpu_execute) {
    SC_METHOD (ALU);
      sensitive << dc_rs;
      sensitive << dc_rd;
      sensitive << dc_op;
  }
};