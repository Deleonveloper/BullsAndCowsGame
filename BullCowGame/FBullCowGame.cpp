#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLenghtToMaxTries = { {3,5},{4,5},{5,5},{6,9} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "pla";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


//validity status of the Guess
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))// if guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!= GetHiddenWordLenght())// if guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else // otherwise 
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();// necessary for compare int32 i with other int32 for HiddenWord lenght and assumin same lenght as guess
	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])// compare the letters against guess word
			{
				if (i == j)// if they match then
				{
					BullCowCount.Bulls++;// increment bulls if they're in the same place
				}
				else
				{
					BullCowCount.Cows++;// increment cows if they aren't in the same place
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//tratar las palabras de 0 y 1 letra como isogramas
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) //bucle para recorrer todas las letras del guess
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true)
		{//comprobar si ya estaba marcada
			//EGuessStatus::Not_Isogram;	//en ese caso no es un isograma
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; // add letter to map
		}
				
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}
