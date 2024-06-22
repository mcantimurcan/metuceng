`timescale 1ns / 1ps

module ROM (
    input [2:0] addr,   
    output reg [7:0] dataOut 
);

    //ROM content
    reg [7:0] rom [7:0]; 

    // Initialize the ROM content
    initial begin
        rom[0] = 8'b00000000;
        rom[1] = 8'b00000001;
        rom[2] = 8'b00000010;
        rom[3] = 8'b00100011;
        rom[4] = 8'b11000100;
        rom[5] = 8'b01100101;
        rom[6] = 8'b00011110;
        rom[7] = 8'b01000101;
    end

    // Asynchronous read operation
    always @(*) begin
        dataOut = rom[addr];
    end

endmodule




module Bitwise_Manipulation_RAM (
    input mode, // 0 for write, 1 for read
    input [2:0] addr, 
    input [1:0] operation, 
    input [7:0] dataIn, 
    input [7:0] romData, 
    input CLK, 
    output reg [7:0] dataOut 
);

    //RAM content
    reg [7:0] ram [7:0];

    // Initialize the RAM content
    initial begin
        ram[0] = 8'b00000000;
        ram[1] = 8'b00000000;
        ram[2] = 8'b00000000;
        ram[3] = 8'b00000000;
        ram[4] = 8'b00000000;
        ram[5] = 8'b00000000;
        ram[6] = 8'b00000000;
        ram[7] = 8'b00000000;
    end

    // Synchronous Write Mode
    always @(posedge CLK) begin
        if (mode == 1'b0) begin
            case (operation)
                2'b00: ram[addr] <= dataIn & romData;  // AND
                2'b01: ram[addr] <= dataIn | romData;  // OR
                2'b10: ram[addr] <= dataIn ^ romData;  // XOR
                2'b11: ram[addr] <= ~(dataIn & romData); // NAND
            endcase
        end
    end

    // Asynchronous Read Mode
    always @* begin
        if (mode == 1'b1) begin
            dataOut = ram[addr];
        end
    end

endmodule




module Combined_Memory_System (
    input mode,         // W/R mode of RAM
    input [2:0] systemAddr, // System address
    input [7:0] dataIn, // System data input
    input [1:0] operation, // Operation code
    input CLK,          // Clock signal
    output [7:0] systemOutput // System output
);

    // Instantiate ROM module
    wire [7:0] romData;
    ROM rom_inst (
        .addr(systemAddr),
        .dataOut(romData)
    );

    // Instantiate RAM module
    Bitwise_Manipulation_RAM ram_inst (
        .mode(mode),
        .addr(systemAddr),
        .operation(operation),
        .dataIn(dataIn),
        .romData(romData),
        .CLK(CLK),
        .dataOut(systemOutput)
    );

endmodule

