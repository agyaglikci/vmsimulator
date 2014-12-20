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
void generateLogFile();
void generateLogFileByCutData();
void generateLogFileByGccTrace();

int main(int argc, const char * argv[]) {
    //generateLogFileByGccTrace();
    
    PageTable lruPageTable   = PageTable(LRU);
    PageTable wsclkPageTable = PageTable(WSCLK);
    PageTable fifoPageTable  = PageTable(FIFO);

    cout << "-- Simulation begins" << endl;
    std::ifstream infile(LOG_FILE_ADDR);
    int processId;
    uint64_t timestamp, virtualAddress;
    int count;
    while (infile >> timestamp >> processId >> std::hex >> virtualAddress) {
        count++;
        // Perform touch operation for different strategies for each line at the log file.
        #ifdef LOG
            cout << timestamp << " " << processId << " " << virtualAddress << endl;
        #endif
        uint64_t virtualPageNumber = virtualAddress >> PAGE_OFFSET_NUM_OF_BITS;
        lruPageTable.touchPage(virtualPageNumber, processId, timestamp);
        wsclkPageTable.touchPage(virtualPageNumber, processId, timestamp);
        fifoPageTable.touchPage(virtualPageNumber, processId, timestamp);
    }
    cout << "-- Simulation finished" << endl;
    cout << "Total number of operation        : " << count << endl;
    
    cout << "Total number of misses for LRU   : " << std::dec << lruPageTable.getNumOfMisses() << endl;
    cout << "Total number of misses for FIFO  : " << std::dec << fifoPageTable.getNumOfMisses() << endl;
    cout << "Total number of misses for WSCLK : " << std::dec << wsclkPageTable.getNumOfMisses() << endl;
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

void memory_trace(){
    
}

void generateLogFileByCutData(){
    std::ifstream infile(CUT_FILE_ADDR);
    ofstream myFile;
    myFile.open (LOG_FILE_ADDR);
    string virtualAddress;
    int i = 0;
    while (infile >> virtualAddress) {
        myFile << std::hex << i << " 1 " << virtualAddress << "000" << endl;
        i++;
    }
    myFile.close();
}

void generateLogFileByGccTrace(){
    std::ifstream infile(GCC_TRACE_FILE_ADDR);
    ofstream myFile;
    myFile.open (LOG_FILE_ADDR);
    string first, second, third;
    while (infile >> first >> second >> third) {
        myFile << std::hex << third << " " << first << " " << second << endl;
    }
    myFile.close();
}

void generateLogFile(){
    //Multiple Process Memory Access Log Generator
    //Creates random memory access timestamps and virtual addresses for each process.
    //Assume that memory is byte addressable. Max address value: 0x7fffffff
    cout << "-- Memory Access Logs are being generated" << endl;
    ofstream myFile;
    myFile.open (LOG_FILE_ADDR);
    for (int a = 0; a < NUM_OF_ACCESSES_PERPROCESS ; a++) {
        for (int p=1; p <= NUM_OF_PROCESSES; p++) {
            int processId = generateProcessId(p);
            uint64_t timestamp = a * NUM_OF_PROCESSES + p;
            uint64_t virtualAddr = rand()%(2^22);  // Random
            //uint64_t virtualAddr = (timestamp % PAGE_TABLE_CAPACITY) << PAGE_OFFSET_NUM_OF_BITS; // FIFO Friendly
            //uint64_t virtualAddr = (timestamp % (PAGE_TABLE_CAPACITY / 3)) << PAGE_OFFSET_NUM_OF_BITS; // FIFO Friendly
            myFile << timestamp << " " << processId << " " << virtualAddr << endl;
        }
    }
    myFile.close();
    cout << "-- Memory Access Log File was generated successfully"<<endl;
}

