`timescale 1ns / 1ps



module lab3_2(
			input[4:0] smartCode,
			input CLK, 
			input lab, //0:Digital, 1:Mera
			input [1:0] mode, //00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,//1:show warning, 0:do not show warning
			output reg isFullMera, //1:full, 0:not full
			output reg isEmptyMera, //1: empty, 0:not empty
			output reg unlockMera,	//1:door is open, 0:closed
			output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
			output reg isFullDigital, //1:full, 0:not full
			output reg isEmptyDigital, //1: empty, 0:not empty
			output reg unlockDigital //1:door is open, 0:closed
	);
	 
	// You may declare your variables below	
	
	integer count;
	integer i;
	
	initial begin
			numOfStuInMera=0;
			numOfStuInDigital=0;
			restrictionWarnMera=0;
			isFullMera=0;
			isEmptyMera=1'b1;
			unlockMera=0;		
			restrictionWarnDigital=0;
			isFullDigital=0;
			isEmptyDigital=1'b1;
			unlockDigital=0;
			count=0;
			i=0;
	end

	//Modify the lines below to implement your design
	always @(posedge CLK) 
	begin


         	if(mode==1 && lab) 
		begin
			restrictionWarnDigital=0;
			unlockDigital = 0;
                 	if(isFullMera) 
			begin
				unlockMera = 0;
				restrictionWarnMera=0;
			end

			else if(numOfStuInMera<15) 
			begin
				unlockMera = 1;
				restrictionWarnMera=0;
				if(numOfStuInMera==0)
				begin
					numOfStuInMera=numOfStuInMera+1;
					isEmptyMera=0;	
				end
				else
					numOfStuInMera=numOfStuInMera+1;
					
			end
                          
			else
			begin
				for(i=0;i<5;i=i+1)
					count=count+smartCode[i];
				if (count%2==0)
				begin
					unlockMera=1;
					restrictionWarnMera=0;
					if(numOfStuInMera==29)
					begin 
						numOfStuInMera=numOfStuInMera+1;
						isFullMera=1;
					end
					else
						numOfStuInMera=numOfStuInMera+1;
						
				end
				else
				begin
					unlockMera = 0;
					restrictionWarnMera=1;
				end
				count=0;
			end 
		end


		
		
		else if(mode==1 && !lab) 
		begin
			restrictionWarnMera=0;
			unlockMera = 0;
                 	if(isFullDigital) 
			begin
				unlockDigital = 0;
				restrictionWarnDigital=0;
			end

			else if(numOfStuInDigital<15) 
			begin
				unlockDigital = 1;
				restrictionWarnDigital=0;
				if(numOfStuInDigital==0)
				begin
					numOfStuInDigital=numOfStuInDigital+1;
					isEmptyDigital=0;
				end
				else
					numOfStuInDigital=numOfStuInDigital+1;
			end
                          
			else
			begin
				for(i=0;i<5;i=i+1)
					count=count+smartCode[i];
				if (count%2==1)
				begin
					unlockDigital=1;
					restrictionWarnDigital=0;
					if(numOfStuInDigital==29)
					begin 
						numOfStuInDigital=numOfStuInDigital+1;
						isFullDigital=1;
					end
					else
						numOfStuInDigital=numOfStuInDigital+1;
				end
				else
				begin
					unlockDigital = 0;
					restrictionWarnDigital=1;
				end
				count=0;
			end 
		end
		
		
		
		
		else if(mode==0 && lab && !isEmptyMera)
		begin
			restrictionWarnDigital=0;	
			unlockMera=1;
			unlockDigital=0;
			restrictionWarnMera=0;
			if (numOfStuInMera==1)
			begin
				numOfStuInMera=numOfStuInMera-1;
				isEmptyMera=1;
			end
			else if (numOfStuInMera==30)
			begin
				numOfStuInMera=numOfStuInMera-1;
				isFullMera=0;
			end
			else
				numOfStuInMera=numOfStuInMera-1;
		end

		
		
		
		else if(mode==0 && !lab && !isEmptyDigital)
		begin
			restrictionWarnMera=0;
			unlockDigital=1;
			unlockMera=0;
			restrictionWarnDigital=0;
			if (numOfStuInDigital==1)
			begin
				numOfStuInDigital=numOfStuInDigital-1;
				isEmptyDigital=1;
			end
			else if (numOfStuInDigital==30)
			begin
				numOfStuInDigital=numOfStuInDigital-1;
				isFullDigital=0;
			end
			else
				numOfStuInDigital=numOfStuInDigital-1;
		end

		
		
		
		else
		begin
			
			unlockMera=0;
			unlockDigital=0;
			restrictionWarnMera=0;
			restrictionWarnDigital=0;

		end
            	
       end
	
endmodule

