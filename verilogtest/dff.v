module dff(q, d, clk);
input d, clk;
output q;
initial q <= 0;
always @(posedge clk) q <= d;
endmodule

module abc();