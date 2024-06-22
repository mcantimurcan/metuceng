`timescale 1ns / 1ps

module testbench_ac;
    // Inputs
    reg A;
    reg C;
    reg clk;
    // Outputs
    wire Q;

    // Instantiate the Unit Under Test (UUT)
    ac_flip_flop uut (
        .A(A),
        .C(C),
        .clk(clk),
        .Q(Q)
    );

    integer grade = 0;

    // Clock generation
    initial clk = 0;
    always #5 clk = ~clk;  // Clock with a period of 10 ns

    // Monitor signals
    initial begin
        $monitor("Time=%t | A=%b C=%b | Q=%b", $time, A, C, Q);
    end

    // Test cases
    initial begin
        // Initial setup
        A = 0; C = 0;
        #1; // Wait 1 ns to check initial output
        if (Q !== 1'b1) begin
            $display("Error: Q should be initialized to 1.");
        end else begin
            $display("Initial value of Q is correct and set to 1.");
            grade = grade + 1;
        end

        // Test input 00 - Q should be 1
        #9; // Move just before the next clock edge
        if (Q !== 1'b1) begin
            $display("Error: Q should be 1 with A=0, C=0.");
        end else begin
            $display("Success: Q remains 1 with A=0, C=0 as expected.");
            grade = grade + 2;
        end

        // Test input 01 - Q should toggle
        A = 0; C = 1;
        #10; // Wait for next clock edge
        if (Q !== 1'b0) begin
            $display("Error: Q should toggle to 0 with A=0, C=1.");
        end else begin
            $display("Success: Q toggled to 0 with A=0, C=1 as expected.");
            grade = grade + 2;
        end

        // Test input 01 - Q should toggle back
        #10; // Wait for next clock edge
        if (Q !== 1'b1) begin
            $display("Error: Q should toggle back to 1 with A=0, C=1.");
        end else begin
            $display("Success: Q toggled back to 1 with A=0, C=1 as expected.");
            grade = grade + 2;
        end

        // Test input 10 - Q should be 0
        A = 1; C = 0;
        #10; // Wait for next clock edge
        if (Q !== 1'b1) begin
            $display("Error: Q should be 1 with A=1, C=0.");
        end else begin
            $display("Success: Q set to 1 with A=1, C=0 as expected.");
            grade = grade + 2;
        end

        // Test input 11 - Q should be 1
        A = 1; C = 1;
        #10; // Wait for next clock edge
        if (Q !== 1'b1) begin
            $display("Error: Q should be 1 with A=1, C=1.");
        end else begin
            $display("Success: Q remains 1 with A=1, C=1 as expected.");
            grade = grade + 2;
        end

        // Finish simulation and display the result
        #10;
        $display("End of Simulation. Total grade: %d/11", grade);
        $finish;
    end
endmodule
