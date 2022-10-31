#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //inint top verilog instance
    Vcounter* top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    //initialize sim input
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    int nine_count = 0;

    //run sims for many clock cycles
    for (i = 0; i < 300; i++) {
        //dump vars into VCD and toggle clock
        for (clk = 0; clk<2; clk++){
            tfp->dump (2*i+clk); //unit in ps
            top->clk = !top->clk;
            top->eval ();
        }

        if((top->count == 9) && (nine_count < 2)){
            nine_count = nine_count + 1;
            top->rst = 0;
            top->en = 0;
        }
        else{
            top->rst = (i<2) | (i == 30);
            top->en = (i>4);
        }
        
        
        
        
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
    
}