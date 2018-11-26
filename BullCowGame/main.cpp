/* 
This is the console executable that makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
FText GetValidGuess();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	PrintIntro();
	do {
		PlayGame();
		bPlayAgain = AskToPlayAgain();  // prints and reads from console
	}
	while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to bulls and Cows!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram of which I am thinking?\n";
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	// TODO change from FOR to WHILE loop once we are validating tries
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();

		// submit valid guess to receive bull & cow counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	while (Status != EGuessStatus::OK) {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram, a word with no repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in all lowercase letters. \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	}

	return Guess;
}

bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Would you like to play again? (y/n) ";
	std::getline(std::cin, Response);

	char Answer = Response[0];
	return (Answer == 'y' || Answer == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You won!\n";
	}
	else
	{
		std::cout << "Aww good tries, good tries. Better luck next time!\n";
	}
	return;
}