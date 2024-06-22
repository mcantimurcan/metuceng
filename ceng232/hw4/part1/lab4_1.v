`timescale 1ns / 1ps

module ROM (
    input [2:0] addr,
    output reg [7:0] dataOut
);
    always @(*) begin
        case (addr)
            3'b000: dataOut = 8'b00000000;
            3'b001: dataOut = 8'b00000001;
            3'b010: dataOut = 8'b00000010;
            3'b011: dataOut = 8'b00100011;
            3'b100: dataOut = 8'b11000100;
            3'b101: dataOut = 8'b01100101;
            3'b110: dataOut = 8'b00011110;
            3'b111: dataOut = 8'b01000101;
        endcase
    end
endmodule



module Bitwise_Manipulation_RAM (
    input mode,                     // 0 for write, 1 for read
    input [2:0] addr,               // RAM address
	input [1:0] operation,          // Operation code (AND, OR, XOR, NAND)
    input [7:0] dataIn,             // Input data
    input [7:0] romData,            // Data from ROM used in operations
    input CLK,                      // Clock signal
	output reg [7:0] dataOut        // Output data
);
    reg [7:0] ram [0:7];

    integer i;
    initial begin
        for (i = 0; i < 8; i = i + 1) begin
            ram[i] = 8'b0;
        end
    end
    
    always @(posedge CLK) begin
        if (mode == 0) begin 
            case (operation)
                2'b00: ram[addr] = dataIn & romData;
                2'b01: ram[addr] = dataIn | romData;
                2'b10: ram[addr] = dataIn ^ romData;
                2'b11: ram[addr] = ~(dataIn & romData);
            endcase
            dataOut = ram[addr];
        end
    end

    always @(*) begin
        if (mode == 1) begin
            dataOut = ram[addr];
        end
    end

endmodule



module Combined_Memory_System (
    input mode,
    input [2:0] systemAddr,
    input [7:0] dataIn,
    input [1:0] operation,
	input CLK,
    output [7:0] systemOutput
);
    ROM rom(
    .addr(systemAddr),
    .dataOut(romData)
    );

    Bitwise_Manipulation_RAM ram(
    .mode(mode),
    .addr(systemAddr),
    .operation(operation),
    .dataIn(dataIn),
    .romData(romData),
    .CLK(CLK),
    .dataOut(systemOutput)
    ); 
	 
endmodule

