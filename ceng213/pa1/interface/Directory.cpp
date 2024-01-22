#include "Directory.h"

File Directory::getFile(int index) const
{
	if (index >= numFiles() || index < 0) {
        return File();
	}
    return files[index];
}

size_t Directory::directorySize() const
{
	size_t result = 0;
	for(int i = 0; i<numFiles(); i++){
	    result += files[i].fileSize();
	}
	return result;
}

bool Directory::isEmpty() const
{
	return (files.size() == 0);
}

size_t Directory::numFiles() const
{
	return files.size();
}

void Directory::newFile(const File &file)
{
	files.insert(files.end(), file);
}

void Directory::removeFile(int index)
{
	if(index >= numFiles() || index < 0){
	    return;
	}
	files.erase(files.begin()+index); 
}

void Directory::removeFile(File &file)
{
	for(int i = 0; i<numFiles(); i++){
	    if(files[i] == file){
	        files.erase(files.begin()+i);
	        break;
	    }
	}
}

void Directory::removeBiggestFile()
{
	int removedIndex = 0;
	for(int i = 0; i<numFiles(); i++){
	    if(files[i].fileSize() > files[removedIndex].fileSize()){
	        removedIndex = i;
	    }
	}
	files.erase(files.begin()+removedIndex);
}

