#pragma once
#include <string>

using FString = std::string;
using int32 = int;


// inicialised all values to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // cosntructor

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString Guess) const;

	void Reset();
	// count Bull and Cows and increment # of tries
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	// see the constructor for know the inicialitation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString Word) const;
	bool IsLowercase(FString Word) const;
};