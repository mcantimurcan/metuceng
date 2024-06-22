`timescale 1ns / 1ps 
module lab3_2(
    input [4:0] money,
    input CLK, 
    input [1:0] selectedArea, // 00: exit, 01: enter, 1x: idle 
    input plugAvailability,
    output reg [5:0] moneyLeft,
    output reg [5:0] seatLeft,
    output reg seatUnavailable,
    output reg insufficientFund,
    output reg notExactFund,
    output reg invalidPlugSeat,
    output reg plugSeatUnavailable,
    output reg seatReady
);

// IMPLEMENT BELOW

reg [5:0] loudSeatLeft;
reg [5:0] quietSeatLeftWithPlug;
reg [5:0] quietSeatLeftWithoutPlug;
reg [5:0] individualSeatLeft;

initial begin
    moneyLeft = 0;
    seatUnavailable = 0;
    insufficientFund = 0;
    notExactFund = 0;
    invalidPlugSeat = 0;
    plugSeatUnavailable = 0;
    seatReady = 0;
	seatLeft = 0;

    loudSeatLeft = 15;
    quietSeatLeftWithPlug = 10;
    quietSeatLeftWithoutPlug = 15;
    individualSeatLeft = 20;
end

always @(posedge CLK) begin
    moneyLeft = 0;
    seatUnavailable = 0;
    insufficientFund = 0;
    notExactFund = 0;
    invalidPlugSeat = 0;
    plugSeatUnavailable = 0;
    seatReady = 0;
    seatLeft = 0;
    case (selectedArea)
        0: // Exit
            begin
                if(loudSeatLeft > 0) begin
                    if(plugAvailability == 1) begin
                        invalidPlugSeat = 1;
                        seatLeft = loudSeatLeft;
                        moneyLeft = money;
                    end
                    else begin
                        if(money >= 10) begin
                            seatReady = 1;
                            moneyLeft = money - 10;
                            loudSeatLeft = loudSeatLeft - 1;
                            seatLeft = loudSeatLeft;
                        end
                        else begin
                            insufficientFund = 1;
                            moneyLeft = money;
                            seatLeft = loudSeatLeft;
                        end
                    end
                end
                else begin        
                    seatUnavailable = 1;
                    moneyLeft = money;
                    seatLeft = 0;
                end
            end
        1: // Enter
            begin
                if(plugAvailability == 1 && quietSeatLeftWithPlug > 0 && money >= 20)
                    begin
                        seatReady = 1;
                        moneyLeft = money - 20;
                        quietSeatLeftWithPlug = quietSeatLeftWithPlug - 1;
                        seatLeft = quietSeatLeftWithPlug;
                    end
                else if (plugAvailability == 1 && quietSeatLeftWithPlug == 0)
                    begin
                        if(quietSeatLeftWithoutPlug == 0)
                            begin
                                seatUnavailable = 1;
                            end
                        else
                            begin
                                plugSeatUnavailable = 1;
                            end
                        moneyLeft = money;
                        seatLeft = quietSeatLeftWithPlug;
                    end
                else if(plugAvailability == 1 && quietSeatLeftWithPlug > 0 && money < 20)
                    begin
                        insufficientFund = 1;
                        moneyLeft = money;
                        seatLeft = quietSeatLeftWithPlug;
                    end
                else if(plugAvailability == 0 && quietSeatLeftWithoutPlug > 0 && money >= 20)
                    begin
                        seatReady = 1;
                        moneyLeft = money - 20;
                        quietSeatLeftWithoutPlug = quietSeatLeftWithoutPlug - 1;
                        seatLeft = quietSeatLeftWithoutPlug;
                    end
                else if (plugAvailability == 0 && quietSeatLeftWithoutPlug == 0)
                    begin
                        seatUnavailable = 1;
                        moneyLeft = money;
                        seatLeft = quietSeatLeftWithoutPlug;
                    end
                else if(plugAvailability == 0 && quietSeatLeftWithoutPlug > 0 && money < 20)
                    begin
                        insufficientFund = 1;
                        moneyLeft = money;
                        seatLeft = quietSeatLeftWithoutPlug;
                    end
            end
        3: // Idle
            begin
                if(individualSeatLeft > 0) begin
                    if(money == 30) begin
                        moneyLeft = 0;
                        individualSeatLeft = individualSeatLeft - 1;
                        seatLeft = individualSeatLeft;
                        seatReady = 1;
                    end
                    else begin
                        moneyLeft = money;
                        seatLeft = individualSeatLeft;
                        notExactFund = 1;
                    end
                end
                else begin
                    moneyLeft = money;
                    seatLeft = individualSeatLeft;
                    seatUnavailable = 1;
                end
            end
    endcase
end

endmodule