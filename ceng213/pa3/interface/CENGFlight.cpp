#include "CENGFlight.h"
#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//
void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    HaltedFlight haltedFlight;
    haltedFlight.airportFrom = airportFrom;
    haltedFlight.airportTo = airportTo;
    haltedFlight.airline = airlineName;
    haltedFlight.w0 = navigationMap.getEdgeWeight(airlineName, airportFrom, airportTo, 0);
    haltedFlight.w1 = navigationMap.getEdgeWeight(airlineName, airportFrom, airportTo, 1);
    
    if(haltedFlight.w0 == -1.0 && haltedFlight.w1 == -1.0){
        PrintCanNotHalt(airportFrom, airportTo, airlineName);
        return;
    }
    
    navigationMap.RemoveEdge(airlineName, airportFrom, airportTo);
    haltedFlights.push_back(haltedFlight);
}

    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
    int flightIndex = -1;
    for(int i = 0; i < haltedFlights.size(); i++){
        if(haltedFlights[i].airportFrom == airportFrom && haltedFlights[i].airportTo == airportTo && haltedFlights[i].airline == airlineName){
            flightIndex = i;
        }
    }
    
    if(flightIndex == -1){
        PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
        return;
    }
    
    navigationMap.AddEdge(airlineName, airportFrom, airportTo, haltedFlights[flightIndex].w0, haltedFlights[flightIndex].w1);
    haltedFlights.erase(haltedFlights.begin()+flightIndex); 
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
    bool isCostWeighted = (alpha == 0) ? true : false;
    
    std::vector<int> pathIndexes;
    if(!navigationMap.HeuristicShortestPath(pathIndexes, startAirportName, endAirportName, alpha)){
        PrintPathDontExist(startAirportName, endAirportName);
    } else {
        if(alpha == 0 || alpha == 1){
            if(lruTable.Find(pathIndexes, pathIndexes[0], pathIndexes[pathIndexes.size()-1], isCostWeighted, true)){
                PrintFlightFoundInCache(startAirportName, endAirportName, isCostWeighted);
                navigationMap.PrintPath(pathIndexes, alpha, true);
                return;
            } else {
                try {
                    lruTable.Insert(pathIndexes, isCostWeighted);
                } catch (TableCapFullException e) {
                    lruTable.RemoveLRU(1);
                    lruTable.Insert(pathIndexes, isCostWeighted);
                }
                PrintFlightCalculated(startAirportName, endAirportName, isCostWeighted);
            }
        }
        navigationMap.PrintPath(pathIndexes, alpha, true);
    }
    
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
    bool isCostWeighted = (alpha == 0) ? true : false;
    std::vector<int> pathIndexes;
    if(!navigationMap.FilteredShortestPath(pathIndexes, startAirportName, endAirportName, alpha, unwantedAirlineNames)){
        PrintPathDontExist(startAirportName, endAirportName);
    } else {
        navigationMap.PrintPath(pathIndexes, alpha, true);
    }
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
    if(navigationMap.vertexIndexByName(airportName) == -1){
        PrintSisterAirlinesDontCover(airportName);
        return;
    }
    
    std::vector<std::string> visitedAirports;
    std::vector<std::string> sisterAirlines;
    sisterAirlines.push_back(startAirlineName);
    visitedAirports.push_back(airportName);
    std::vector<std::string> newVisitedAirports = navigationMap.visitAirportsUsingAirline(visitedAirports, sisterAirlines, airportName);
    for(int i = 0; i < newVisitedAirports.size(); i++){
        visitedAirports.push_back(newVisitedAirports[i]);
    }
    
    bool changed;
    do {
        changed = false;
        std::string selectedAirport = navigationMap.maxNonVisitedNeighborAirport(visitedAirports);
        if (selectedAirport.empty()) {
            PrintSisterAirlinesDontCover(airportName);
            return;
        }

        std::string newAirline = navigationMap.getFirstNonUtilizedAirline(selectedAirport, visitedAirports, sisterAirlines);
        if (newAirline.empty()) {
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        sisterAirlines.push_back(newAirline);

        std::vector<std::string> newVisitedAirports = navigationMap.visitAirportsUsingAirline(visitedAirports, sisterAirlines, selectedAirport);
        if (!newVisitedAirports.empty()) {
            for(int i = 0; i < newVisitedAirports.size(); i++){
                visitedAirports.push_back(newVisitedAirports[i]);
            }
            changed = true;
        }
        
    } while (changed && !navigationMap.allAirportsVisited(visitedAirports));
    
    if(!changed && !navigationMap.allAirportsVisited(visitedAirports)){
        PrintSisterAirlinesDontCover(airportName);
        return;
    }
    
    sisterAirlines.erase(sisterAirlines.begin());
    airlineNames = sisterAirlines;
}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    int airportIndex = navigationMap.vertexIndexByName(airportName);
    
    if (airportIndex == -1) {
        return -1;
    }
    
    int result = navigationMap.MaxDepthViaEdgeName(airportName, airlineName);
    return result;
}


