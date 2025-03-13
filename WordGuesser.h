#ifndef WORDGUESSER_H_DEFINED

#define WORDGUESSER_H_DEFINED

// Főmenü függvénye
void WordGuesser();

// Elmentett pontszámok kiírása
void Scores();

// Játék
void Play(BinarySearchTree<string>& WordList);

// A megadott betűkből az összes lehetséges szó létrehozása és létező szavak elmentése
void GenerateWords(string& possibleChars, string currentString, vector<bool> usedChars, vector<string>& correctWords, BinarySearchTree<string>& WordList);

// Egy random szám a két megadott érték között
int rangeRand(int a, int b);


#include "WordGuesser.cpp"

#endif