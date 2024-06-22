`timescale 1ns / 1ps

module ac_flip_flop(
    input A,
    input C,
    input clk,
    output reg Q
);

    initial begin
        Q = 1;
    end

    always @ (posedge clk)
                begin
                        if (A == 0 && C == 0) Q = 1;
                        else if (A == 0 && C == 1) Q = ~Q;
                        else if (A == 1 && C == 1) Q = 1;
                        else Q = Q;
                end

endmodule

module ic1406(
    input A0,
    input A1,
    input A2,
    input clk,
    output Q0,
    output Q1,
    output Z
);
	wire w1, w2, w3, w4, w5;

    assign w1 = A0 ^ A1;
    assign w2 = w1 | ~A2;
    assign w3 = A0 && A1;
    assign w4 = ~A0 | ~A1;
    assign w5 = w4 && ~A2;

    ac_flip_flop ac1(~w2, w3, clk, Q0);
    ac_flip_flop ac2(w3, w5, clk, Q1);
	
    assign Z = Q0 ^ Q1;
endmodule

