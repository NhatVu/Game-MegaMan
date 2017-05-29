#include "FileUtil.h"

s_framework::FileUtil::FileUtil()
{
}

s_framework::FileUtil::~FileUtil()
{

}

vector<string> s_framework::FileUtil::split(const string & value, char delim)
{
	vector<string> result;
	if (value.length() > 0) //Neu gia tri truyen vao khac null thi tien hanh cat
	{
		stringstream  values(value);
		string item;
		while (std::getline(values, item, delim))
		{
			if (item.length() > 0)
			{
				result.push_back(item);
			}
		}
	}
	return result;
}

vector<string> s_framework::FileUtil::loadFromFile(const string & filePath)
{
	ifstream* reader = new ifstream(filePath);
	string item;
	vector<string> result;
	if (reader->is_open())
	{
		while (!reader->eof())
		{
			std::getline(*reader, item);
			result.push_back(item);
		}
		reader->close();
	}
	return result;
}
