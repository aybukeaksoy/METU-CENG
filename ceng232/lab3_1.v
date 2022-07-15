`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);

    initial Q = 0;
    
    always@(posedge clk)
    begin
         if(!A && !B) Q<=Q;
         else if(!A && B) Q<=1;
         else if(A && !B) Q<=0;
         else if(A && B) Q<=!Q;
    end

    // You can implement your code here
    // ...

endmodule

module ic1337(// Inputs
              input I0,
              input I1,
              input I2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);
              
    // You can implement your code here
    // ...
             wire D0,D1,F0,F1;
	     

             assign D0=~(I0 | ~I1) & ~I2;
             assign D1=~(I2 | ~I1) ~^ I0;
             
             ab ff0(D0,I2,clk,F0);
             ab ff1(~I2,D1,clk,F1);
             assign Q0=F0;
             assign Q1=F1;
             assign Z=F0^F1;

endmodule
