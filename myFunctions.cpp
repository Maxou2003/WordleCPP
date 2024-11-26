#pragma once
#include "myFunctions.h"
#include <codecvt>
#include <cwctype>  // Pour std::iswalpha
#include <filesystem>
#include <locale>

using namespace std;

namespace MM{
	
	bool newParsedFile(std::ifstream& file, const std::string newfileName) { // créé un nouveau fichier avec seulement
		string line;														// les premiers éléments parser de chaque ligne
		string word;
		vector<std::vector<std::string>> table;
		ofstream newFile(newfileName.c_str());

		if (file && newFile) {
			int error=parseFileToVector(file, table, ',');
			if (error)return 1;

			error = writeFileFromVector(newFile,table,' ');
			if (error)return 1;

			return 0;
		}
		else {
			return 1;
		}
	}
	bool parseFileToVector(std::ifstream& file, std::vector<std::vector<std::string>>& table, char delimiter) {
		if (file) {
			std::string line;
			std::string word;
			std::vector <std::string> content;
	
			while (getline(file, line)) {
				stringstream S(line);
				while (getline(S, word, delimiter)) {
					content.push_back(word);
				}
				table.push_back(content);
				while (content.size() > 0) {
					content.pop_back();
				}
			}
			return 0;
		}else return 1;
	}
	bool writeFileFromVector(std:: ofstream& file,std::vector < std::vector<std::string>>& table, char delimiter){
		string word;
		int index = 0;
		wstring str;
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		if (file)
		{
			for (size_t i = 0; i < table.size(); i++)
			{
				stringstream S(table[i][0]);
				index = 0;
				while (getline(S, word, delimiter)) {
					index++;	
				}
		
				if (index == 1 && converter.from_bytes(table[i][0]).size() == 5) {
					str = converter.from_bytes(table[i][0]);
					if(str.size()==5 && isAllLetters(str)) {
						file << table[i][0] << endl;
					}		
				}
			}
			return 0;
		}else return 1;
	}
	int testFile(std::ifstream& file) {
		std::string line;
		wstring str;
		int index = 0;
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		while (getline(file, line)) {
			if (converter.from_bytes(line).size() != 6) {
				return 0;
			}
			index++;
		}
		if (index == 0) {
			return 0;
		}
		return index;
		
	}
	bool myRename(const char* oldFileName, const char* newFileName) {
		try {
			remove(newFileName);
		}
		catch (const exception& e){
			cerr << e.what();
		}
		if (rename(oldFileName, newFileName) != 0){ return 1; }	
		else { return 0; }
		
	}
	bool isAllLetters(const std::wstring& str) {
		for (wchar_t ch : str) {
			if (!std::iswalpha(ch)) {
				return false;
			}
		}
		return true;
	}
	std::wstring getWord(std::ifstream& file, const int& index) {
		std::string str = "Prout";
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring output = L"";
		file.seekg(0, file.beg);
		for (int i = 0; i < index; i++) {
			getline(file, str);
		}
		for (wchar_t car : converter.from_bytes(str)) {
			if (car != '\r' and car!='\n') {
				output += car;
			}	
		}
		return output;
	}
	wchar_t toLowerCase(wchar_t c) {
		if (L'A' <= c && c<= L'Z') {
			return c - L'A' + L'a';
		}
		else {
			return c;
		}
	}
	bool charCompare(wchar_t c1, wchar_t c2) {
		wchar_t cl1 = toLowerCase(c1);
		wchar_t cl2 = toLowerCase(c2);
		wchar_t temp;

		if (cl1 == cl2) {
			return 1;
		}
		else {
			for (int i = 0; i < 2; i++) {
				if ((cl1 == L'é' || cl1 == L'è' || cl1 == L'ê') && cl2 == L'e') {
					return 1;
				}
				else if ((cl1 == L'ù' || cl1 == L'û') && cl2 == L'u') {
					return 1;
				}
				else if (cl1 == L'ô' && cl2 == L'o') {
					return 1;
				}
				else if (cl1 == L'î' && cl2 == L'i') {
					return 1;
				}
				else if ((cl1 == L'à' || cl1 == L'â') && cl2 == L'a') {
					return 1;
				}
				else if (cl1 == L'ç' && cl2 == L'c') {
					return 1;
				}
				temp = cl2;
				cl2 = cl1;
				cl1 = temp;
			}

		}
		return 0;

		
	}
	wstring toLowerCase(wstring s1) {
		for (int i = 0; i < s1.size();i++) {
			s1[i] = toLowerCase(s1[i]);
		}
		return s1;
	}
	bool strCompare(wstring s1, wstring s2) {
		if (s1 == s2) {
			return 1;
		}
		else if (s1.size() != s2.size()) {
			return 0;
		}
		else {
			for (int i = 0;i < s1.size();i++) {
				if (!charCompare(s1[i],s2[i])) {
					return 0;
				}
			}
		}
		return 1;
	}
}