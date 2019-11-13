/*
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. For
game logic see FBullCowGame class.
*/

// <> are because we are using standard lilbraries
// "" for files we have created ourselves
// #pragma once to every file to make sure we don't double import files
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


// FText == used in Unreal for interacting with the user (main.cpp is a view for this whole game)
using FText = std::string; // to make code more Unreal friendly
using int32 = int; // to make code more Unreal friendly
int main();

// these are function prototypes as outside a class that make code after main accessible from main
// later we use a header file so this is n00b stuff
void PrintIntro();
FText GetValidGuess();

void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game instance, which we re-use across plays

// the entry point for our application
int main()
{
	bool FirstGame = true;
	// namespace for standard library, general way of accessing members from library is '::'
	do
	{
		if (!FirstGame) std::cout << "\n\n";
		else FirstGame = false;

		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	// constexpr is determinable right now and can't be changed during runtime
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}


// get a guess from the player
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";

		// all variables are named with an uppercase letter, since 
		// that's the coding standard of Unreal Engine

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break; // assume the guess is valid
			// std::cin == where we get it from, Guess == where we put it
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}


// loop for the number of turns asking for guesses while the game is not won and there are tries remaining
void PlayGame()
{
	// instance of our game
	// instantiates/makes an instance of a new game
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while ((!BCGame.IsGameWon()) && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


// prints whether player won or lose
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!" << "\n";
	}
	else
	{
		std::cout << "YOU LOSE - Better luck next time!" << "\n";
	}
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
