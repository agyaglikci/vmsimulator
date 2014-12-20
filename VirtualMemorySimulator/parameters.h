//
//  parameters.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//


#define NUM_OF_PROCESSES 16
#define NUM_OF_ACCESSES_PERPROCESS 1024
#define PAGE_OFFSET_NUM_OF_BITS 12 // 1 page contains 4096 bytes = 4kB
#define PAGE_TABLE_CAPACITY 32
#define LOG_FILE_ADDR "/Users/agyaglikci/Workspace/VirtualMemorySimulator/VirtualMemorySimulator/memoryAccessFile.txt"
#define CUT_FILE_ADDR "/Users/agyaglikci/Workspace/VirtualMemorySimulator/VirtualMemorySimulator/safariCutData2.txt"
#define GCC_TRACE_FILE_ADDR "/Users/agyaglikci/Workspace/VirtualMemorySimulator/VirtualMemorySimulator/gcc_trace.txt"

//Page Table Strategies
#define LRU 0
#define WSCLK 1
#define FIFO 2

//Working Set Parameters
#define TAO 16

//Log Key
#define LOG 1