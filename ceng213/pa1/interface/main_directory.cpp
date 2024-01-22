#ifndef DIRECTORY_MAIN_H
#define DIRECTORY_MAIN_H

#include "Node.h"
#include "Block.h"
#include "LinkedList.h"
#include "File.h"
#include "Directory.h"

int main()
{
	// You can test your implementations here
	Block block1 = Block("Block1");
	Block block2 = Block("Block2");
	Block block3 = Block("Block3");

	File file1 = File();
	file1.newBlock(block1);
	file1.newBlock(block2);
}

#endif //DIRECTORY_MAIN_H