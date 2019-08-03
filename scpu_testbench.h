//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#include "systemc.h"
#include "scpu_top.cpp"
SC_MODULE (scpu_testbench) {
	//Ports and signals
	sc_in <bool> clk;
	sc_signal <bool> rst_n;
	//Instance declaration - DUT declaration
	scpu_top *scpu_top_inst;
    //Process to drive the inputs of DUT
    //Process declaration
	void RESET_GEN();
	//Constructor
	SC_CTOR (scpu_testbench)  {
	  //Instance creation and connection
	  scpu_top_inst = new scpu_top("scpu_top_inst");
	    scpu_top_inst->clk(clk);
	    scpu_top_inst->rst_n(rst_n);
	  //Load memory
	  #include "scpu_load_mem.h"
      //Process register
	  SC_THREAD (RESET_GEN);
	    sensitive << clk.pos();
	}
	//De-constructor
	~scpu_testbench (){	
    }
};

