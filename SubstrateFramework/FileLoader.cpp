#include "FileLoader.h"

FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

//This method opens the specified file.
void FileLoader::openFile(std::string fileName)
{
	file.open(fileName, std::fstream::in);
}

//This method reads the next line of the file.
void FileLoader::readLine(std::string &lineOut)
{
	std::getline(file, lineOut, '\n');
}

//This method determines if the file has another line.
//Returns false if the EOF flag is set for the file object.
bool FileLoader::hasNextLine()
{
	if (file.eof()) return false;
	else return true;
}

//This method closes the file.
void FileLoader::closeFile()
{
	file.close();
}
