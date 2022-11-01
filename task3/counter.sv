module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic              clk,
    input logic              rst,
    input logic              en,
    input logic              direction,
    input logic [WIDTH-1:0]  load,
    output logic [WIDTH-1:0] count
);

always_ff @(posedge clk, posedge rst)
    if(rst) count <= load; //forms width bits of '0'
    else if (direction == 0'b1) begin
        count <= count + {{WIDTH-1{1'b0}}, en}; //adds width-1 digits of binary 0's and then adds the enable
    end
    else begin
        if (en == 1'b1) begin
            count <= count + {{WIDTH-1{1'b1}}, en};
        end
        else begin
            count <= count;
        end
    end


endmodule-

