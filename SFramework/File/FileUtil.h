#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
namespace s_framework
{
	class FileUtil
	{
	private:
		static FileUtil* mInstance;

	public:
		FileUtil();
		~FileUtil();
		vector<string> split(const string & value, char delim);
		vector<string> loadFromFile(const string & filePath);

		static FileUtil* getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new FileUtil();
			}

			return mInstance;
		}
	};
}

