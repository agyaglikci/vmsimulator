//
//  pageTableEntry.h
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#ifndef __VirtualMemorySimulator__pageTableEntry__
#define __VirtualMemorySimulator__pageTableEntry__

#include <stdio.h>
#include <stdint.h>
#include "parameters.h"

class PageTableEntry {
    uint64_t virtualPageNum, lastAccessTime;
    int numOfHits, processId;
    bool valid = false;
    
public:
    PageTableEntry();
    PageTableEntry(uint64_t pageNumber, int processId);
    void incHit();
    
    int getNumOfHits();
    int getNumOfMisses();
    uint64_t getTimeStamp ();
    
    bool isIdentical(uint64_t virtualPageNum, int processId);
    bool isValid();
    
    void evictAndSet(uint64_t virtualPageNum, int processId, uint64_t current);
    void setTimeStamp (uint64_t timeStamp);
    
};

#endif /* defined(__VirtualMemorySimulator__pageTableEntry__) */

