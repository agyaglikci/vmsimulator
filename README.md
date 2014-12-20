Virtual Memory Simulator
===========

This is a highly primitive virtual memory simulator to observe the behavior of page replacement algorithms.
The implemented replacement algorithms are not working exactly as real implementation but replacement decisions are the same with real implementation. 

The implemented page replacement algorithms are as follows: 
- LRU (Last Recently Used)
- FIFO (First in first out)
- WSCLOCK (Working Set Clock)

Adding new replacement algorithm is pretty easy, only required modification is at the selectEvictPage function of PageTable class. 

  
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
    }
  

You can add your own case part to add a new replacement algorithm. You also supposed to define the required parameters, variables, set-get functions etc. if you need.
