//
//  main.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#define NUM_OF_PROCESSES 32
#define NUM_OF_ACCESSES_PEPROCESS 1024
#define LOG_FILE_ADDR "/Users/agyaglikci/Workspace/VirtualMemorySimulator/VirtualMemorySimulator/memoryAccessFile.txt"

#include <iostream>
#include <fstream>
#include <ios>
#include "main.h"
#include "process.h"

using namespace std;


//Prototypes
int generateProcessId (int index);
void generateLogFile ();

int main(int argc, const char * argv[]) {
    generateLogFile();
    
    
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

void generateLogFile(){ //Multiple Process Memory Access Log Generator
    //Creates random memory access timestamps and virtual addresses for each process.
    
    cout << "Memory Access Logs are being generated" << endl;
    ofstream myFile;
    myFile.open (LOG_FILE_ADDR);
    for (int a = 0; a < NUM_OF_ACCESSES_PEPROCESS ; a++) {
        for (int p=1; p <= NUM_OF_PROCESSES; p++) {
            int processId = generateProcessId(p);
            uint64_t timestamp = (rand() % NUM_OF_PROCESSES) + a * NUM_OF_PROCESSES;
            uint64_t virtualAddr = rand();
            myFile << processId << "," << timestamp << "," << virtualAddr << endl;
            
        }
    }
    myFile.close();
    cout << "Memory Access Log File was generated successfully"<<endl;
}