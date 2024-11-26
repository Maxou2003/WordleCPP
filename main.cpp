#pragma once
#include "myFunctions.h"
#include <vector>
#include<filesystem>
#include <codecvt>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include "Wordle.h"

using namespace std;
using namespace MM;

int main() {

	
	char answer;
	string line;
	wstring wordToFind;
	int nbError = 0;
	const string nameFile("dico.csv"); 
	ifstream myFile(nameFile.c_str(), std::ios::binary);
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	
	srand(time(NULL));

	 
	if (myFile) {

		int nbLine = testFile(myFile);

		if (nbLine==0) {
			cout << "Your dictionary file isn't formated correctly to play wordle" << endl;
			newParsedFile(myFile, "new_" + nameFile);
			myFile.close();
			if (myRename(("new_" + nameFile).c_str(), (nameFile).c_str()) != 0) { perror("Error moving file"); }
			else { cout << "File moved successfully" << endl; }
			myFile.open(nameFile.c_str(), std::ios::binary);
			if (testFile(myFile) == 0) {
				cout << "We haven't been able to repair your library file... " << endl;
				return 1;
			}
		}
		cout << "Do you want to play a game of worlde ? (Y/N)" << endl;
		cin >> answer;

		if (toLowerCase(answer) != 'y') {
			myFile.close();
			cout << "Answer assertion error" << endl;
			exit(0);
		}

		myFile.close();
		myFile.open(nameFile.c_str(), std::ios::binary);

		int random = (rand() % nbLine);
		wstring guess;
		int result=1;
		Wordle myWordle(getWord(myFile, random));

		_setmode(_fileno(stdout), _O_U16TEXT); // set stdout to be the good format to display wstring ( can't display normal string with this setup)
		wcout << myWordle.getWordToFind() << endl;
		do {
			wcout << myWordle << L"Guess the word: ";
			wcin >> guess;
			wcout << L"Your guess is <" << guess << L">" << endl;
			result=myWordle.checkWord(guess);
			system("pause");
			system("cls");
		} while (myWordle.getNbTry() < 6 and result == 1);
		

		if (result == 0) {
			wcout << L"Well done! You won !" << endl;
			system("pause");
		}
		else {
			wcout << L"Sorry you lost this one, the word was " << myWordle.getWordToFind() << endl;
			system("pause");
		}
		
	}
	else {
		cout << "The file \"" << nameFile << "\" hasn't opened up correctly" << endl;
		return 1;
	}
	
	
	return 0;
}
