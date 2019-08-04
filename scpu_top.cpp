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
	   scpu_decoder_inst.dc_output_socket.bind(scpu_fetch_inst.dc2fetch_socket);
	   scpu_decoder_inst.dc_output_socket.bind(scpu_execute_inst.dc2ex_socket);
	   scpu_execute_inst.ex2dc_socket.bind(scpu_decoder_inst.dc_input_socket);
	   scpu_fetch_inst.fetch2dc_socket.bind(scpu_decoder_inst.dc_input_socket);   
	   
	  //Create the instance FETCH
      scpu_fetch_inst.clk(clk);
      scpu_fetch_inst.rst_n(rst_n);
	  //Create the instance DECODER
	  scpu_decoder_inst.clk(clk);
	  scpu_decoder_inst.rst_n(rst_n);
	 //Create the instance EXECUTE
	}
};
