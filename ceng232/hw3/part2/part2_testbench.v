`timescale 1ns / 1ps

module SeatingSystemTestbench;
    // Inputs
    reg [5:0] money;
    reg CLK;
    reg plugAvailability;
    reg [1:0] selectedArea;

    // Outputs
    wire [5:0] moneyLeft;
    wire [4:0] seatLeft;
    wire seatUnavailable;
    wire insufficientFund;
    wire notExactFund;
    wire invalidPlugSeat;
    wire plugSeatUnavailable;
    wire seatReady;
	 
	 // Vars for test
	 integer grade,i, gradeLocal;
    reg caseFailed;

    // Instantiate the Unit Under Test (UUT)
     lab3_2 SeatingSystem (
        .money(money),
        .CLK(CLK),
        .plugAvailability(plugAvailability),
        .selectedArea(selectedArea),
        .moneyLeft(moneyLeft),
        .seatLeft(seatLeft),
        .seatUnavailable(seatUnavailable),
        .insufficientFund(insufficientFund),
        .notExactFund(notExactFund),
        .invalidPlugSeat(invalidPlugSeat),
        .plugSeatUnavailable(plugSeatUnavailable),
        .seatReady(seatReady)
    );

    // Clock generation
    initial CLK = 1;
	 always #5 CLK = ~CLK;

    // Test scenarios
	 initial begin
		 $display("Starting Testbench");
		 grade = 0;
		 caseFailed = 1;
			
		 /////////////////////////////////////
		 //////// TESTS FOR LOUD AREA ////////
		 /////////////////////////////////////
	 
		 // Test Case 1: Attempt to reserve a seat with plug in the Loud area - invalidPlugseat
		 // No seatLeft and moneyLeft checks ??
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 1; 
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (seatLeft == 15) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 1");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 1");
		 grade = grade + gradeLocal;
		 

		 
		 /////////////////////////////////////
		 //////// TESTS FOR QUIET AREA ///////
		 /////////////////////////////////////
		 
		 // Test Case 5: Successfully reserve a seat with plug from the quiet area
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 //$display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 9) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5");
		 grade = grade + gradeLocal;

		 /////////////////////////////////////
		 ///// TESTS FOR INDIVIDUAL AREA /////
		 /////////////////////////////////////
		 
		 // Test Case 11: ATTEMPY TO RESERVE W INSUFFICIENT MONEY
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 3;
		 #10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 20) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11");
		 grade = grade + gradeLocal; 
		 
		 
		 

	end



endmodule
