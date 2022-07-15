`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

    //================//
    // INITIAL BLOCK  //
    //================//
    //Modify the lines below to implement your design
    reg [2:0] opcodes[0:31];
    reg [3:0] values[0:31];
    reg [9:0] p1;
    reg [9:0] p0;
    integer opcode_count;
    integer start_index;
    integer i;
    integer temp;

    initial begin

        // ...
        temp=0;
        overflow=0;
        cacheFull=0;
        invalidOp=0;
        result=0;
        opcode_count=0;
        start_index=0;
        p1=0;
        p0=0;
        i=start_index;
 
    end

    //================//
    //      LOGIC     //
    //================//
    //Modify the lines below to implement your design
    always @(posedge clk or posedge reset)
    begin
        if (reset)
        begin
            
            temp=0;
            overflow=0;
            cacheFull=0;
            invalidOp=0;
            result=0;
            opcode_count=0;
            start_index=0;
            p1=0;
            p0=0;
            i=start_index;

        end
        else
        begin
            if(!mode)
            begin
                if(opcode_count==32)    cacheFull=1;
                else
                begin
                    if(opCode==0)
                    begin
                        invalidOp=0; 
                        opcodes[opcode_count]=3'b000;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else if (opCode==1)
                    begin
                        invalidOp=0;
                        opcodes[opcode_count]=3'b001;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else if (opCode==2)
                    begin
                        invalidOp=0;
                        opcodes[opcode_count]=3'b010;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else if (opCode==4)
                    begin
                        invalidOp=0;
                        opcodes[opcode_count]=3'b100;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else if (opCode==5)
                    begin
                        invalidOp=0;
                        opcodes[opcode_count]=3'b101;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else if (opCode==6)
                    begin
                        invalidOp=0;
                        opcodes[opcode_count]=3'b110;
                        values[opcode_count]=value;
                        opcode_count=opcode_count+1;
                    end
                    else invalidOp=1;
                end

            end

            else if(mode && opcode_count)
            begin
                if(opcodes[i]==0)
                begin
                    if(p0+values[i]>=1024)  overflow=1;
                    else overflow=0;
                    temp=p0;
                    result=p0+values[i];
                    p0=result;
                    p1=temp;
                end
                else if (opcodes[i]==1)
                begin
                    if(p0+values[i]+p1>=1024)  overflow=1;
                    else overflow=0;
                    temp=p0;
                    result=p0+values[i]+p1;
                    p0=result;
                    p1=temp;
                end
                else if (opcodes[i]==2)
                begin
                    if(p0*p1+values[i]>=1024)  overflow=1;
                    else overflow=0;
                    temp=p0;
                    result=p0*p1+values[i];
                    p0=result;
                    p1=temp;
                end
                else if (opcodes[i]==4)
                begin
                    temp=p0;
                    overflow=0;
                    result=p0[0]+p0[1]+p0[2]+p0[3]+p0[4]+p0[5]+p0[6]+p0[7]+p0[8]+p0[9];
                    p0=result;
                    p1=temp;
                end
                else if (opcodes[i]==5)
                begin
                    temp=p0;
                    overflow=0;
                    result={p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6],p0[7],p0[8],p0[9]};
                    p0=result;
                    p1=temp;
                end
                else if (opcodes[i]==6)
                begin
                    start_index=values[i];
                end
                i=i+1;
                if(i==opcode_count) i=start_index;
            end
        end
    end
endmodule
