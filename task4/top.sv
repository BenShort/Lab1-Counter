module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic              clk,
    input logic              rst,
    input logic              en,
    output logic [WIDTH-1:0] count
);

always_ff @(posedge clk, posedge rst)
    if(rst) count <= {WIDTH{1'b0}}; //forms width bits of '0'
    else count <= count + {{WIDTH-1{1'b0}}, en}; //adds width-1 digits of binary 0's and then adds the enable
endmodule


module top #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             en,       // enable
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [11:0]      bcd       // count output
);

  logic  [WIDTH-1:0]       count;    // interconnect wire

counter myCounter (
  .clk (clk),
  .rst (rst),
  .en (en),
  .count (count)
);

bin2bcd myDecoder (
  .x (count),
  .BCD (bcd)
);

endmodule

