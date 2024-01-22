#include "File.h"

Block File::getBlock(int index) const
{
	Node<Block> *current = blocks.getNodeAtIndex(index);
    if (current) {
        return current->data;
    }
    return Block();
}

size_t File::fileSize() const
{
	size_t result = 0;
	Node<Block> *current = blocks.getFirstNode();
	while(current){
	    result = result + current -> data.getSize();
	    current = current -> next;
	}
	return result;
}

int File::numBlocks() const
{
	int result = 0;
	Node<Block> *current = blocks.getFirstNode();
	while(current){
	    result++;
	    current = current -> next;
	}
	return result;
}

bool File::isEmpty() const
{
	Node<Block> *current = blocks.getFirstNode();
	return (current == NULL);
}

bool File::operator==(const File &rhs) const
{
	if(rhs.numBlocks() != numBlocks()){
	    return false;
	}
	Node<Block> *current = blocks.getFirstNode();
	Node<Block> *currentRHS = rhs.blocks.getFirstNode();
	while(current){
	    if(!(current -> data == currentRHS -> data)){
	       return false;
	    } 
	    current = current -> next;
	    currentRHS = currentRHS -> next;
	}
	return true;
}

void File::newBlock(const Block &block)
{
	blocks.append(block);
}

void File::removeBlock(int index)
{
    blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	blocks.mergeNodes(sourceIndex, destIndex);
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}