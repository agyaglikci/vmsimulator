//
//  pageTableEntry.cpp
//  VirtualMemorySimulator
//
//  Created by Abdullah Giray Yaglikci on 12/18/14.
//  Copyright (c) 2014 Pikseladam. All rights reserved.
//

#include "pageTableEntry.h"

PageTableEntry::PageTableEntry(){

}

PageTableEntry::PageTableEntry(uint64_t pageNumber, int processId){
    this->virtualPageNum = pageNumber;
    this->processId = processId;
}

void PageTableEntry::evictAndSet(uint64_t virtualPageNum, int processId, uint64_t current){
    
    this->virtualPageNum = virtualPageNum;
    this->processId = processId;
    this->numOfHits = 0;
    this->lastAccessTime = current;
    this->entryTime = current;
    this->valid = true;
    this->touched = true;
}


bool PageTableEntry::isIdentical(uint64_t virtualPageNum, int processId){
    return (virtualPageNum == this->virtualPageNum && processId == this->processId);
}
bool PageTableEntry::isValid(){
    return this->valid;
}
bool PageTableEntry::isTouched(){
    return this->touched;
}

void PageTableEntry::clearTouched(){
    this->touched = false;
}
void PageTableEntry::incHit(){
    this->numOfHits++;
}

int PageTableEntry::getNumOfHits(){
    return this->numOfHits;
}
int PageTableEntry::getNumOfMisses(){
    return this->numOfHits;
}
uint64_t PageTableEntry::getLastAccessTime(){
    return this->lastAccessTime;
}
uint64_t PageTableEntry::getEntryTime(){
    return this->entryTime;
}
void PageTableEntry::updateLastAccessTime (uint64_t timeStamp){
    this->lastAccessTime = timeStamp;
    this->touched = true;
}

