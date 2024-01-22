#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int costWeightedInt = isCostWeighted ? 1 : 0;
    return PRIMES[0]*startInt + PRIMES[1]*endInt + PRIMES[2]*costWeightedInt;
}

template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    for(int i = 0; i < MAX_SIZE; i++){
        table[i].lruCounter = 0;
        table[i].sentinel = EMPTY_MARK;
    }
    elementCount = 0;
}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    if(intArray.size() == 0){
        throw InvalidTableArgException();
    }
    
    int hash1 = Hash(intArray[0], intArray[intArray.size()-1], isCostWeighted);
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            int hash2 = Hash(table[i].intArray[0], table[i].intArray[table[i].intArray.size()-1], table[i].isCostWeighted);
            if(hash1 == hash2){
                table[i].lruCounter++;
                return table[i].lruCounter;
            }
        }
    }
    
    bool isFull = true;
    if(elementCount*2 < MAX_SIZE){
        isFull = false;
    }
    
    if(isFull){
        throw TableCapFullException(elementCount);
    }
    
    int insertTo = hash1 % MAX_SIZE;
    int count = 1;
    while(table[insertTo].sentinel == OCCUPIED_MARK){
        insertTo = (hash1 + count * count) % MAX_SIZE;
        count++;
    }
    
    table[insertTo].sentinel = OCCUPIED_MARK;
    table[insertTo].lruCounter = 1;
    table[insertTo].intArray = intArray;
    table[insertTo].startInt = intArray[0];
    table[insertTo].endInt = intArray[intArray.size()-1];
    table[insertTo].isCostWeighted = isCostWeighted;
    elementCount++;
    
    return 0;
}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    int hash1 = Hash(startInt, endInt, isCostWeighted);
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            int hash2 = Hash(table[i].intArray[0], table[i].intArray[table[i].intArray.size()-1], table[i].isCostWeighted);
            if(hash1 == hash2){
                if(incLRU){
                    table[i].lruCounter++;
                }
                intArray = table[i].intArray;
                return true;
            }
        }
    }
    
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
    for(int i = 0; i < MAX_SIZE; i++){
        table[i].lruCounter = 0;
        table[i].sentinel = EMPTY_MARK;
    }
    elementCount = 0;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    int maxLruIndex = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            if(table[i].lruCounter > table[maxLruIndex].lruCounter){
                maxLruIndex = i;
            }
        }
    }
    intArray = table[maxLruIndex].intArray;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    std::vector<int> newArray;
    int hash1 = Hash(startInt, endInt, isCostWeighted);
    
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            int hash2 = Hash(table[i].intArray[0], table[i].intArray[table[i].intArray.size()-1], table[i].isCostWeighted);
            if(hash1 == hash2){
                intArray = table[i].intArray;
                table[i].intArray = newArray;
                table[i].sentinel = SENTINEL_MARK;
                table[i].lruCounter = -1;
                table[i].startInt = NULL;
                table[i].endInt = NULL;
                table[i].isCostWeighted = NULL;
                elementCount--;
                return;
            }
        }
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    MinPairHeap<int, HashData> helperQueue;
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            Pair<int, HashData> myPair;
            myPair.key = table[i].lruCounter;
            myPair.value = table[i];
            helperQueue.push(myPair);
        }
    }
    
    while(lruElementCount != 0){
        HashData topHashData = helperQueue.top().value;
        Remove(topHashData.intArray, topHashData.startInt, topHashData.endInt, topHashData.isCostWeighted);
        helperQueue.pop();
        lruElementCount--;
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    MaxPairHeap<int, HashData> helperQueue;
    for(int i = 0; i < MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            Pair<int, HashData> myPair;
            myPair.key = table[i].lruCounter;
            myPair.value = table[i];
            helperQueue.push(myPair);
        }
    }
    while(!helperQueue.empty()){
        int tableIndex = 0;
        for(int i = 0; i < MAX_SIZE; i++){
            if(table[i].sentinel == OCCUPIED_MARK){
                Pair<int, HashData> myPair;
                myPair.key = table[i].lruCounter;
                myPair.value = table[i];
                if(helperQueue.top().key == myPair.key && helperQueue.top().value.isCostWeighted == myPair.value.isCostWeighted && helperQueue.top().value.intArray == myPair.value.intArray){
                    tableIndex = i;
                    break;
                }
            }
        }
        PrintLine(tableIndex);
        helperQueue.pop();
    }
}

#endif // HASH_TABLE_HPP