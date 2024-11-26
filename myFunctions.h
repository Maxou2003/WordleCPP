#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <cstring>  
#include <sstream> 
#include <vector>

namespace MM {
	bool newParsedFile( std::ifstream& file, const std::string newfileName);
	bool parseFileToVector(std::ifstream& file, std::vector<std::vector<std::string>>& table, char delimiter);
	bool writeFileFromVector(std::ofstream& file,std::vector < std::vector<std::string>>& table, char delimiter );
	int testFile(std::ifstream& file);
	bool myRename(const char * oldFileName, const char* newFileName);
	bool isAllLetters(const std::wstring& str);
	std::wstring getWord(std::ifstream& file,const int& index);
	wchar_t toLowerCase(wchar_t c);
	std::wstring toLowerCase(std::wstring s1);
	bool charCompare(wchar_t c1, wchar_t c2);
	bool strCompare(std::wstring s1,std::wstring s2);
}