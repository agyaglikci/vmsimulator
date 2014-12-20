//
//  pageTable.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#include "pageTable.h"
PageTable::PageTable(int strategy){
    this->strategy = strategy;
    for (int i = 0 ; i < PAGE_TABLE_CAPACITY; i++) {
        activePageTable[i] = PageTableEntry();
    }
}

void PageTable::touchPage(uint64_t virtualPageNum, int processId, uint64_t current){
    int entryIndex = this->searchPage(virtualPageNum,processId);
    if ( entryIndex == -1){
        this->incMisses();
        if (this->isThereEmptySpots()){
            this->insertPageEntry(virtualPageNum,processId,current);
            this->incNumOfEntries();
        }
        else {
            int evictIndex = this->selectEvictPage(current);
            activePageTable[evictIndex].evictAndSet(virtualPageNum,processId,current);
        }
    }
    else {
        this->activePageTable[entryIndex].updateLastAccessTime(current);
        this->activePageTable[entryIndex].incHit();
    }
}

int PageTable::searchPage(uint64_t virtualPageNum, int processId){
    for (int i = 0 ; i < PAGE_TABLE_CAPACITY ; i++) {
        if ( activePageTable[i].isIdentical(virtualPageNum, processId) && activePageTable[i].isValid()) {
            return i;
        }
    }
    return -1;
}
int PageTable::selectEvictPage(uint64_t current){
    switch (this->strategy) {
        
        case LRU:{
            uint64_t minTimestamp = current;
            int minIndex = 0;
            for (int i = 0 ; i < PAGE_TABLE_CAPACITY; i++) {
                uint64_t tempTimeStamp = activePageTable[i].getLastAccessTime();
                if ( tempTimeStamp < minTimestamp ){
                    minTimestamp = tempTimeStamp;
                    minIndex = i ;
                }
            }
            return minIndex;
            break;
        }
            
        case FIFO:{
            uint64_t minTimestamp = current;
            int minIndex = 0;
            for (int i = 0 ; i < PAGE_TABLE_CAPACITY; i++) {
                uint64_t tempTimeStamp = activePageTable[i].getEntryTime();
                if ( tempTimeStamp < minTimestamp ){
                    minTimestamp = tempTimeStamp;
                    minIndex = i ;
                }
            }
            return minIndex;
            break;
        }
          
        case WSCLK:{
            bool victimSelected = false;
            while (!victimSelected) {
                if (current - activePageTable[wsClockPointer].getLastAccessTime() >= TAO) {
                    if (activePageTable[wsClockPointer].isTouched()) {
                        activePageTable[wsClockPointer].clearTouched();
                        wsClockPointer = ( wsClockPointer + 1 ) % PAGE_TABLE_CAPACITY;
                    }
                    else {
                        victimSelected = true;
                    }
                }
                else {
                    wsClockPointer = ( wsClockPointer + 1 ) % PAGE_TABLE_CAPACITY;
                }
            }
            return wsClockPointer;
            
            break;
        }
            
        default:{
            return 0;
            break;
        }
    }
}
int  PageTable::insertPageEntry(uint64_t virtualPageNum, int processId, uint64_t current){
    for (int i = 0; i < PAGE_TABLE_CAPACITY; i++) {
        if (!activePageTable[i].isValid()){
            activePageTable[i].evictAndSet(virtualPageNum,processId,current);
            return i;
        }
    }
    return PAGE_TABLE_CAPACITY - 1;
}
void PageTable::incNumOfEntries(){
    this->totalFilledEntries++;
}
void PageTable::incMisses(){
    this->numOfMisses++;
}
int PageTable::getNumOfMisses(){
    return this->numOfMisses;
}
bool PageTable::isThereEmptySpots(){
    return totalFilledEntries < PAGE_TABLE_CAPACITY;
}
/*
void PageTable::showPageTable(){
    cout << "Page Table : " << endl;
    for (int i = 0; i < PAGE_TABLE_CAPACITY; i++) {
        cout << this->activePageTable[i].virtualPageNum <<
    }
}
 */
