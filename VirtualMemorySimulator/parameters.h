//
//  parameters.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//


#define NUM_OF_PROCESSES 16
#define NUM_OF_ACCESSES_PEPROCESS 8096
#define PAGE_OFFSET_NUM_OF_BITS 0 // Page size is 4kB
#define PAGE_TABLE_CAPACITY 4
#define LOG_FILE_ADDR "/Users/agyaglikci/Workspace/VirtualMemorySimulator/VirtualMemorySimulator/memoryAccessFile.txt"

//Page Table Strategies
#define LRU 0
#define WSCLK 1
#define FIFO 2

//Log Key
#define LOG 1