`timescale 1ns / 1ps

module Board232 (
	input mclk,
	input wire [3:0] btn,
	input wire [7:0] sw,
	output wire [7:0] led,
	output reg [6:0] seg,
	output reg [3:0] an,
	output dp,
	output [2:1] OutBlue,
	output [2:0] OutGreen,
	output [2:0] OutRed,
	output HS,
	output VS
    );
	assign dp = 1'b1;
	//assign led[4:4]=0;
	initial begin
			seg[6:0] = 7'b0111111;
			an[3:0]  = 4'b1111;
	end
 
	// adjust board clock
	reg [26:0] mclk_counter;
	initial mclk_counter<= 0;
	always @(posedge mclk) mclk_counter = mclk_counter+1;
	// select clock : 26->slower | 24->faster
	reg clk;
	initial clk = 1'b0;
	always@(btn[3] or mclk_counter[25] or btn[0]) 
	begin
		if(btn[3]) 
			clk = mclk_counter[25];
		else 
			clk = btn[0];
	end
	
	wire [5:0] moneyLeft;
	wire [5:0] seatLeft;
	reg [7:0] tmp_digit;
	lab3_2 HH (
		   sw[7:3], // money
			clk,
			sw[2:1], //selectedArea
			sw[0], // plugAvailability
			moneyLeft,
			seatLeft,			
			led[7],//seatUnavailable
			led[6],//insufficientFund
			led[5],//notExactFund
			led[4], //invalidPlugSeat
			led[3],//plugSeatUnavailable
			led[2]//seatReady
	);

	always @(mclk_counter[18:17])
	begin
		case (mclk_counter[18:17])
			2'b00:
				begin
					an = 4'b1110;
					if (seatLeft>=30)
						tmp_digit = seatLeft - 30;
					else if (seatLeft>=20) 
						tmp_digit = seatLeft - 20;
					else if (seatLeft>=10 && seatLeft <20)
						tmp_digit = seatLeft - 10;
					else
						tmp_digit = seatLeft;
				end
			2'b01:
				begin
					an = 4'b1101;
					if (seatLeft>=30)
						tmp_digit = 3;
					else if (seatLeft>=20)
						tmp_digit = 2;
					else if (seatLeft>=10 && seatLeft<20)
						tmp_digit = 1;
					else
						tmp_digit = 0;
				end
			2'b10:
				begin
					an = 4'b1011;
					if (moneyLeft>=30)
						tmp_digit = moneyLeft - 30;
					else if (moneyLeft>=20) 
						tmp_digit = moneyLeft - 20;
					else if (moneyLeft>=10 && moneyLeft <20)
						tmp_digit = moneyLeft - 10;
					else
						tmp_digit = moneyLeft;
				end
			default:
				begin
					an = 4'b0111;
					if (moneyLeft>=30)
						tmp_digit = 3;
					else if (moneyLeft>=20) 
						tmp_digit = 2;
					else if (moneyLeft>=10 && moneyLeft <20)
						tmp_digit = 1;
					else
						tmp_digit = 0;
				end
		endcase
		
		case (tmp_digit)
			4'd0: seg <= ~7'h3F;
			4'd1: seg <= ~7'h06;
			4'd2: seg <= ~7'h5B;
			4'd3: seg <= ~7'h4F;
			4'd4: seg <= ~7'h66;
			4'd5: seg <= ~7'h6D;
			4'd6: seg <= ~7'h7D;
			4'd7: seg <= ~7'h07;
			4'd8: seg <= ~7'h7F;
			4'd9: seg <= ~7'h6F;
			4'd10: seg <= ~7'h77;
			4'd11: seg <= ~7'h7C;
			4'd12: seg <= ~7'h39;
			4'd13: seg <= ~7'h5E;
			4'd14: seg <= ~7'h79;
			4'd15: seg <= ~7'h71;
			default: seg <= ~7'b0000000;
		endcase
		
	end
	
	// VGA
	assign OutBlue = 0;
	assign OutGreen = 0;
	assign OutRed = 0;
	assign HS = 0;
	assign VS = 0;

endmodule
