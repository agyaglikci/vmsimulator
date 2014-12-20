//
//  pageTable.h
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#ifndef __VirtualMemorySimulator__pageTable__
#define __VirtualMemorySimulator__pageTable__

#include <stdio.h>
#include <stdint.h>
#include <map>
#include "pageTableEntry.h"
#include "parameters.h"

class PageTable {
    int strategy;
    int numOfMisses = 0;
    int totalFilledEntries = 0;
    int wsClockPointer = 0;
    PageTableEntry activePageTable[PAGE_TABLE_CAPACITY];
public:
    PageTable(int);
    int  searchPage(uint64_t virtualPageNum, int processId);
    int  selectEvictPage(uint64_t timestamp);
    void touchPage(uint64_t virtualPageNum, int processId, uint64_t current);
    void incMisses();
    bool isThereEmptySpots();
    int  insertPageEntry(uint64_t virtualPageNum, int processId, uint64_t current);
    void incNumOfEntries();
    
    int getNumOfMisses();

    //void showPageTable();
};


#endif /* defined(__VirtualMemorySimulator__pageTable__) */



