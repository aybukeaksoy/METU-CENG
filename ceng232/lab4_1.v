// Code your design here
`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);


	
	reg [4:0] romreg[0:15];

	initial begin
		romreg[0]=5'b00000;
		romreg[1]=5'b00001;
		romreg[2]=5'b00110;
		romreg[3]=5'b00111;
		romreg[4]=5'b01011;
		romreg[5]=5'b01100;
		romreg[6]=5'b01101;
		romreg[7]=5'b01110;
		romreg[8]=5'b11101;
		romreg[9]=5'b11110;
		romreg[10]=5'b11111;
		romreg[11]=5'b10000;
		romreg[12]=5'b10111;
		romreg[13]=5'b11000;
		romreg[14]=5'b11001;
		romreg[15]=5'b11010;
	end 

	always@(romAddr)
	begin
		romOutput=romreg[romAddr];
	end
endmodule
																							
module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);

	


	reg [8:0] ramreg[0:15];
	integer i,k,count,arg;
	reg [8:0] result;
	reg [7:0] concat;

	initial begin
		count=0;
		result=0;
		ramOutput=0;
		concat=0;
		arg=0;
		for(i=0;i<16;i=i+1)
			ramreg[i]=0;
	end 

	always@(*)
	begin
		if(!ramMode) ramOutput=ramreg[ramAddr];
	
	end

	always@(posedge CLK)
	begin

		if(ramMode)
		begin
			
			case(ramArg)
		    
				2'b00: arg=1;
				2'b01: arg=2;
				2'b10: arg=-1;
				2'b11: arg=-2;
		    endcase

			if(ramOp)
			begin
				k=4;
              			for(i=4;i>0;i=i-1)
				begin
					if(ramInput[i]==0)
						count=count+(k*(arg**(k-1)));
					if(ramInput[i]==1)
						count=count-(k*(arg**(k-1)));
					k=k-1;
				end
			 
			end
			
			else
			begin
                			k=4;
              			for(i=4;i>=0;i=i-1)
				begin
					if(ramInput[i]==0)
						count=count+(arg**k);
					if(ramInput[i]==1)
						count=count-(arg**k);
					k=k-1;
				end	

			end	

			if(count>=0)
			begin
					concat=count;
					result={1'b0,concat};
			end
			else
			begin
					concat=-count;
		            result={1'b1,concat};
			end
			ramreg[ramAddr]=result;
			count=0;
			concat=0;
			result=0;
		end
    end
endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);


	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);



endmodule