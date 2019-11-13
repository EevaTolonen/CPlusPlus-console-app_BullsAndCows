/*
This is FBullCow class that contains our game logic.
*/
#pragma once
#include "FBullCowGame.h"
#include <map>
#define Tmap std::map // to make code more Unreal friendly
// we make substitution and call std::map Tmap since it suites our needs, naming it Tmap goes according to Unreal's data types, which override standard ones
// REMEMBER: when including standard libraries, use <>, when including your own files, use ""

using int32 = int;

// these are initialised at run time, in FBullCowGame.h the same variables are initialised at compile time
FBullCowGame::FBullCowGame() { Reset(); } // default constructor

// wise to put your getter methods on top and nicely on one line, common practise and easy to read
// const == in this case (after "()", it means that those getter functions can't modify the variables they are accessing
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
// CHECK game state and return whether player won the game or not
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	// collection of max tries according to the length of the word
	Tmap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 8}, {5, 15} , {6, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "cats"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	// MyMaxTries = MAX_TRIES; no need to it 
	return;
}


//--------------------------------------------------------------
// INTRODUCTION TO PERFORMANCE AND BOG O NOTATION :D

// let's use a hash table!

// our word = planet  --> we have a table of letters of the alphabet, when we go through the hiddenWord, we mark 1 to that letter in the table and continue
// if same letter comes again, in table we will have a number 2, and we can stop since it's not an isogram!
//a | 1
//b |
//c |
//. |
//. |
//p | 1
//etc.
//--------------------------------------------------------------


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
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, increments turn and returns count
// if right letter in right place == bull, if right letter but in wrong place == cow
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	// set up a return variable/structure
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();


	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)  BullCowCount.Bulls++;
				else BullCowCount.Cows++;
			}
		}
	}
	bGameIsWon = (BullCowCount.Bulls == WordLength);
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) return true;

	//setup our map
	Tmap<char, bool> LetterSeen;	// we let compiler to decide the type of for loop objects
	//LetterSeen.clear();
	for (auto Letter : Word)		// for all letters of the word
	{
		Letter = tolower(Letter);	// handle mixed case
		if (LetterSeen[Letter])		// if the letter is in the map
		{
			return false;			// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add letter to the map as seen
		}
	}
	return true;
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() == 0) return true;

	for (auto Letter : Word)
	{
		if (!(Letter >= 65 && Letter <= 90)) continue;
		if (Letter == ' ') continue;
		if (!islower(Letter)) return false;
	}
	return true;
}
