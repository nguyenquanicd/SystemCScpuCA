//--------------------------------------
//Project: Simple CPU
//Module:  SPCU Testbench - body file
//Function: Provide input for CPU
//Author:  Truong Cong Hoang Viet
//Page:    VLSI Technology
//--------------------------------------

#include "scpu_testbench.h"

void scpu_testbench::RESET_GEN(){
  rst_n.write(0);
  wait(8,SC_NS);
  rst_n.write(1);	
}