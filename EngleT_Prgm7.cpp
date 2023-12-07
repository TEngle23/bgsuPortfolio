#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
using namespace std;

///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/// 
/// Trenton Engle
/// CS2010 14:30
/// Program Assignment 7
/// 
/// Purpose: Create a "snowman" guessing game where the user
/// guesses letters in order to discover the secret word.
/// 
/// Inputs Needed: file with 100 words to form a word bank to
/// pull from, and a guessed letter
/// 
/// Processes: Read from dictionary file, sort the file into a
/// new sorted dictionary, select a word from the dict array,
/// get guesses and compare them to the selected secret word.
/// 
/// Results: For each incorrect guess, add 1 to the turn value
/// and show more of the snowman drawing. If the whole drawing
/// is shown, the user loses and is asked to play again. If
/// the user wins, a message is shown congratulating them, and
/// the user is asked to play again.
/// 
/// Reflection: This program was much more fun to make than
/// the other ones, mostly because it had a game that could
/// be played rather than just showing a single aspect of
/// the program. There were some parts where I got stuck, but
/// it was a fun challenge.
/// 
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int loadDictionary(string dict[])
{
	ifstream infile;
	int i = 0;

	//opening the file
	infile.open("pgm7.txt");

	//returning an error when the file cannot be opened
	if (infile.is_open() == false)
	{
		cout << "Error in opening file";
		return -1;
	}

	//putting the words from the file into the dict array
	while (!infile.fail())
	{
		infile >> dict[i];
		++i;
	}

	return i;
}

void drawSnowman(int turn)
{
	//setting everything up to print extended ascii characters based on
	//info I found online.
	setlocale(LC_ALL, "");
	_setmode(_fileno(stdout), _O_WTEXT);

	//creating the if statements to draw the sections of the snowman
	if (turn > 0)
	{
		wcout << L"     ┌───┐" << endl;
		wcout << L"     │   │" << endl;
		wcout << L"    ─┼───┼─" << endl;
	}
	if (turn > 1)
	{
		wcout << L"     │* *│" << endl;
		wcout << L"     │ │ │" << endl;
		wcout << L"    ┌┴───┴┐" << endl;
	}
	if (turn > 2)
	{
		wcout << L"   /│     │\\" << endl;
		wcout << L"  / │  @  │ \\" << endl;
		wcout << L" /  │     │  \\" << endl;
		wcout << L"   ┌┴─────┴┐" << endl;
	}
	if (turn > 3)
	{
		wcout << L"   │       │" << endl;
		wcout << L"   │   @   │" << endl;
		wcout << L"   │       │" << endl;
		wcout << L"   └───────┘" << endl;
	}

	if (turn > 5)
	{
		wcout << L"     ║   ║" << endl;
		wcout << L"     ║   ║" << endl;
		wcout << L"     ╝   ╚" << endl;
	}
	else if (turn > 4)
	{
		wcout << L"     ║" << endl;
		wcout << L"     ║" << endl;
		wcout << L"     ╝" << endl;
	}

	wcout << endl;
}

char getGuess()
{
	//getting the guess
	char guessLetter;
	wcout << "Enter your guess: " ;
	cin >> guessLetter;
	return guessLetter;
}

int setSecretWord(char secret[], string dict[], int wordcount)
{
	//getting a random seed for random numbers
	srand(time(0));
	int i;
	int randVal;
	string secretWord;

	//getting random word
	secretWord = dict[rand() % wordcount];

	//putting the word into an array of characters
	for (i = 0; i < secretWord.length(); ++i)
	{
		secret[i] = secretWord.at(i);
	}

	//getting the number in the dict array that hold the secret word
	for (i = 0; i < wordcount; ++i)
	{
		if (dict[i] == secretWord)
		{
			return i;
		}
	}
	return 0;
}

void showStatus(char guesses[], int secretLen)
{
	int i;

	//showing the guesses array
	for (i = 0; i < secretLen; ++i)
	{
		wcout << " " << guesses[i];
	}
	wcout << endl;
}

void initGuess(char guesses[], int secretLen)
{
	int i;

	//filling the guesses array with underscores
	for (i = 0; i < secretLen; ++i)
	{
		guesses[i] = '_';
	}
}

bool recordGuess(char secret[], char guesses[], char letter, int secretLen)
{
	int i;
	bool isThereLetter = false;

	//looping until the letters have been compared and placed into the
	//guesses array if applicable
	for (i = 0; i < secretLen; ++i)
	{
		if (letter == secret[i])
		{
			guesses[i] = letter;
			isThereLetter = true;
		}
		if (letter == (secret[i] - 32))
		{
			guesses[i] = letter + 32;
		}
	}
	//error if the guess isn't a letter
	if (isalpha(letter) == false)
	{
		wcout << L"The numbers mason, what do they mean?" << endl;
		wcout << L"Please only input alphabetic characters" << endl;
		return true;
	}

	if (isThereLetter == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isWin(char guesses[], int secretLen)
{
	int i;

	//looping to check if any of the letters are still remaining
	for (i = 0; i < secretLen; ++i)
	{
		if (isalpha(guesses[i]) == false)
		{
			return false;
		}
	}
	return true;
}

void showSecret(char secret[], int secretLen)
{
	int i;

	//looping to show the secret word
	for (i = 0; i < secretLen; ++i)
	{
		wcout << " " << secret[i];
	}
	wcout << endl;
}

void bubbleSort(string dict[], int size)
{
	int i;
	int j;
	string sortHold;
	ofstream sortedDictionary;

	//opening new sorted file
	sortedDictionary.open("prgm7Sorted.txt");

	//bubble sorting based on the zybooks example
	for (i = 0; i < size; ++i) {
		int swaps = 0;
		for (j = 0; j < size - i - 1; ++j)
		{
			if (dict[j] < dict[j + 1])
			{
				sortHold = dict[j + 1];
				dict[j + 1] = dict[j];
				dict[j] = sortHold;
				swaps = 1;
			}
		}
		if (!swaps)
		{
			break;
		}
	}

	for (i = 0; i < size; ++i)
	{
		sortedDictionary << dict[i] << endl;
	}

	sortedDictionary.close();
}

int main()
{
	const int wordCount = 100;
	string dict[wordCount];
	char secretWord[wordCount];
	char guessArr[wordCount];
	char lastGuess;
	char continueChar = 'y';
	int secretWordLength;
	int turn = 0;
	int secretWordVal;

	//exiting if loading the dictionary fails
	if (loadDictionary(dict) == -1)
	{
		return 0;
	}

	bubbleSort(dict, wordCount);

	//outter loop to continue the game
	while (continueChar == 'y' || continueChar == 'Y')
	{
		//getting all of the information from the functions
		secretWordVal = setSecretWord(secretWord, dict, wordCount);
		secretWordLength = dict[secretWordVal].length();
		initGuess(guessArr, secretWordLength);

		//inner loop for checking if the game is won
		while (isWin(guessArr, secretWordLength) == false && turn != 6)
		{
			showStatus(guessArr, secretWordLength);
			lastGuess = getGuess();
			if (recordGuess(secretWord, guessArr, lastGuess, secretWordLength) == false)
			{
				//counting turns if there is an incorrect guess
				turn += 1;
			}
			//drawing the snowman based on the turns
			drawSnowman(turn);
		}
		//showing the secret word at the end of the game and asking if
		//the game should be continued with a new word
		showSecret(secretWord, secretWordLength);

		//winning message
		if (turn != 6)
		{
			wcout << L"-------------------" << endl;
			wcout << L"Congrats, You Won!!" << endl;
			wcout << L"-------------------" << endl;
		}
		//losing message
		if (turn == 6)
		{
			wcout << L"-------------------" << endl;
			wcout << L"Game over. You lost." << endl;
			wcout << L"-------------------" << endl;
		}
		turn = 0;
		wcout << "Play again [Y = play again]";
		cin >> continueChar;
		//clearing screen between games
		system("cls");
	}
	return 0;
}