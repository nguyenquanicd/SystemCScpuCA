//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------
#include "scpu_top.cpp"
SC_MODULE (scpu_testbench) {
	//Ports and signals
	sc_in <bool> clk;
	sc_signal <bool> rst_n;
	//
	scpu_top *scpu_top_inst;
    //
	void RESET_GEN();
	//Constructor
	SC_CTOR (scpu_testbench)  {
	  //
	  scpu_top_inst = new scpu_top("scpu_top_inst");
	    scpu_top_inst->clk(clk);
	    scpu_top_inst->rst_n(rst_n);
	    //Load memory
		#include "scpu_load_mem.h"
        //
	    SC_THREAD (RESET_GEN);
	      sensitive << clk.pos();
	}
	//Destructor
	~scpu_testbench (){	
	   delete scpu_top_inst;
    }
};

