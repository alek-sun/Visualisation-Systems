#pragma once
#include <fstream>
#include <string>


class File
{
public:
	static bool Exists(const char * filePath)
	{
		std::ifstream file(filePath);
		return file.good();
	}

	static bool Exists(const std::string & filePath)
	{
		return Exists( filePath.c_str() );
	}

	static std::string GetFileName(const char * filePath)
	{
		std::string str(filePath);

		size_t idx1 = str.find_last_of('\\');
		size_t idx2 = str.find_last_of('/');
		
		size_t idx = std::string::npos;
		{
			if (idx1 != std::string::npos)
			{
				idx = idx1;
			}

			if (idx2 != std::string::npos)
			{
				if (idx != std::string::npos)
				{
					idx = (idx < idx2) ? idx2 : idx;
				}
				else
				{
					idx = idx2;
				}
			}
		}
				
		if (idx == std::string::npos) return str;

		idx = idx + 1;
		size_t len = str.length() - idx;

		return str.substr(idx, len);
	}
	
	static std::string ReadAllText(const char * filePath)
	{
		std::ifstream ifs(filePath);
		std::string fileText;

		fileText.assign((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()) );

		return fileText;
	}

	static std::string ReadAllText(const std::string & filePath)
	{
		return ReadAllText( filePath.c_str() );
	}
};
