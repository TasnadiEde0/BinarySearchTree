#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include "WordGuesser.h"

using namespace std;

int rangeRand(int a, int b)
{
	return a + (rand() % (b - a + 1));
}

void GenerateWords(string& possibleChars, string currentString, vector<bool> usedChars, vector<string>& correctWords, BinarySearchTree<string>& WordList)
{
	if (currentString.size() >= 2 && WordList.findElement(currentString) && find(correctWords.begin(), correctWords.end(), currentString) == correctWords.end()) {
		correctWords.push_back(currentString);
	}

	for (int i = 0; i < possibleChars.size(); i++) {
		if (!usedChars[i]) {
			usedChars[i] = true;
			GenerateWords(possibleChars, currentString + possibleChars[i], usedChars, correctWords, WordList);
			usedChars[i] = false;
		}
	}
}

void Play(BinarySearchTree<string>& WordList)
{
	cout << endl;
	cout << "1 - Exit" << endl;
	cout << "2 - Next Round" << endl;

	int Rounds = 0;
	int Score = 0;
	vector<string> correctWords;
	string possibleChars = "", secondString = "";
	vector<string>::iterator iter;

	while (true)
	{
		possibleChars = "";
		secondString = "";
		char presChar;

		while (possibleChars.size() < 8) {			// Használandó betűk legenerálása
			presChar = 'a' + rangeRand(0, 25);

			if (possibleChars.find(presChar) < possibleChars.size()) {
				if (secondString.find(presChar) > secondString.size()) {
					possibleChars += presChar;
				}
			}
			else {
				possibleChars += presChar;
			}
		}

		sort(possibleChars.begin(), possibleChars.end());
		vector<bool> usedChars(possibleChars.size(), false);
		correctWords.clear();
		GenerateWords(possibleChars, "", usedChars, correctWords, WordList);

		if (correctWords.size() >= 3 && correctWords.size() <= 10) {

			Rounds++;

			cout << "Round " << Rounds << endl;
			cout << "Given characters: ";
			for (int i = 0; i < possibleChars.size(); i++) {
				cout << possibleChars[i] << " ";
			}
			cout << endl;
			cout << correctWords.size() << " combinations" << endl;

			string word = "";
			while (correctWords.size() != 0) {		// Szavak találgatása

				cout << "Give a guess: ";
				cin >> word;
				if (word == "1") {					// Kilépés a játékból
					cout << endl;
					cout << "You played " << Rounds << " rounds" << endl;
					cout << "Your score is " << Score << endl;
					cout << "Do you want to save your score? (y/n)" << endl;
					string input;
					cin >> input;
					if (input == "y") {
						string name;
						ofstream fout("game_data.txt", ofstream::app);
						cout << "Name: ";
						cin >> name;
						if (name.size() > 7) {
							while (name.size() > 7) {
								cout << "Name is too long" << endl;
								cout << "Name: ";
								cin >> name;
							}
						}
						fout << name << " " << Rounds << " " << Score << " ";
					}
					return;
				}
				if (word == "2") {
					break;
				}
				if (word == "3") {
					for (int i = 0; i < correctWords.size(); i++) {
						cout << correctWords[i] << " ";
					}
					cout << endl;
				}
				iter = find(correctWords.begin(), correctWords.end(), word);
				if (iter != correctWords.end()) {			//Helyes szó
					correctWords.erase(iter);
					cout << "Correct guess!" << endl;
					Score++;
				}
			}

			word = "";
			while (word != "y" && word != "n") {
				cout << "Next Round? (y/n)" << endl;
				cin >> word;
			}
			if (word == "n") {
				cout << "You played " << Rounds << " rounds" << endl;
				cout << "Your score is " << Score << endl;
				cout << "Do you want to save your score? (y/n)" << endl;
				string input;
				cin >> input;
				if (input == "y") {
					string name;
					ofstream fout("game_data.txt", ofstream::app);
					cout << "Name: ";
					cin >> name;
					if (name.size() > 7) {
						while (name.size() > 7) {
							cout << "Name is too long" << endl;
							cout << "Name: ";
							cin >> name;
						}
					}
					fout << name << " " << Rounds << " " << Score << " ";
				}
				return;
			}
		}
	}
}

void Scores()
{
	ifstream fin("game_data.txt");
	string text;

	cout << endl;
	cout << "Name" << '\t' << '\t' << "Rounds" << '\t' << "Score" << endl;
	while (fin >> text) {
		cout << text << '\t' << '\t';
		fin >> text;
		cout << text << '\t';
		fin >> text;
		cout << text << endl;
	}
	cout << endl;
}

void WordGuesser()
{
	BinarySearchTree<string> WordList("words.txt");
	int menuInput;
	srand(time(NULL));

	while (true) {

		cout << "1 - Play" << endl;
		cout << "2 - Scores" << endl;
		cout << "3 - Exit" << endl;

		cin >> menuInput;

		switch (menuInput) {
		case 1:
			Play(WordList);
			break;
		case 2:
			Scores();
			break;
		case 3:
			return;
		}
	}
}