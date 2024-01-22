#include <iostream>
#include "LinkedList.h"

int main() {
    // You can test your implementations here

    LinkedList<int> linkedList = LinkedList<int>();
    linkedList.append(1);
    linkedList.append(2);
    linkedList.append(3);
    linkedList.append(4);
    linkedList.append(5);

    linkedList.mergeNodes(0,4);
    for(int i = 0; i<linkedList.getSize(); i++){
        std::cout << linkedList.getNodeAtIndex(i) -> data << " ";
    }
}
