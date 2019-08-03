//--------------------------------------
//Project:  Simple CPU
//Module:   Decoder
//Function: All declarations of decoder
//Author:   Truong Cong Hoang Viet - Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------
//
//MEMORY
//
#include "systemc.h"
#include "scpu_define.h"

SC_MODULE (scpu_decoder) {
	//Input
	sc_in<bool> clk;
	sc_in<bool> rst_n;
	sc_in<sc_uint<8> > fetch_ir;
	sc_in<sc_uint<8> > fetch_dr;
	sc_in<sc_uint<8> > fetch_mem_dout;
	sc_in<sc_uint<9> > ex_dout; //Note: 9 bits
	//Output
    sc_out<bool>	  dc_load_pc;
    sc_out<bool>	  dc_imm;
    sc_out<bool>	  dc_mem_wr;
    sc_out<bool>	  dc_load_dr;
    sc_out<bool>	  dc_load_ir;
    sc_out<sc_uint<2> >	    dc_addr_sel;
    sc_out<sc_uint<9> >     dc_rs; //Note: 9 bits
    sc_out<sc_uint<9> >     dc_rd; //Note: 9 bits
    sc_out<sc_uint<2> >     dc_op;
    //Internal signals
    sc_signal<sc_uint<2> > ctrl_counter_next;
    sc_signal<sc_uint<9> > reg_in; //Note: 9 bits
    sc_signal<sc_uint<9> > reg0;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg1;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg2;   //Note: 9 bits
	sc_signal<sc_uint<9> > reg3;   //Note: 9 bits
	sc_signal<sc_uint<9> > dc_rs_reg; //Note: 9 bits
    sc_signal<sc_uint<9> > dc_rd_reg; //Note: 9 bits
    sc_signal<sc_uint<2> > ctrl_counter;
	sc_signal<sc_uint<4> > load_reg;
    sc_signal<bool>  clr_counter;
    sc_signal<bool>  jump_en;
    sc_signal<bool>  load_reg_en;
    sc_signal<bool>	  dc_load_dr_tmp;
    sc_signal<bool>   dc_load_ir_tmp;
    //
    //Method declaration
    //
    //Control counter
	void CLR_COUNTER_COMP();
	void CTRL_COUNTER_COMP();
	void CTRL_COUNTER_FF();
	void DC_LOAD_PC_COMP();
	// decoder block 3: dc_imm
	void JUMP_EN_COMP();
	void DC_IMM_COMP();
	// decoder block 4: dc_addr_sel
	void DC_ADDR_SEL_COMP();
	void RS_SEL();
	void RS_OUTPUT();
	void RD_SEL();
	void RD_OUTPUT();
	void REG_WE();
	void REG_WE_SEL();
	void REG_IN_SEL();
	void LOAD_DTA_TO_REG();
	// decoder block 6: dc_load_dr
	void DC_LOAD_DR_COMP();
    void DC_LOAD_DR_OUTPUT();
	// decoder block 7: dc_load_ir
	void DC_LOAD_IR_COMP();
	void DC_LOAD_IR_OUTPUT();
	// decoder block 8: dc_op
	void DC_OP_COMP();
	// decoder block 9: dc_mem_wr
	void DC_MEM_WR_COMP();
    //
    //Constructor
    //
	SC_CTOR(scpu_decoder) {
		SC_METHOD(RS_SEL);
		  sensitive << fetch_ir;
		  sensitive << reg0;
		  sensitive << reg1;
		  sensitive << reg2;
		  sensitive << reg3;
		SC_METHOD(RS_OUTPUT);
		  sensitive << dc_rs_reg;
		//
		SC_METHOD(RD_SEL);
		  sensitive << fetch_ir;
		  sensitive << reg0;
		  sensitive << reg1;
		  sensitive << reg2;
		  sensitive << reg3;
		SC_METHOD(RD_OUTPUT);
		  sensitive << dc_rd_reg;
		//
		SC_METHOD(REG_WE);
		  sensitive << fetch_ir;
		  sensitive << ctrl_counter;
		
		SC_METHOD(REG_WE_SEL);
		  sensitive << fetch_ir;
		  sensitive << load_reg_en;
		//
		SC_METHOD(REG_IN_SEL);
		  sensitive << fetch_ir;
		  sensitive << ex_dout;
		  sensitive << dc_rs_reg;
		  sensitive << fetch_dr;
		  sensitive << fetch_mem_dout;
		//
		SC_METHOD(LOAD_DTA_TO_REG);
		  sensitive << clk.pos();
        // decoder block 2: dc_load_pc
        SC_METHOD( CLR_COUNTER_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        //
        SC_METHOD( CTRL_COUNTER_COMP );
          sensitive << clr_counter;
          sensitive << ctrl_counter;
        //
        SC_METHOD( CTRL_COUNTER_FF );
          sensitive << clk.pos();
        //
        SC_METHOD( DC_LOAD_PC_COMP );
          sensitive << dc_load_ir;
          sensitive << dc_load_dr_tmp;
        // decoder block 3: dc_imm
        SC_METHOD( JUMP_EN_COMP );
          sensitive << fetch_ir;
          sensitive << dc_rd;
        //
        SC_METHOD( DC_IMM_COMP );
          sensitive << jump_en;
          sensitive << ctrl_counter;
        // decoder block 4: dc_addr_sel
        SC_METHOD( DC_ADDR_SEL_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        // decoder block 6: dc_load_dr
        SC_METHOD( DC_LOAD_DR_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
        //
        SC_METHOD (DC_LOAD_DR_OUTPUT);
          sensitive << dc_load_dr_tmp; 
        // decoder block 7: dc_load_ir
        SC_METHOD(DC_LOAD_IR_COMP);
          sensitive << clr_counter;
        //
        SC_METHOD(DC_LOAD_IR_OUTPUT);
          sensitive << dc_load_ir_tmp;
        // decoder block 8: dc_op
        SC_METHOD( DC_OP_COMP );
          sensitive << fetch_ir;
        // decoder block 9: dc_mem_wr
        SC_METHOD( DC_MEM_WR_COMP );
          sensitive << fetch_ir;
          sensitive << ctrl_counter;
	}
};
