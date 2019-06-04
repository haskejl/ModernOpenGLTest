#pragma once

#include <fstream>
#include <string>

#include "Logger.h"

class FileLoader
{
private:
	std::fstream file;
public:
	FileLoader();
	~FileLoader();

	void openFile(std::string fileName);
	void readLine(std::string &lineOut);
	bool hasNextLine();
	void closeFile();
};

