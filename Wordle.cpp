#include "Wordle.h"


namespace MM {
	Wordle::Wordle(std::wstring word) : _wordToFind(word) {
		_guess = L"";
		for (int i = 0;i < word.size(); i++) {
			_wellPlacedLetters.push_back(L'_');
			_missPlacedLetters.push_back(L'_');
			_guess += L"_";
		}
		_nbTry = 0;
		_game = L"";

	}
	bool Wordle::checkWord(std::wstring guess) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		if (guess.size() != _wordToFind.size()) {
			return 1;
		}
		else {
			_guess = guess;
			_nbTry++;
			for (int i = 0; i < _guess.size(); i++) {                   // We go through guess' letters
				if (charCompare(_wordToFind[i],_guess[i])) {
					_wellPlacedLetters[i] = _wordToFind[i];
					_game += converter.from_bytes("\033[32m") + _guess[i];
				}
				else {
					for (int j = 0; j < _wordToFind.size();j++) {
						if (i != j and charCompare(_wordToFind[j],_guess[i])) {
							_missPlacedLetters[i] = _guess[i];
							_game += converter.from_bytes("\033[31m") + _guess[i];
							break;
						}
					}
				}
				if (!charCompare(_wellPlacedLetters[i], _guess[i]) && !charCompare(_missPlacedLetters[i],_guess[i])) {
					_game += converter.from_bytes("\033[0m") + _guess[i];
				}
			}
		}
		_game += converter.from_bytes("\033[0m \n");
		if (strCompare(_wordToFind,_guess)){
			return 0;
		}
		return 1;

	}
	int Wordle::getNbTry() const {
		return _nbTry;
	}
	std::wstring Wordle::getWordToFind() const {
		return _wordToFind;
	}
	std::vector<wchar_t> Wordle::getWellPlacedLetters() const {
		return _wellPlacedLetters;
	}
	std::vector<wchar_t> Wordle::getMissPlacedLetters() const {
		return _missPlacedLetters;
	}
	std::wstring Wordle::getGuess() const {
		return _guess;
	}
	std::wstring Wordle::getGame() const {
		return _game;
	}

	std::wostream& operator<<(std::wostream& os, const Wordle& w) {
		os << w.getGame() << std::endl;
		return os;
	}

}