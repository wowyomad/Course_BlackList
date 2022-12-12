#pragma once
#include <fstream>
#include <vector>


enum  class FileStatus
{
	Opened = 0,
	Empty = 1,
	NotOpened = 2
};

class File
{
public:
	template <class T>
	static bool ReadFileToVector(std::fstream& file, std::vector<std::shared_ptr<T>>& vector)
	{
		if (!file.is_open()) return false;
		while (true)
		{
			T temp;
			file >> temp;
			if (!file.eof())
			{
				vector.emplace_back(std::make_shared<T>(temp));
			}
			else
				break;
		}
		return true;
	}

	template <class T>
	static bool WriteVectorToFile(std::fstream& file, std::vector<std::shared_ptr<T>>& vector)
	{
		if (!file.is_open()) return false;
		for (std::shared_ptr<T>& it : vector)
		{
			file << *it.get();
		}
		return true;
	}

	template <class T>
	static bool ReadFile(const char* path, std::vector<std::shared_ptr<T>>& vector)
	{
		std::fstream file(path, std::ios::in);
		bool state = ReadFileToVector(file, vector);
		file.close();
		return state;
	}

	template <class T>
	static bool  WriteToFile(const char* path, std::vector<std::shared_ptr<T>>& vector)
	{
		if (vector.size() < 1) return false;
		std::fstream file(path, std::ios::out);
		bool state = WriteVectorToFile(file, vector);
		file.close();
		return state;
	}

	template<class T>
	static int GetFileStatus(const char* path, std::vector<T>& vector)
	{
		std::fstream file(path, std::ios::in);
		if (file.is_open())
		{
			int state;
			file.seekg(0, std::ios::end);
			if (file.tellg() > 0)
				state = FileStatus::Opened;
			else
				state = FileStatus::Empty;
			file.close();
			return state;
		}
		return FileStatus::NotOpened;
	}

};