#include "FileLoader.h"

namespace ssfw
{
	FileLoader::FileLoader()
	{
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	}


	FileLoader::~FileLoader()
	{
	}

	//This method opens the specified file.
	void FileLoader::openFile(std::string fileName)
	{
		try
		{
			file.open(fileName, std::fstream::in);
		}
		catch (std::ifstream::failure e)
		{
			Logger::printErrMsg("Failed to open file: " + fileName + "\n", 10);
		}
	}

	//This method reads the next line of the file.
	void FileLoader::readLine(std::string &lineOut)
	{
		try
		{
			std::getline(file, lineOut, '\n');
			Logger::printMsg(lineOut, 1);
		}
		catch (std::ifstream::failure e)
		{
			Logger::printErrMsg(e.what(), 1);
			file.close();
		}
	}

	//This method determines if the file has another line.
	//Returns false if the EOF flag is set for the file object.
	bool FileLoader::hasNextLine()
	{
		//During an error state or on an EOL character, returns false
		if (!file.good()) return false;
		else return true;
	}

	//This method closes the file.
	void FileLoader::closeFile()
	{
		try
		{
			file.close();
		}
		catch (std::ifstream::failure e)
		{
			Logger::printErrMsg(e.what(), 10);
		}
	}
}
