#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

void sortArray(char*** tokens, int* tokenCounts, int videoCount) {
    int i, j, k;
    char* temp;
    for (i=0; i<videoCount; i++) {
        for (j=3; j<tokenCounts[i]; j+=2) {
            for (k=j+2; k<tokenCounts[i]; k+=2) {
                if (atoi(tokens[i][k]) > atoi(tokens[i][j]) ||
                    (atoi(tokens[i][k]) == atoi(tokens[i][j]) && strcmp(tokens[i][k-1], tokens[i][j-1]) < 0)) {
                    
                    temp = tokens[i][j];
                    tokens[i][j] = tokens[i][k];
                    tokens[i][k] = temp;
                    
                    temp = tokens[i][j-1];
                    tokens[i][j-1] = tokens[i][k-1];
                    tokens[i][k-1] = temp;
                }
            }
        }
    }
}

void setFirstNode(CacheNode** head, CacheNode* targetNode) {
    if(*head == targetNode){
        return;
    } else {
        if (targetNode == NULL) {
            return;
        }
        if (*head != NULL) {
            if (targetNode -> prev != NULL) {
                targetNode -> prev -> next = targetNode -> next;
            }
            if (targetNode -> next != NULL) {
                targetNode -> next -> prev = targetNode -> prev;
            }
            targetNode -> prev = NULL;
            targetNode -> next = *head;
    
            (*head) -> prev = targetNode;
        }
        *head = targetNode;
    }
}

DomainFreqNode* findDomain(DomainFreqList* list, char* domain)
{
    DomainFreqNode* test = list -> head;
    while(test){
        if(strcmp(test -> name, domain) == 0){
            return test;
        }
        test = test -> next;
    }
    return NULL;
}

void sortList(DomainFreqNode* head) {
    DomainFreqNode *current = NULL, *index = NULL;
    if (head == NULL) {
        return;
    }
    else {
        for (current = head; current -> next != NULL; current = current -> next) {
            for (index = current -> next; index != NULL; index = index -> next) {
                if (current -> freq < index -> freq) {
                    int freq_temp;
                    char* name_temp;
                    
                    freq_temp = current -> freq;
                    current -> freq = index -> freq;
                    index -> freq = freq_temp;

                    name_temp = current -> name;
                    current -> name = index -> name;
                    index -> name = name_temp;
                }
                else if (current -> freq == index -> freq && strcmp(current -> name, index -> name) > 0) {
                    char* name_temp = current -> name;
                    current -> name = index -> name;
                    index -> name = name_temp;
                }
            }
        }
    }
}  


/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    int cacheSize, currentSize = 0, videoCount, i, *tokenCounts;
    char **input, ***tokens;
    DomainFreqList** domainList;
    const char split[2] = " ";
    Cache* newCache;
    CacheNode** nodes;
    DomainFreqNode*** domainNodes;
    
    newCache = (Cache*)malloc(sizeof(Cache));
    
    scanf("%d %d\n", &cacheSize, &videoCount);
    
    newCache -> mediaCount = videoCount;
    newCache -> cacheLimit = cacheSize;
    
    input = (char**)malloc(sizeof(char*) * videoCount);
    nodes = (CacheNode**)malloc(sizeof(CacheNode*) * videoCount);
    domainList = (DomainFreqList**)malloc(sizeof(DomainFreqList*) * videoCount);
    tokens = (char***)malloc(sizeof(char**) * videoCount);
    tokenCounts = (int*)malloc(sizeof(int)*videoCount);
    domainNodes = (DomainFreqNode***)malloc(sizeof(DomainFreqNode**) * videoCount);
    
    for(i=0; i<videoCount; i++){
        input[i] = (char*)malloc(sizeof(char) * 1000);
        fgets(input[i], 1000, stdin);
    }
    
    for(i=0; i<videoCount; i++){
        char *token = strtok(input[i], split);
        int t = 0;
        tokens[i] = (char**)malloc(sizeof(char*) * 100);
        while (token != NULL) {
            tokens[i][t] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(tokens[i][t], token);
            t++;
            token = strtok(NULL, split);
        }
        tokenCounts[i] = t;
    }
    
    sortArray(tokens, tokenCounts, videoCount);
    free(input);
    
    for(i=0; i<videoCount; i++){
        int j, t=0;
        int a = (tokenCounts[i]-2)/2;
        domainNodes[i] = (DomainFreqNode**)malloc(sizeof(DomainFreqNode*) * a);
        for(j=0; j<a; j++){
            domainNodes[i][j] = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        }
        for(j=2; j<tokenCounts[i]; j+=2){
            domainNodes[i][t] -> name = tokens[i][j];
            domainNodes[i][t] -> freq = atoi(tokens[i][j+1]);
            if(t == 0){
                domainNodes[i][t] -> next = domainNodes[i][t+1];
                domainNodes[i][t] -> prev = NULL;
            } else if (t == a-1){
                domainNodes[i][t] -> next = NULL;
                domainNodes[i][t] -> prev = domainNodes[i][t-1];
            } else {
                domainNodes[i][t] -> next = domainNodes[i][t+1];
                domainNodes[i][t] -> prev = domainNodes[i][t-1];
            }
            t++;
        }
    }
    
    for(i=0; i<videoCount; i++){
        domainList[i] = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        nodes[i] = (CacheNode*)malloc(sizeof(CacheNode));
    }
    
    for(i=0; i<videoCount; i++){
        nodes[i] -> media.name = tokens[i][0];
        nodes[i] -> media.size = atoi(tokens[i][1]);
        nodes[i] -> domainFreqList = domainList[i];
        if (i == 0) {
            nodes[i] -> prev = NULL;
            nodes[i] -> next = nodes[i + 1];
        } else if (i == videoCount - 1) {
            nodes[i] -> prev = nodes[i - 1];
            nodes[i] -> next = NULL;
        } else {
            nodes[i] -> prev = nodes[i - 1];
            nodes[i] -> next = nodes[i + 1];
        }
        domainList[i] -> head = domainNodes[i][0];
        domainList[i] -> tail = domainNodes[i][(tokenCounts[i]-2)/2 - 1];
    }
    
    newCache -> head = nodes[0];
    newCache -> tail = nodes[videoCount-1];
    
    for(i=0; i<videoCount; i++){
        currentSize = currentSize + atoi(tokens[i][1]);
    }
    
    newCache -> currentSize = currentSize;
    
    return newCache;
}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{
    if(cache -> mediaCount != 0){
        CacheNode* test = cache -> head;
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n", cache -> cacheLimit);
        printf("Current Size: %d KB\n", cache -> currentSize);
        printf("Media Count: %d\n", cache -> mediaCount);
        printf("Cache Media Info:\n");
        while(test){
            DomainFreqNode* test2 = test -> domainFreqList -> head;
            printf("        Name: %s    Size: %d KB\n", test -> media.name, test -> media.size);
            printf("    ------- Media Domain Frequencies -------\n");
            while(test2){
                printf("        Name: %s        Freq: %d\n", test2 -> name, test2 -> freq);
                test2 = test2 -> next;
            }
            printf("    ----------------------------------------\n");
            test = test -> next;
        }
        printf("----------------------------------------------\n");
    } else {
        printf("The Cache is Empty\n");
    }
}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    if(findMedia(cache, media.name)){
        if(findDomain(findMedia(cache, media.name) -> domainFreqList, domain)){
            findDomain(findMedia(cache, media.name) -> domainFreqList, domain) -> freq += 1;
            setFirstNode(&(cache -> head), findMedia(cache, media.name));
            sortList(findMedia(cache, media.name) -> domainFreqList -> head);
        } else {
            DomainFreqNode* newDomainNode;
            DomainFreqNode* previous = NULL;
            DomainFreqNode* current = findMedia(cache, media.name) -> domainFreqList -> head;
            
            newDomainNode = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            newDomainNode -> name = domain;
            newDomainNode -> freq = 1;
            
            while(current != NULL && current -> freq > 1){
                previous = current;
                current = current -> next;
            }
            while(current!=NULL && strcmp(current -> name, newDomainNode -> name) < 0){
                previous = current;
                current = current -> next;
            }
            
            if (current == NULL && previous == NULL) {
                findMedia(cache, media.name)->domainFreqList->head = newDomainNode;
                findMedia(cache, media.name)->domainFreqList->tail = newDomainNode;
            } else if (current == NULL && previous != NULL) {
                newDomainNode -> prev = previous;
                newDomainNode -> next = NULL;
                previous -> next = newDomainNode;
                findMedia(cache, media.name) -> domainFreqList -> tail = newDomainNode;
            } else if (previous == NULL && current != NULL) {
                newDomainNode -> next = current;
                current -> prev = newDomainNode;
                newDomainNode -> prev = NULL;
                findMedia(cache, media.name) -> domainFreqList -> head = newDomainNode;
            } else {
                newDomainNode -> next = current;
                current -> prev = newDomainNode;
                newDomainNode -> prev = previous;
                previous -> next = newDomainNode;
            }
            setFirstNode(&(cache -> head), findMedia(cache, media.name));
        }
    } else {
        CacheNode* newNode;
        DomainFreqNode* newDomainNode;
        DomainFreqList* newDomainFreqList;
        
        newNode = (CacheNode*)malloc(sizeof(CacheNode));
        newDomainFreqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        newDomainNode = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        
        while((cache -> currentSize + media.size) > cache -> cacheLimit){
            deleteMedia(cache, cache -> tail -> media.name);
        }
        
        newDomainNode -> name = domain;
        newDomainNode -> freq = 1;
        newDomainNode -> prev = NULL;
        newDomainNode -> next = NULL;
        
        newDomainFreqList -> head = newDomainNode;
        newDomainFreqList -> tail = newDomainNode;
        
        newNode -> media = media;
        newNode -> domainFreqList = newDomainFreqList;
        
        if (cache -> head == NULL) {
            cache -> head = newNode;
            cache -> tail = newNode;
        } else {
            newNode -> next = cache -> head;
            cache -> head -> prev = newNode;
            cache -> head = newNode;
        }
        
        cache -> currentSize += media.size;
        cache -> mediaCount += 1;
    }
    
    return cache -> head;
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    CacheNode* test = cache -> head;
    while(test){
        if(strcmp(test -> media.name, name) == 0){
            return test;
        }
        test = test -> next;
    }
    return NULL;
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    CacheNode* deletedNode = findMedia(cache, name);
    CacheNode* current = cache -> head;
    CacheNode* previous = NULL;
    cache -> currentSize = (cache -> currentSize) - (deletedNode -> media.size);
    cache -> mediaCount = (cache -> mediaCount) - 1;

    while (current) {
        if (current == deletedNode) {
            if (previous) {
                previous -> next = current -> next;
            } else {
                cache -> head = current -> next;
            }
            if (current -> next) {
                current -> next -> prev = previous;
            } else {
                cache -> tail = previous; 
            }
            free(current); 
            break;
        } else {
            previous = current;
            current = current -> next;
        }
    }
}