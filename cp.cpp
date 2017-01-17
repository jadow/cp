#include <string>
#include <fstream>
#include "File_Service_Helper.h"

int main(int argc, char *argv[])
{
	/*
	copy [source][filename] [destination][filename]
	copy [source][filename] [destination]
	copy [source]           [destination]
	*/
	std::string sourceFileName, destinationFileName, sourceDirectory, destinationDirectory;

	if(argc == 3)
	{
		sourceFileName.assign(fileServiceHelper::getFileName(std::string(argv[1])));
		destinationFileName.assign(fileServiceHelper::getFileName(std::string(argv[2])));
		sourceDirectory.assign(fileServiceHelper::getDirectory(std::string(argv[1])));
		destinationDirectory.assign(fileServiceHelper::getDirectory(std::string(argv[2])));
	
		if(!destinationDirectory.size())
			destinationDirectory.assign(fileServiceHelper::getCurrentDirectory());

		if(!sourceDirectory.size())
			sourceDirectory.assign(fileServiceHelper::getCurrentDirectory());

		if(!sourceFileName.size() && !destinationFileName.size())
		{
			fileServiceHelper::copyDirectory(sourceDirectory, destinationDirectory);
		}
		else
		{
			if(!destinationFileName.size())
				destinationFileName.assign(sourceFileName);

			fileServiceHelper::copyFile(sourceDirectory.append(sourceFileName), destinationDirectory.append(destinationFileName));
		}
	}
	else
	{
		return 1;
	}

	return 0;
}