#include <map>
#define TMap std::map

#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	constexpr int32 MAX_TRIES = 5;

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // a validated guess has the same length as the hidden word
	for (int32 GPos = 0; GPos < WordLength; GPos++)
	{
		for (int32 HPos = 0; HPos < WordLength; HPos++)
		{
			char GChar = Guess[GPos];
			char HChar = MyHiddenWord[HPos];

			if (IsSameLetter(GChar, HChar))
			{
				if (IsSamePosition(GPos, HPos))
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}

		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) return true;

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	bool AllLower = true;
	for (auto Letter : Word)
	{
		AllLower &= IsLower(Letter);
	}
	return AllLower;
}

bool FBullCowGame::IsLower(char letter) const
{
	return letter >= 'a' && letter <= 'z';
}

bool FBullCowGame::IsSameLetter(char a, char b) const
{
	return a == b;
}

bool FBullCowGame::IsSamePosition(int32 x, int32 y) const
{
	return x == y;
}