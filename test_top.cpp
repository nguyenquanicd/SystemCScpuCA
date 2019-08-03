#include <iostream>
#include "scpu_testbench.cpp"

int sc_main (int argc, char* argv[]) {
  //1. Internal signal declaration
  sc_signal <bool> rst_n;
  //2. Create the clock 
  //Cycle: 2 ns
  //Duty cycle: 50%
  sc_clock clk("clk", 2, SC_NS, 0.5);
  //3. Instances
  scpu_testbench scpu_testbench_inst("scpu_testbench_inst");
    scpu_testbench_inst.clk(clk);
  //4. Create VCD file to trace
  #include "scpu_trace.h"
  //5. Start simulation
  cout << "3.Start simulation" << endl;
  int count = 0;
  for (int i = 0; i < 100; i++) {
    sc_start(2, SC_NS); //One cycle
  }
  //6. Close the waveform file
  sc_close_vcd_trace_file (scpu_waveform);
  //7. END
  return 0;
}
