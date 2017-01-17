#ifndef _FILE_SERVICE_HELPER_H_
#include <string>

#define VALID_DIRECTORY		0
#define VALID_FILE			1
#define INVALID_DIRECTORY	2

#ifdef WIN32
#include <windows.h>
#endif

class fileServiceHelper
{
public:
	static std::string getFileName(std::string directory)
	{
		std::string tempt;
		std::size_t found = directory.find_last_of("/\\");
		tempt.assign(directory.substr(found+1));
		return tempt;
	}
	
	static std::string getDirectory(std::string directory)
	{
		std::string tempt;
		std::size_t found = directory.find_last_of("/\\");

		if(found > directory.size())
			return tempt;

		tempt.assign(directory.substr(0, found)).append("\\");
		return tempt;
	}
	
	static bool copyFile(std::string source, std::string destination)
	{	
		try
		{
			std::ifstream src(source.c_str(), std::ios::binary);
			std::ofstream dst(destination.c_str(), std::ios::binary);
			dst << src.rdbuf();
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

#ifdef WIN32
	static std::string getCurrentDirectory()
	{
	    char buffer[MAX_PATH];
		GetModuleFileNameA( NULL, buffer, MAX_PATH );
		std::size_t pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0,pos).append("\\");
	}

	static bool copyDirectory(std::string source, std::string destination)
	{	
		try
		{
			WIN32_FIND_DATAA ffd;
			HANDLE hFind = FindFirstFileA(std::string(source).append("\*").c_str(), &ffd);
			do
			{
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					copyFile(std::string(source).append(ffd.cFileName), std::string(destination).append(ffd.cFileName));
			}
			while (FindNextFileA(hFind, &ffd) != 0);
			FindClose(hFind);
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
#endif //WIN32

};
#define _FILE_SERVICE_HELPER_H_
#endif
