
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <windows.h>

typedef std::vector<std::string> stringvec;

static class DirectoryHelper
{
private: 
	DirectoryHelper()
	{
	}

	bool isSystemDirectory(std::string dirName)
	{
		if (dirName == "." || dirName == "..")
			return true;
		else
			return false;
	}

public:

	void read_directory(const std::string& name, stringvec& v, int& cIndex)
	{
		std::string pattern(name);
		pattern.append("\\*");
		WIN32_FIND_DATA data;
		HANDLE hFind;
		std::string currentFileName;
		if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				cIndex++;
				currentFileName = name + "/" + data.cFileName;
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && !isSystemDirectory(data.cFileName)) {
					read_directory(currentFileName, v, cIndex);
				}
				else {
					v.push_back(currentFileName);
				}
			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
	}

};

