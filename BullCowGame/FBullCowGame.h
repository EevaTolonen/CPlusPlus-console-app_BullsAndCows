/*
This is the header file for the FBullCowGame class including prototypes for the methods and variables done in the .cpp file
The game locig (no view code or direct user interaction)
The game is a simple guess the word game
*/

#pragma once
#include <string>
// never use "using namespace" in a header file!!! you loose track of what namespaces you have access to

// interesting way to see classes and istances of classes: if a class is like a factory, instance is a car coming out of that factory :D
using FString = std::string; // to make code more Unreal friendly
using int32 = int;			 // to make code more Unreal friendly

// this struct is outside the class since we don't need to access it from main.cpp, since it's only used for game logic
// all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


// Enumerations should be named with an uppercase E according to Unreal's coding standards
// if we use just 'enum', its scope is global (visible to both main.cpp and FBullCowGame.cpp), 
// and then we can't use same member names in other enums (f.ex. 'OK' wouldn't do), so 
// adding word 'class' makes its scope smaller
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public:
	// public INTERFACE to our class
	FBullCowGame(); // constructor for the instance in main.cpp i.e. when we create instance in main.cpp, it looks for a constructor (from .h file) if it's available and uses those params (from .cpp file)

	// const == in this case (after "()"), it means that those getter functions can't modify the variables they are accessing
	// ONLY works on methods that are defined in a class (so functions in main.cpp can't have const at the end, but methods in FBullCowGame.h which contains a class FBullCowGame, can be const

	// header file includes PROTOTYPES of our methods and variables
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	// counts bulls and cows and increases try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

	void Reset();


// ignore this for now and focus on public interface above
private:
	// private variables are called member variables
	// see constructor for initialisation of these private variables
	// these are initialised at compile time, in FBullCowGame.cpp the same variables are initialised at run time
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool bGameIsWon;
};
