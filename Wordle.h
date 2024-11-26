#pragma once
#include <vector>
#include <codecvt>
#include <iostream>
#include "myFunctions.h"

namespace MM {
	class Wordle
	{
	private:
		std::wstring _wordToFind;
		std::vector<wchar_t> _wellPlacedLetters;
		std::vector<wchar_t> _missPlacedLetters;
		std::wstring _guess;
		std::wstring _game;
		int _nbTry;
	public:
		Wordle(std::wstring word);
		bool checkWord(std::wstring guess); // modify _well, _miss placed letters and potentially nbErrors
		int getNbTry() const;
		std::wstring getWordToFind() const;
		std::wstring getGuess() const;
		std::vector<wchar_t> getWellPlacedLetters() const;
		std::vector<wchar_t> getMissPlacedLetters() const;
		std::wstring getGame() const;
	};
	std::wostream& operator<<(std::wostream& os, const Wordle& w);


}

