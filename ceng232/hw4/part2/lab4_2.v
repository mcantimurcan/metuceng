`timescale 1ns / 1ps

module lab4_2(
	input [1:0] mode,//Student Entrance Mode 01, Student Exit Mode 00,Search Mode 10,List Mode 11
	input [5:0] userID,//USERID
	input CLK,
	output reg [1:0] selectedAreaId, //show user selected area 
	output reg [5:0] numberOfInsideUser, //seatLeft
	output reg [5:0] listOutput,
	output reg AlreadyInside,
	output reg NotInside
);

reg [15:0] loudSeats;
reg [15:0] quietSeats;
reg [15:0] individualSeats;
reg [15:0] zoomSeats;
reg [15:0] currentSeats;

reg [4:0] loudIndex;
reg [4:0] quietIndex;
reg [4:0] individualIndex;
reg [4:0] zoomIndex;
reg [4:0] selectedIndex;

reg [3:0] userIndex;
integer i;

initial begin
    loudSeats = 16'b0;
    quietSeats = 16'b0;
    individualSeats = 16'b0;
    zoomSeats = 16'b0;
	currentSeats = 16'b0;

    selectedAreaId = 2'b0;
    numberOfInsideUser = 6'b0;
    listOutput = 6'b0;
    AlreadyInside = 1'b0;
    NotInside = 1'b0;

    loudIndex = 5'b0;
    quietIndex = 5'b0;
    individualIndex = 5'b0;
    zoomIndex = 5'b0;
    selectedIndex = 5'b0;

	userIndex = 4'b0;
end

always @(posedge CLK) begin
    selectedAreaId = userID[5:4];
    userIndex = userID[3:0];
    currentSeats = 16'b0;

    case (selectedAreaId)
        2'b00: begin 
            currentSeats = loudSeats;
            quietIndex = 4'b0;
            individualIndex = 4'b0;
            zoomIndex = 4'b0;
        end
        2'b01: begin 
            currentSeats = quietSeats;
            loudIndex = 4'b0;
            individualIndex = 4'b0;
            zoomIndex = 4'b0;
        end
        2'b10: begin
            currentSeats = individualSeats;
            loudIndex = 4'b0;
            quietIndex = 4'b0;
            zoomIndex = 4'b0;
        end
        2'b11: begin
            currentSeats = zoomSeats;
            loudIndex = 4'b0;
            quietIndex = 4'b0;
            individualIndex = 4'b0;
        end
    endcase

    AlreadyInside = 1'b0;
    NotInside = 1'b0;
    listOutput = 6'b0;
	
    case (mode)
        2'b01: begin
            loudIndex = 4'b0;
            quietIndex = 4'b0;
            individualIndex = 4'b0;
            zoomIndex = 4'b0;
            selectedIndex = 4'b0;
            if (currentSeats[userIndex] == 1'b1) begin
                AlreadyInside = 1'b1;
            end else begin
                currentSeats[userIndex] = 1'b1;
            end
        end

        2'b00: begin
            loudIndex = 4'b0;
            quietIndex = 4'b0;
            individualIndex = 4'b0;
            zoomIndex = 4'b0;
            selectedIndex = 4'b0;
            if (currentSeats[userIndex] == 1'b0) begin
                NotInside = 1'b1;
            end else begin
                currentSeats[userIndex] = 1'b0;
            end
        end

        2'b10: begin
            loudIndex = 4'b0;
            quietIndex = 4'b0;
            individualIndex = 4'b0;
            zoomIndex = 4'b0;
            selectedIndex = 4'b0;
            if (currentSeats[userIndex] == 1'b1) begin
                AlreadyInside = 1'b1;
            end else begin
                NotInside = 1'b1;
            end
        end

        2'b11: begin
            case (selectedAreaId)
                2'b00: selectedIndex = loudIndex;
                2'b01: selectedIndex = quietIndex;
                2'b10: selectedIndex = individualIndex;
                2'b11: selectedIndex = zoomIndex;
            endcase

            if(selectedIndex > 15) begin
                listOutput = 6'b0xx;
            end else begin
                while (currentSeats[selectedIndex] == 1'b0 && selectedIndex < 15) begin
                    selectedIndex = selectedIndex + 1;
                end
                if (currentSeats[selectedIndex] == 1'b1) begin
                    listOutput = {selectedAreaId, selectedIndex[3:0]};
                    selectedIndex = selectedIndex + 1;
                end else begin
                    listOutput = 6'b0xx;
                    selectedIndex = selectedIndex + 1;
                end
            end

            case (selectedAreaId)
                2'b00: loudIndex = selectedIndex;
                2'b01: quietIndex = selectedIndex;
                2'b10: individualIndex = selectedIndex;
                2'b11: zoomIndex = selectedIndex;
            endcase
        end
    endcase

    case (selectedAreaId)
        2'b00: loudSeats = currentSeats;
        2'b01: quietSeats = currentSeats;
        2'b10: individualSeats = currentSeats;
        2'b11: zoomSeats = currentSeats;
    endcase

    numberOfInsideUser = 0; 
    for (i = 0; i < 16; i = i + 1) begin
        if (currentSeats[i] == 1'b1) begin
            numberOfInsideUser = numberOfInsideUser + 1;
        end
    end
end

endmodule