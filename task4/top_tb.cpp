#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //inint top verilog instance
    Vtop* top = new Vtop;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("top.vcd");

    //init vbuddy
    if(vbdOpen()!=1) return (-1);
    vbdHeader("Lab1: top");

    //initialize sim input
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->direction = 1;
    top->load = 0;
    vbdSetMode(1);

    bool loaded = false;
    


    //run sims for many clock cycles
    for (i = 0; i < 30000; i++) {
        
        for (clk = 0; clk<2; clk++){
            tfp->dump (2*i+clk); //unit in ps
            top->clk = !top->clk;
            top->eval ();
        }
        //send counter to vbuddy

        /**
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);
        //end output section
        **/

       vbdPlot(int(top->bcd), 0, 255);

       

        top->rst = (i<2) | (i == 30);
        top->en = (i>4);
        
        
        if (Verilated::gotFinish()) exit(0);
        
    }
    vbdClose();
    tfp->close();
    exit(0);
    
}