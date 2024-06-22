`timescale 1ns / 1ps

module testbench_ic1337;
    // Inputs
    reg A0;
    reg A1;
    reg A2;
    reg clk;
    // Outputs
    wire Q0;
    wire Q1;
    wire Z;
	 
    // Input Pattern Memory
    reg [2:0] scrInputs[7:0]; // Scrambled inputs
    reg [2:0] incInputs[7:0]; // Incrementing inputs
    reg [2:0] decInputs[7:0]; // Decrementing inputs

    // Result Memory (for each type of input pattern)
    reg [2:0] resultsScr[7:0]; // Results for scrambled inputs
    reg [2:0] resultsInc[7:0]; // Results for incrementing inputs
    reg [2:0] resultsDec[7:0]; // Results for decrementing inputs
	 
	 integer grade = 0; // proposed grade
    integer i; // Loop iterator
    parameter INPUT_COMBINATIONS = 8;

    // Instantiate the Unit Under Test (UUT)
    ic1406 uut (
        .A0(A0),
        .A1(A1),
        .A2(A2),
        .clk(clk),
        .Q0(Q0),
        .Q1(Q1),
        .Z(Z)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // Toggle clock every 5 ns
    end

    initial begin
			
			
        // Initialize scrambled input patterns
        scrInputs[0] = 3'b010;
        scrInputs[1] = 3'b100;
        scrInputs[2] = 3'b110;
        scrInputs[3] = 3'b001;
        scrInputs[4] = 3'b000;
        scrInputs[5] = 3'b011;
        scrInputs[6] = 3'b111;
        scrInputs[7] = 3'b101;

        // Initialize incrementing input patterns
        incInputs[0] = 3'b000;
        incInputs[1] = 3'b001;
        incInputs[2] = 3'b010;
        incInputs[3] = 3'b011;
        incInputs[4] = 3'b100;
        incInputs[5] = 3'b101;
        incInputs[6] = 3'b110;
        incInputs[7] = 3'b111;

        // Initialize decrementing input patterns
        decInputs[0] = 3'b111;
        decInputs[1] = 3'b110;
        decInputs[2] = 3'b101;
        decInputs[3] = 3'b100;
        decInputs[4] = 3'b011;
        decInputs[5] = 3'b010;
        decInputs[6] = 3'b001;
        decInputs[7] = 3'b000;
		  
		  
		  // Need to fill-in the expected results, as in:
		  // resultsInc[i] = 3'bXYZ
		  resultsInc[0] = 3'b101;
		  resultsInc[1] = 3'b011;
		  resultsInc[2] = 3'b101;
		  resultsInc[3] = 3'b000;
		  resultsInc[4] = 3'b110;
		  resultsInc[5] = 3'b011;
		  resultsInc[6] = 3'b011;
		  resultsInc[7] = 3'b011;
		  
		  // resultsDec[i] = 3'bXYZ
		  resultsDec[0] = 3'b011;
		  resultsDec[1] = 3'b011;
		  resultsDec[2] = 3'b011;
		  resultsDec[3] = 3'b011;
		  resultsDec[4] = 3'b110;
		  resultsDec[5] = 3'b101;
		  resultsDec[6] = 3'b011;
		  resultsDec[7] = 3'b101;
		  		  
		  // resultsScr[i] = 3'bXYZ
		  resultsScr[0] = 3'b011;
		  resultsScr[1] = 3'b011;
		  resultsScr[2] = 3'b011;
		  resultsScr[3] = 3'b101;
		  resultsScr[4] = 3'b011;
		  resultsScr[5] = 3'b110;
		  resultsScr[6] = 3'b011;
		  resultsScr[7] = 3'b011;
		end

		initial begin
		  #6;		
		   //Enter to the loop 1 ms later
			if(Q0 !== 1'b1) $display("Wrong Q0[%b], should be 1", Q0);
         else grade = grade + 2;
         if(Q1 !== 1'b1) $display("Wrong Q1[%b], should be 1", Q1);
         else grade = grade + 2;
         //Do a one round check of all bits
         //w/e it checks.

		
		  $display("=============== INCREMENT Results - fill in resultsInc ===============");
        //==========================//
        //         INCREMENT        //
        //==========================//
        // FOR LOOP SHOULD START 1NS AFTER POSEDGE CLOCK
        // Run the clock check the provided input with compared output
        for(i = 0; i < INPUT_COMBINATIONS; i = i + 1)
        begin
            // Time: (n + 1)
            // Decompose the i to bits
				#5;
            A0 = incInputs[i][0];
            A1 = incInputs[i][1];
            A2 = incInputs[i][2];
            // Wait to next pos edge
				#5;
            //$display("Inp = %b, Res = %b, %b",incInputs[i],{Z, Q1, Q0}, clk);
            // Check the output
            if(Q0 !== resultsInc[i][0]) $display("Wrong Q0[%b], should be %b", Q0, resultsInc[i][0]);
            else grade = grade + 1;
            if(Q1 !== resultsInc[i][1]) $display("Wrong Q1[%b], should be %b", Q1, resultsInc[i][1]);
            else grade = grade + 1;
            if( Z !== resultsInc[i][2]) $display("Wrong  Z[%b], should be %b",  Z, resultsInc[i][2]);
            else grade = grade + 1;
            
        end
		  
		  $display("=============== DECREMENT Results - fill in resultsDec ===============");
        //==========================//
        //         DECREMENT        //
        //==========================//
        // FOR LOOP SHOULD START 1NS AFTER POSEDGE CLOCK
        // Run the clock check the provided input with compared output
        for(i = 0; i < INPUT_COMBINATIONS; i = i + 1)
        begin
            // Time: (n + 1)
            // Decompose the i to bits
				#5;
            A0 = decInputs[i][0];
            A1 = decInputs[i][1];
            A2 = decInputs[i][2];
            // Wait to next pos edge
				#5;
            //$display("Inp = %b, Res = %b, %b",decInputs[i],{Z, Q1, Q0}, clk);
            // Check the output
            if(Q0 !== resultsDec[i][0]) $display("Wrong Q0[%b], should be %b", Q0, resultsDec[i][0]);
            else grade = grade + 1;
            if(Q1 !== resultsDec[i][1]) $display("Wrong Q1[%b], should be %b", Q1, resultsDec[i][1]);
            else grade = grade + 1;
            if( Z !== resultsDec[i][2]) $display("Wrong  Z[%b], should be %b",  Z, resultsDec[i][2]);
            else grade = grade + 1;
            
        end		  
		  
		  $display("=============== SCRAMBLED Results - fill in resultsScr ===============");
        //==========================//
        //         SCRAMBLED        //
        //==========================//
        // FOR LOOP SHOULD START 1NS AFTER POSEDGE CLOCK
        // Run the clock check the provided input with compared output
        for(i = 0; i < INPUT_COMBINATIONS; i = i + 1)
        begin
            // Time: (n + 1)
            // Decompose the i to bits
				#5;
            A0 = scrInputs[i][0];
            A1 = scrInputs[i][1];
            A2 = scrInputs[i][2];
            // Wait to next pos edge
				#5;
            // $display("Inp = %b, Res = %b, %b",scrInputs[i],{Z, Q1, Q0}, clk);
            // Check the output
            if(Q0 !== resultsScr[i][0]) $display("Wrong Q0[%b], should be %b", Q0, resultsScr[i][0]);
            else grade = grade + 2;
            if(Q1 !== resultsScr[i][1]) $display("Wrong Q1[%b], should be %b", Q1, resultsScr[i][1]);
            else grade = grade + 2;
            if( Z !== resultsScr[i][2]) $display("Wrong  Z[%b], should be %b",  Z, resultsScr[i][2]);
            else grade = grade + 2;
            
        end		  
		  #1;
        $display("Result is:%d", grade);
		  $finish;
		  

    end
endmodule
