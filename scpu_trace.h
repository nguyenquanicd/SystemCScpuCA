//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
//START
sc_trace_file *scpu_waveform =  sc_create_vcd_trace_file("scpu_waveform");
  if(scpu_waveform==NULL) cout<<"1. Cannot create the waveform file"<< endl;
  else cout << "2. Create the waveform file - " << scpu_waveform << endl;
//
//SCPU_FETCH
//
//Ports
//inputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.clk, "fetch.clk");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.rst_n, "fetch.rst_n");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_load_pc, "fetch.dc_load_pc");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_addr_sel, "fetch.dc_addr_sel");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_rs, "fetch.dc_rs");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_rd, "fetch.dc_rd");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_mem_wr, "fetch.dc_mem_wr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_load_dr, "fetch.dc_load_dr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.dc_load_ir, "fetch.dc_load_ir");
//ouputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.fetch_ir, "fetch.fetch_ir");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.fetch_dr, "fetch.fetch_dr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.fetch_mem_dout, "fetch.fetch_mem_dout");
//Internal signals
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.mem_dout,"fetch.mem_dout");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.pc,"fetch.pc");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.mem_addr,"fetch.mem_addr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.fetch_dr_in,"fetch.fetch_dr_in");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_fetch_inst.mem_array[60],"fetch.mem_array_60");
//
//SCPU_DECODER
//
//inputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.clk,"decoder.clk");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.rst_n,"decoder.rst_n");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.fetch_ir,"decoder.fetch_ir");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.fetch_dr,"decoder.fetch_dr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.fetch_mem_dout,"decoder.fetch_mem_dout");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.ex_dout,"decoder.ex_dout");
//ouputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_load_pc,"decoder.dc_load_pc");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_imm,"decoder.dc_imm");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_mem_wr,"decoder.dc_mem_wr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_load_dr,"decoder.dc_load_dr");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_load_ir,"decoder.dc_load_ir");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_addr_sel,"decoder.dc_addr_sel");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_rs,"decoder.dc_rs");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_rd,"decoder.dc_rd");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_op,"decoder.dc_op");
//Internal signals
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.ctrl_counter_next,"decoder.ctrl_counter_next");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.reg_in,"decoder.reg_in");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.ctrl_counter,"decoder.ctrl_counter");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.load_reg,"decoder.load_reg");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.reg0,"decoder.reg0");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.reg1,"decoder.reg1");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.reg2,"decoder.reg2");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.reg3,"decoder.reg3");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.clr_counter,"decoder.clr_counter");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.jump_en,"decoder.jump_en");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.load_reg_en,"decoder.load_reg_en");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_load_dr_tmp,"decoder.dc_load_dr_tmp");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_load_ir_tmp,"decoder.dc_load_ir_tmp");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_rs_reg,"decoder.dc_rs_reg");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_decoder_inst.dc_rd_reg,"decoder.dc_rd_reg");
//
//SCPU_EXECUTE
//
//inputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_execute_inst.dc_rs,"execute.dc_rs");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_execute_inst.dc_rd,"execute.dc_rd");
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_execute_inst.dc_op,"execute.dc_op");
//ouputs
sc_trace(scpu_waveform, scpu_testbench_inst.scpu_top_inst->scpu_execute_inst.ex_dout,"execute.ex_dout");
//Internal signals

//END