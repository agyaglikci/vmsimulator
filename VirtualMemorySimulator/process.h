//
//  process.h
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#ifndef __VirtualMemorySimulator__process__
#define __VirtualMemorySimulator__process__

#include <stdio.h>
#include <stdint.h>
#include <map>

#endif /* defined(__VirtualMemorySimulator__process__) */

class Process {
    
    int processId;
    std::map <uint64_t , uint64_t> memoryAccesses;
    
public:
    void setProcessID (int processId);
    void appendMemoryAccess (uint64_t timeStamp, uint64_t virtualAddress);
    
    std::map <uint64_t , uint64_t> getMemoryAccesses();
    
};