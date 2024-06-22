`timescale 1ns / 1ps

module testbench;

    // IO
	 reg CLK; real result=0;
	 /*for ROM */
	 reg [2:0] ROM_Addr; wire [7:0] ROM_Res;
	 /*Bitwise_Manipulation_RAM*/ 
	 reg RAM_mode; reg [2:0] RAM_Addr; reg [7:0] RAM_dataIn; reg [1:0] RAM_operation; reg [7:0] RAM_romData; wire [7:0] RAM_dataOut;
	 /*Combined_Memory_System*/
	 reg System_mode; reg [2:0] System_Addr; reg [7:0] System_dataIn; reg [1:0] System_operation; wire [7:0] System_output;

	 // instantiate ROM
    ROM rom(
        .addr(ROM_Addr),
        .dataOut(ROM_Res)
    );
	 
	 // instantiate RAM
	 Bitwise_Manipulation_RAM ram(
        .mode(RAM_mode),
        .addr(RAM_Addr),
		  .operation(RAM_operation),
        .dataIn(RAM_dataIn),
        .romData(RAM_romData),
		  .CLK(CLK),
        .dataOut(RAM_dataOut)
    );
	 
	 // Instantiate Combined_Memory_System 
	Combined_Memory_System memory(
		 .mode(System_mode),
		 .systemAddr(System_Addr),
		 .dataIn(System_dataIn),
		 .operation(System_operation),
		 .CLK(CLK),
		 .systemOutput(System_output)
	);
	
	
		//Set initial values
		initial CLK = 0;
		always #5 CLK = ~CLK;	
		// to hold the expected binary results of bitwise ops
		reg [7:0] expected_result;

	
		initial begin
			
			//////////////////
			//// ROM TEST ////
			//////////////////
			#1
			ROM_Addr = 3'b000;
			#1
			if(ROM_Res == 8'b00000000)  result=result+1; else $display("Error in case 1"); /*case 1*/
			$display("1-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b001;
			#1
			if(ROM_Res == 8'b00000001)  result=result+1; else $display("Error in case 2"); /*case 2*/
			$display("2-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b010;
			#1
			if(ROM_Res == 8'b00000010)  result=result+1; else $display("Error in case 3"); /*case 3*/
			$display("3-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b011;
			#1
			if(ROM_Res == 8'b00100011)  result=result+1; else $display("Error in case 4"); /*case 4*/
			$display("4-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b100;
			#1
			if(ROM_Res == 8'b11000100)  result=result+1; else $display("Error in case 5"); /*case 5*/
			$display("5-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b101;
			#1
			if(ROM_Res == 8'b01100101)  result=result+1; else $display("Error in case 6"); /*case 6*/
			$display("6-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b110;
			#1
			if(ROM_Res == 8'b00011110)  result=result+1; else $display("Error in case 7"); /*case 7*/
			$display("7-ROM_Res: %b", ROM_Res);
			#1
			ROM_Addr = 3'b111;
			#1
			if(ROM_Res == 8'b01000101)  result=result+1; else $display("Error in case 8"); /*case 8*/
			$display("8-ROM_Res: %b", ROM_Res);
			
			$display(" ");
			
			//////////////////
			//// RAM TEST ////
			//////////////////
			#6
			RAM_mode=1'b1;//read mode
			RAM_Addr = 3'b001;
			#2
			if(RAM_dataOut == 0) result=result+1; else $display("Error in case 9"); /*case 9*/
			$display("9-RAM_dataOut: %b", RAM_dataOut);
			
			// Test writing to RAM w/ AND operation
			#10
			RAM_Addr = 3'b111;
			RAM_operation = 2'b00; // AND
			RAM_dataIn = 8'b11010111;
			RAM_romData = 8'b01010111;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#1
			if(RAM_dataOut == (RAM_dataIn & RAM_romData)) result=result+1; else $display("Error in case 10"); /*case 10*/
			$display("10-RAM_dataOut: %b --- %b, ---> %b", RAM_dataOut, RAM_dataIn & RAM_romData, RAM_dataOut == (RAM_dataIn & RAM_romData));
			
			// Test writing to RAM w/ OR operation
			#10
			RAM_Addr = 3'b101;
			RAM_operation = 2'b01; // OR
			RAM_dataIn = 8'b11111111;
			RAM_romData = 8'b10000101;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#1
			if(RAM_dataOut == (RAM_dataIn | RAM_romData)) result=result+1; else $display("Error in case 11"); /*case 11*/
			$display("11-RAM_dataOut: %b --- %b, ---> %b", RAM_dataOut, RAM_dataIn | RAM_romData, RAM_dataOut == (RAM_dataIn | RAM_romData));
			
			// Test writing to RAM w/ XOR operation
			#10
			RAM_Addr = 3'b011;
			RAM_operation = 2'b10; // XOR
			RAM_dataIn = 8'b11111000;
			RAM_romData = 8'b01100101;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#1
			if(RAM_dataOut == (RAM_dataIn ^ RAM_romData)) result=result+1; else $display("Error in case 12"); /*case 12*/
			$display("12-RAM_dataOut: %b --- %b, ---> %b", RAM_dataOut, RAM_dataIn ^ RAM_romData, RAM_dataOut == (RAM_dataIn ^ RAM_romData));
			
			// Test writing to RAM w/ NAND operation
			#10
			RAM_Addr = 3'b110;
			RAM_operation = 2'b11; // NAND
			RAM_dataIn = 8'b11111000;
			RAM_romData = 8'b01100101;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#1
			if(RAM_dataOut == ~(RAM_dataIn & RAM_romData)) result=result+1; else $display("Error in case 13"); /*case 13*/
			$display("13-RAM_dataOut: %b --- %b, ---> %b", RAM_dataOut, ~(RAM_dataIn & RAM_romData), RAM_dataOut == ~(RAM_dataIn & RAM_romData));
			
			
			#20
			$display("Result is:%2.2f",result); // MAX 13
			$finish;
			
			
			
			
		end
		

		



endmodule
