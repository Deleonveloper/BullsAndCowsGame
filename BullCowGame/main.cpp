/*This is the console executable, that mahe use the class FBullCowGame
This acts as the view in a MVC pattern, and is responsible for all user interactions.
For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSumary();

FBullCowGame BCGame; // instantiate a new Game

// the entry point for our application
int main()
{
	do
	{
		BCGame.Reset();

		PrintIntro();

		PlayGame();
	} 
	while (AskToPlayAgain());

	return 0;
}

// introducction of Game
void PrintIntro()
{
	//constexpr int32 WORD_LENGHT = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letters isogram I'm thinking of?\n" << std::endl;
	return;
}

// print sumarise of match game
void PrintGameSumary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WIN!!!\n";
	}
	else //if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) // not necessary, in loop of playGame checking the tries yet.
	{
		std::cout << "Bad luck, you lose...\n";
	}
}

// body of the game
void PlayGame()
{
	// loop for the number of turns asking for guesses
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl; // for testing MaxTries with console output

	//loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

		// print the guess back to them 
		//std::cout << "Your guess was: " << Guess << std::endl;

	}
	PrintGameSumary();
}


// get a guess from the player
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = " ";
	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() <<" of " << BCGame.GetMaxTries() << ": ";
		std::cout << "Introduce your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			break;
		}
		//std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we getno errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you wanna play again with the same hidden word: (y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	//std::cout << "This is Yes: " << ((Response[0] == 'y') || (Response[0] == 'Y')) << std::endl;
	//std::cout << "This is No: " << ((Response[0] == 'n') || (Response[0] == 'N')) << std::endl;
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}
