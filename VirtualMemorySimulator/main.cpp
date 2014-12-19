//
//  main.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ios>

#include "parameters.h"
#include "pageTable.h"


using namespace std;


//Prototypes
int generateProcessId (int index);
void generateLogFile ();
uint64_t addressTranslation(uint64_t virtualAddress, int processId);

int main(int argc, const char * argv[]) {
    //generateLogFile();
    
    PageTable  lruPageTable = PageTable(LRU);
    //PageTable wsclkPageTable = PageTable(WSCLK);
    //PageTable fifoPageTable = PageTable(FIFO);
    cout << "Simulation begins" << endl;
    
    std::ifstream infile(LOG_FILE_ADDR);
    int processId;
    uint64_t timestamp, virtualAddress;
    while (infile >> timestamp >> processId >> virtualAddress) {
        // Perform touch operation for different strategies for each line at the log file.
        #ifdef LOG
            cout << timestamp << " " << processId << " " << virtualAddress << endl;
        #endif
        uint64_t virtualPageNumber = virtualAddress >> PAGE_OFFSET_NUM_OF_BITS;
        lruPageTable.touchPage(virtualPageNumber, processId, timestamp);
        //wsclkPageTable.touchPage(virtualPageNumber, processId, timestamp);
        //fifoPageTable.touchPage(virtualPageNumber, processId, timestamp);
    }
    cout << "Simulation finished" << endl;
    cout << "Total number of misses for LRU: " << lruPageTable.getNumOfMisses();
    return 0;
}

int generateProcessId (int index){
    if (index < 10) {
        return index * 1101;
    }
    else {
        return index * 101;
    }
}

void generateLogFile(){
    //Multiple Process Memory Access Log Generator
    //Creates random memory access timestamps and virtual addresses for each process.
    //Assume that memory is byte addressable. Max address value: 0x7fffffff
    cout << std::hex << RAND_MAX << endl;
    cout << "Memory Access Logs are being generated" << endl;
    ofstream myFile;
    myFile.open (LOG_FILE_ADDR);
    for (int a = 0; a < NUM_OF_ACCESSES_PEPROCESS ; a++) {
        for (int p=1; p <= NUM_OF_PROCESSES; p++) {
            int processId = generateProcessId(p);
            uint64_t timestamp = a * NUM_OF_PROCESSES + p;
            uint64_t virtualAddr = rand() / 2048;
            myFile << std::hex << timestamp << " " << processId << " " << virtualAddr << endl;
        }
    }
    myFile.close();
    cout << "Memory Access Log File was generated successfully"<<endl;
}

uint64_t addressTranslation(uint64_t virtualAddress, int processId){
    //Assume that physical addresses always starts with process id in left most 4 digits.
    return virtualAddress + processId * 0x800000;
}