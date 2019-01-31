///////////////////////////////////////////////////////////////
//  ______         _    _    _             _      _          //
//  | ___ \       | |  | |  | |           | |    (_)         //
//  | |_/ /  __ _ | |_ | |_ | |  ___  ___ | |__   _  _ __    //
//  | ___ \ / _` || __|| __|| | / _ \/ __|| '_ \ | || '_ \   //
//  | |_/ /| (_| || |_ | |_ | ||  __/\__ \| | | || || |_) |  //
//  \____/  \__,_| \__| \__||_| \___||___/|_| |_||_|| .__/   //
// CIST 2361                                        | |      //
// A program written by: DJ Cmar                    |_|      //
///////////////////////////////////////////////////////////////
#include<iostream>
#include<conio.h>				//allows detection of keyboard strikes and a more effiecent clear screen function
#include<fstream>
#include<cstring>
#include<string>
#include<Windows.h>
#include"MMSystem.h"			//for music and sound effects
#include<time.h>				//for the timer
#include<ctime>					//for random seeding
#pragma comment( lib, "Winmm.lib" )	//allows program to create an EXE with no issues
using namespace std;

class battleship
{
public:
		////mainline module that kicks the while thing off
	void mainLine(void);

private:
		////file stream objects. mianly for loading display arrays////
	fstream tempFile,
		playerFile,
		recordFile;
	
	ifstream menuFile,
		gameFile;

		////enumerated values to make coding easier to keep track of and understand////
	enum key {		//enumaerated values for ASCII & shortcuts to help make coding easier
		ENTER = 13, UP = 301, DOWN = 302,
		LEFT = 303, RIGHT = 304 };

	enum selection {
		VSPLR = 1, VSCOM = 2, SETTINGS = 3,
		PLAYER1 = 10, PLAYER2 = 20, COMPUTER = 30,
		PLAYER1ATT = 40, PLAYER2ATT = 50, BLANK = 100,
		CREDITS = 24, BACK = 23,
		EASY = 31, MEDIUM = 32, HARD = 33};

	enum icons {    //These represent the ship/ hit/ miss icons on the display
		NOTHING = 0, PATROL = 1, DESTROYER = 2,
		SUB = 3, BATTLESHIP = 4, CARRIER = 5, HIT = 6,
		MISS = 7, SINK = 8};

		////Game variables////
	string timeStamp;							//for holding a time stamp

	const int DISP_W = 60,						//array constants
		DISP_H = 30,
		ARR_W = 10,
		ARR_H = 10;

	char display[60][30];						//the entire display array

	int keyPress = 0,							//value that stores keystrokes. Works with enum key values
		menuSelection = VSCOM,					//menu selection that works with enum selection values
		settingsSelection = BACK,				//menu selection that works with enum selection values
		comDifficulty = MEDIUM,					//difficulty of the computer / default is set to medium
		gameMode = 0,							//game mode that works with enum selection values
		currentTurn = 0,						//variable to indicate whos turn it is
		turnNum = 0,							//indicates the turn number
		attackW = 0,							//variable to store attack coordinate for width
		attackH = 0,							//variable to store attack coordinate for height
		shipHit = NOTHING,						//variable to know which ship has been hit
		shipSunk = NOTHING,						//variable to know which ship has been sunk
		winner = BLANK,							//variable to know who won the game
		trackNum = 0,							//holds the variable for the soundtrack number
		blankArray[10][10],						//an array with all 0's for a blank display
		p1Array[10][10],						//p1's ship map
		p1atkArray[10][10],						//p1's attack map
		p2Array[10][10],						//p2's ship map
		p2atkArray[10][10],						//p2's attack map
		comArray[10][10];						//com's ship map


	bool waitingForInput = true,				//boolean values mainly for module flags
		arrowKeyPressed = false,
		atMenu = true,
		victory = false,
		vsCom = false,
		vsPlr = false,
		inputingString = false,
		firstHalfTurn = true;						//in between turns - true while 1st person goes - false while second goes

		////Modules////
	////main modules that kickoff the program////
	void init(void);
	void proc(void);
	void eoj(void);

	////mode modules that operate the flow of the game////
	void menu(void);				//operates main menu
	void loadSettings(void);		//operates the settings menu
	void inputMode(void);			//waits for user input
	void vsComputer(void);			//sets up game mode to play against computer
	void vsPlayer(void);			//sets up game mode to play against another player
	void setupPlayers(void);		//players 1 and 2 set up their ships on their board
	void setupComputer(void);		//computer sets up their board
	void placeMode(int selection);			//mode for placing ships on the map for any player
	void playerPlaceShip(int shipW, int shipH, int selection, int shipType);//moves and places your ships accepts ship wid & hei & player as arguments
	void comPlaceShip(int shipW, int shipH, int shipType);   //moves and places com ships accepts ship width & height as arguments
	void navMode(void);				//mode for highlighting spots on the game board
	void resetBoard(int selection);	//resets the array of the selection argumented
	void whoGoesFirst(int secondPerson);		//decides who goes first
	void takeTurn(void);			//makes one turn in any gametype elapse
	void targetMode(int selection);			//enables player to choose a target and fire
	void comAttack(int attempt);	//for when the computer goes to select a target to hit
	void checkForSink(int wIdx, int hIdx, int reciever);   //check to see if a ship has been sunk
	void checkForVictory();			//see if someone won the game

	////display modules that are designed to change or operate the display array////
	void loadImage(ifstream &menuFile);							//load image as an input only item
	void displayImage();										//clears screen and displays image from display array
	void manipPixel(int wpos,int hpos, char swapChar);			//change 1 character on the display array (does not update display)
	void updateMap(int selection);								//updates the display array to refect the enum selection argument
	void changeTopText(string text);							//clears and adds text argument to the top text box (does not update display)
	void clearTopText(void);									//clears top text box in display array (does not update display)
	void changeBottomText(string line1, string line2 = "");		//clears and adds text arguments to the bottom text box (does not update display)
	void clearBottomText(void);									//clears bottom text box in display array (does not update display)
	void addToInfoBox(string text);								//adds a line to the info box and pushes all other lines down one
	void highlightBoard(int wIdx, int hIdx);					//highlights the square on the game board that is inputed into the arguments
	void highlightPlacement(int wIdx, int hIdx, int shipW, int shipH);	//highlights two spots for placing ships on the game board based on arguments
	string vCord(int attackH);									//changes the vertical coordinate to match the related map character
	string hCord(int attackW);									//changes the horizontal coordinate to match the related map character

	////misc modules for random things that operate the game
	void changeSoundtrack(int change);							//change the music soundtrack
	void updateTime(void);										//updates the time for the time stamp


};


void main(void)
{
	battleship game;
	game.mainLine();

	return;
}

void battleship::mainLine(void)
{
	bool stillPlaying = true;

	while (stillPlaying)
	{
		init();
		proc();
	}
	eoj();

	return;
}

void battleship::init(void)
{

	if (recordFile.fail())						//if file does not exist
	{
		recordFile.open("recordData.ship", ios::out);	//create this file
		updateTime();
		recordFile << endl << timeStamp  << " ***Started the battleship program***\n\n";
	}
	else									//if file does exist
	{
		recordFile.open("recordData.ship", ios::out|ios::app);	//open this file in append mode
		updateTime();
		recordFile << endl << timeStamp << " ***Started the battleship program***\n\n";
	}

	unsigned seed = time(0);	//set up the seed for random numbers
	srand(seed);				//seed random numbers

	menu();						//call the menu function

	return;
}

void battleship::proc(void)
{
	gameFile.open("Board1.txt", ios::in);
	loadImage(gameFile);
	displayImage();

	currentTurn = 0;				//reset variable to indicate whos turn it is
	turnNum = 0;					//reset indicates the turn number
	attackW = 0;					//reset variable to store attack coordinate for width
	attackH = 0;					//reset variable to store attack coordinate for height
	shipHit = NOTHING;				//reset variable to know which ship has been hit
	shipSunk = NOTHING;				//reset variable to know which ship has been sunk
	winner = BLANK;					//reset winner variable
	waitingForInput = true;			//reset boolean values mainly for module flags
	victory = false;				//reset victory variable
	resetBoard(BLANK);				//add all 0's to the blank array
	resetBoard(PLAYER1);			//initlize p1 board with all 0's
	resetBoard(PLAYER1ATT);			//initlize p1 att board with all 0's

	if (gameMode == VSCOM)
	{
		resetBoard(COMPUTER);		//initlize com board with all 0's
		vsComputer();
	}
	else if (gameMode == VSPLR)
	{
		resetBoard(PLAYER2);		//initlize p2 board with all 0's
		resetBoard(PLAYER2ATT);		//initlize p2 att board with all 0's
		vsPlayer();
	}
	return;
}

void battleship::eoj(void)
{
	cout << "\n\n\nProgram will now exit. Thank you for playing Battleship!\n\n\n";
	updateTime();
	recordFile << endl << timeStamp << " ***Ended the battleship program***\n\n";
	recordFile.close();
	menuFile.close();
	system("pause");
	exit(1);
	return;
}

void battleship::menu(void)
{
	atMenu = true;
	vsCom = false;
	vsPlr = false;
	gameMode = 0;							//reset game mode variable to 0

	int coinFlip = ((rand() % 3));			//flip a coin

	if (coinFlip != 2)				//if heads
	{
		sndPlaySound("Stars & Stripes.wav", SND_LOOP | SND_ASYNC);		//loops stars and stripes
	}
	else if (coinFlip == 2)			//if tails
	{
		sndPlaySound("Rufus Welcoming.wav", SND_LOOP | SND_ASYNC);		//loops rufus welcoming
	}

	while (atMenu)
	{
		if (menuSelection == VSCOM)
		{
			menuFile.open("Menu1.txt", ios::in);
		}
		else if (menuSelection == VSPLR)
		{
			menuFile.open("Menu2.txt", ios::in);
		}
		else if (menuSelection == SETTINGS)
		{
			menuFile.open("Menu3.txt", ios::in);
		}

		loadImage(menuFile);
		displayImage();

		inputMode();
		if (keyPress == UP)
		{
			if (menuSelection == VSCOM)
			{
				menuSelection = SETTINGS;
			}
			else if (menuSelection == VSPLR)
			{
				menuSelection = VSCOM;
			}
			else if (menuSelection == SETTINGS)
			{
				menuSelection = VSPLR;
				displayImage();
			}
		}
		else if (keyPress == DOWN)
		{
			if (menuSelection == VSCOM)
			{
				menuSelection = VSPLR;
			}
			else if (menuSelection == VSPLR)
			{
				menuSelection = SETTINGS;
			}
			else if (menuSelection == SETTINGS)
			{
				menuSelection = VSCOM;
			}
		}
		else if (keyPress == ENTER)
		{
			if (menuSelection == VSCOM)
			{
				gameMode = VSCOM;
				atMenu = false;
			}
			else if (menuSelection == VSPLR)
			{
				gameMode = VSPLR;
				atMenu = false;
			}
			else if (menuSelection == SETTINGS)
			{
				loadSettings();
			}
		}
	}
	return;
}

void battleship::loadSettings(void)
{
	bool waiting = true,
		credits = true;
	menuFile.open("MenuQ.txt", ios::in);
	loadImage(menuFile);

	if (comDifficulty == HARD)
	{
		manipPixel(51, 12, 'H');	//difficulty selection box
		manipPixel(52, 12, 'A');	//difficulty selection box
		manipPixel(53, 12, 'R');	//difficulty selection box
		manipPixel(54, 12, 'D');	//difficulty selection box
		manipPixel(55, 12, ' ');	//difficulty selection box
		manipPixel(56, 12, ' ');	//difficulty selection box
	}
	else if (comDifficulty == EASY)
	{
		manipPixel(51, 12, 'E');	//difficulty selection box
		manipPixel(52, 12, 'A');	//difficulty selection box
		manipPixel(53, 12, 'S');	//difficulty selection box
		manipPixel(54, 12, 'Y');	//difficulty selection box
		manipPixel(55, 12, ' ');	//difficulty selection box
		manipPixel(56, 12, ' ');	//difficulty selection box
	}

	while (waiting)
	{
		displayImage();
		inputMode();
		if (keyPress == UP)
		{
			if (settingsSelection == BACK)
			{
				manipPixel(39, 21, ' ');	//brackets around main menu
				manipPixel(40, 21, ' ');	//brackets around main menu
				manipPixel(54, 21, ' ');	//brackets around main menu
				manipPixel(55, 21, ' ');	//brackets around main menu
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == CREDITS)
			{
				manipPixel(31, 18, ' ');	//brackets around credits
				manipPixel(32, 18, ' ');	//brackets around credits
				manipPixel(55, 18, ' ');	//brackets around credits
				manipPixel(56, 18, ' ');	//brackets around credits
				if (comDifficulty == EASY)
				{
					settingsSelection = EASY;
					manipPixel(36, 15, '<');	//brackets around easy
					manipPixel(37, 15, '<');	//brackets around easy
				}
				else if (comDifficulty == MEDIUM)
				{
					settingsSelection = MEDIUM;
					manipPixel(38, 15, '>');	//brackets around medium
					manipPixel(39, 15, '>');	//brackets around medium
					manipPixel(50, 15, '<');	//brackets around medium
					manipPixel(51, 15, '<');	//brackets around medium
				}
				else if (comDifficulty == HARD)
				{
					settingsSelection = HARD;
					manipPixel(52, 15, '>');	//brackets around hard
					manipPixel(53, 15, '>');	//brackets around hard
				}
			}
		}
		else if (keyPress == DOWN)
		{
			if (settingsSelection == EASY)
			{
				manipPixel(36, 15, ' ');	//brackets around easy
				manipPixel(37, 15, ' ');	//brackets around easy
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == MEDIUM)
			{
				manipPixel(38, 15, ' ');	//brackets around medium
				manipPixel(39, 15, ' ');	//brackets around medium
				manipPixel(50, 15, ' ');	//brackets around medium
				manipPixel(51, 15, ' ');	//brackets around medium
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == HARD)
			{
				manipPixel(52, 15, ' ');	//brackets around hard
				manipPixel(53, 15, ' ');	//brackets around hard
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == CREDITS)
			{
				manipPixel(31, 18, ' ');	//brackets around credits
				manipPixel(32, 18, ' ');	//brackets around credits
				manipPixel(55, 18, ' ');	//brackets around credits
				manipPixel(56, 18, ' ');	//brackets around credits
				settingsSelection = BACK;
				manipPixel(39, 21, '>');	//brackets around main menu
				manipPixel(40, 21, '>');	//brackets around main menu
				manipPixel(54, 21, '<');	//brackets around main menu
				manipPixel(55, 21, '<');	//brackets around main menu
			}
		}
		else if (keyPress == LEFT)
		{
			if (settingsSelection == MEDIUM)
			{
				manipPixel(38, 15, ' ');	//brackets around medium
				manipPixel(39, 15, ' ');	//brackets around medium
				manipPixel(50, 15, ' ');	//brackets around medium
				manipPixel(51, 15, ' ');	//brackets around medium
				settingsSelection = EASY;
				comDifficulty = EASY;
				manipPixel(51, 12, 'E');	//difficulty selection box
				manipPixel(52, 12, 'A');	//difficulty selection box
				manipPixel(53, 12, 'S');	//difficulty selection box
				manipPixel(54, 12, 'Y');	//difficulty selection box
				manipPixel(55, 12, ' ');	//difficulty selection box
				manipPixel(56, 12, ' ');	//difficulty selection box
				manipPixel(36, 15, '<');	//brackets around easy
				manipPixel(37, 15, '<');	//brackets around easy
			}
			else if (settingsSelection == HARD)
			{
				manipPixel(52, 15, ' ');	//brackets around hard
				manipPixel(53, 15, ' ');	//brackets around hard
				settingsSelection = MEDIUM;
				comDifficulty = MEDIUM;
				manipPixel(51, 12, 'M');	//difficulty selection box
				manipPixel(52, 12, 'E');	//difficulty selection box
				manipPixel(53, 12, 'D');	//difficulty selection box
				manipPixel(54, 12, 'I');	//difficulty selection box
				manipPixel(55, 12, 'U');	//difficulty selection box
				manipPixel(56, 12, 'M');	//difficulty selection box
				manipPixel(38, 15, '>');	//brackets around medium
				manipPixel(39, 15, '>');	//brackets around medium
				manipPixel(50, 15, '<');	//brackets around medium
				manipPixel(51, 15, '<');	//brackets around medium
			}
		}
		else if (keyPress == RIGHT)
		{
			if (settingsSelection == EASY)
			{
				manipPixel(36, 15, ' ');	//brackets around easy
				manipPixel(37, 15, ' ');	//brackets around easy
				settingsSelection = MEDIUM;
				comDifficulty = MEDIUM;
				manipPixel(51, 12, 'M');	//difficulty selection box
				manipPixel(52, 12, 'E');	//difficulty selection box
				manipPixel(53, 12, 'D');	//difficulty selection box
				manipPixel(54, 12, 'I');	//difficulty selection box
				manipPixel(55, 12, 'U');	//difficulty selection box
				manipPixel(56, 12, 'M');	//difficulty selection box
				manipPixel(38, 15, '>');	//brackets around medium
				manipPixel(39, 15, '>');	//brackets around medium
				manipPixel(50, 15, '<');	//brackets around medium
				manipPixel(51, 15, '<');	//brackets around medium
			}
			else if (settingsSelection == MEDIUM)
			{
				manipPixel(38, 15, ' ');	//brackets around medium
				manipPixel(39, 15, ' ');	//brackets around medium
				manipPixel(50, 15, ' ');	//brackets around medium
				manipPixel(51, 15, ' ');	//brackets around medium
				settingsSelection = HARD;
				comDifficulty = HARD;
				manipPixel(51, 12, 'H');	//difficulty selection box
				manipPixel(52, 12, 'A');	//difficulty selection box
				manipPixel(53, 12, 'R');	//difficulty selection box
				manipPixel(54, 12, 'D');	//difficulty selection box
				manipPixel(55, 12, ' ');	//difficulty selection box
				manipPixel(56, 12, ' ');	//difficulty selection box
				manipPixel(52, 15, '>');	//brackets around hard
				manipPixel(53, 15, '>');	//brackets around hard
			}
		}
		else if (keyPress == ENTER)
		{
			if (settingsSelection == EASY)
			{
				manipPixel(36, 15, ' ');	//brackets around easy
				manipPixel(37, 15, ' ');	//brackets around easy
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == MEDIUM)
			{
				manipPixel(38, 15, ' ');	//brackets around medium
				manipPixel(39, 15, ' ');	//brackets around medium
				manipPixel(50, 15, ' ');	//brackets around medium
				manipPixel(51, 15, ' ');	//brackets around medium
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == HARD)
			{
				manipPixel(52, 15, ' ');	//brackets around hard
				manipPixel(53, 15, ' ');	//brackets around hard
				settingsSelection = CREDITS;
				manipPixel(31, 18, '>');	//brackets around credits
				manipPixel(32, 18, '>');	//brackets around credits
				manipPixel(55, 18, '<');	//brackets around credits
				manipPixel(56, 18, '<');	//brackets around credits
			}
			else if (settingsSelection == CREDITS)
			{
				while (credits)
				{
					system("CLS");
					cout << "\nA Program by DJ Cmar\n\nmade for CIST 2361\n\n\n"
						<< "\nThis program is only made possible by the support of loved ones."
						<< "\n\nNamely his girlfriend Maria Lerma who stood by him while"
						<< "\nhis eyes swelled up and his back broke for absolutely no reason..."
						<< "\n\nWell, there you have it folks. my first big game..."
						<< "\n\n\t-DJ Cmar\n\n\n"
						<< "\n\n\t\t::M U S I C  C R E D I T S::"
						<< "\n\n\t-I do not own any of the music that I use-"
						<< "\n\nhttps://www.youtube.com/watch?v=z-fleXlIRbs	--rufus welcoming ceremony"
						<< "\nhttps://www.youtube.com/watch?v=-mRn9chmRAY	--stars and stripes forever"
						<< "\nhttps://www.youtube.com/watch?v=64tkl3SjgxA	--smb3 orchestral airship theme"
						<< "\nhttps://www.youtube.com/watch?v=jw3Ea8fKIxU	--unfortunate son instr CCR"
						<< "\nhttps://www.youtube.com/watch?v=-YCN-a0NsNk	--ff7 victory theme"
						<< "\nhttps://www.youtube.com/watch?v=Czc9SQeOjFk	--halo 4 final mission theme"
						<< "\n\nP.S. good luck finding the easter egg..."
						<< "\n\nPress ENTER to continue....";
					inputMode();
					if (keyPress == ENTER)
					{
						credits = false;
					}
				}
			}
			else if (settingsSelection == BACK)
			{
				waiting = false;
			}
		}
	}

	menu();			//go back to menu
	return;
}

void battleship::inputMode(void)
{
	int secretCounter = 0;

	waitingForInput = true;

	while (waitingForInput)					//while we need user input before we can continue...
	{
		if (_kbhit())								//Prevents an infinite loop when '\n' is inputted
		{
			while (_kbhit())							//if a keyboard press is detected
			{
				keyPress = _getch();						//assigns the keyboard press value to 'keypress' and resets the buffer
				if (keyPress == 224)						//arrow keys return two values... the first one is always 224
				{
					arrowKeyPressed = true;					//if an arrow key has been pressed, trip the flag
				}
			}
			if (keyPress == 75 && arrowKeyPressed)
			{
				keyPress = LEFT;
				arrowKeyPressed = false;                   //reset the arrow key flag
				waitingForInput = false;
			}
			else if (keyPress == 72 && arrowKeyPressed)
			{
				keyPress = UP;
				arrowKeyPressed = false;                   //reset the arrow key flag
				waitingForInput = false;
			}
			else if (keyPress == 77 && arrowKeyPressed)
			{
				keyPress = RIGHT;
				arrowKeyPressed = false;                   //reset the arrow key flag
				waitingForInput = false;
			}
			else if (keyPress == 80 && arrowKeyPressed)
			{
				keyPress = DOWN;
				arrowKeyPressed = false;                   //reset the arrow key flag
				waitingForInput = false;
			}
			else if (keyPress == ENTER)
			{
				waitingForInput = false;
			}
			else if (keyPress == 'r')
			{
				waitingForInput = false;
			}
			else if (keyPress == 'y')
			{
				waitingForInput = false;
			}
			else if (keyPress == 'n')
			{
				waitingForInput = false;
			}
			else if (keyPress == '1')
			{
				waitingForInput = false;
			}
			else if (keyPress == '2')
			{
				waitingForInput = false;
			}
			else if (keyPress == '3')
			{
				waitingForInput = false;
			}
			else if (keyPress == 'm')
			{
				waitingForInput = false;
			}
			else if (keyPress == 'a' && !inputingString && !atMenu)	//if it is a keypress for sound
			{
				changeSoundtrack(-1);
				waitingForInput = false;
			}
			else if (keyPress == 's' && !inputingString && !atMenu)	//if it is a keypress for sound
			{
				changeSoundtrack(1);
				waitingForInput = false;
			}
			else if (keyPress == 'q')	//if it is q keypress
			{
				eoj();				//run end of job to wrap things up
			}
			else if (keyPress == 'z')	//if it is z keypress
			{
				secretCounter++;
				if (secretCounter == 5)
				{
					sndPlaySound("Halo4 End.wav", SND_LOOP | SND_ASYNC);		
					cout << "\n\nHAHA, you found it. My easter egg.... yep.. ;) -DJ";
					system("pause");
					secretCounter = 0;
				}
			}
		}
	}

	//		break;      <-- put this in code when you want to break out of a while loop


	return;
}

void battleship::loadImage(ifstream &imgFile)
{
	if (!imgFile)
	{
		cout << "\nERROR: Image failed to load.";
		system("pause");
	}

	cout << flush;

	for (int height = 0; height < DISP_H; height++)
	{

		for (int width = 0; width < DISP_W; width++)
		{
			imgFile.get(display[width][height]);
		}

	}

	imgFile.close();

	return;
}

void battleship::displayImage(void)
{
	system("CLS");

	for (int height = 0; height < DISP_H; height++)
	{

		for (int width = 0; width < DISP_W; width++)
		{
			cout << display[width][height];
		}

	}

	return;
}

void battleship::manipPixel(int wpos, int hpos, char swapChar)				//function that swaps out a char in the display
{

	for (int height = 0; height < DISP_H; height++)
	{

		for (int width = 0; width < DISP_W; width++)
		{
			if (wpos == width && hpos == height)
			{
				display[width][height] = swapChar;
			}
		}
	}
		
	return;
}

void battleship::vsComputer(void)
{
//	tempFile.open("temp.txt", ios::out);					for creating player records
	updateTime();
	recordFile << endl << timeStamp << " Selected game mode vs Computer\n\n";

	if (comDifficulty == EASY)
	{
		updateTime();
		recordFile << endl << timeStamp << " Computer is set to EASY difficulty\n\n";
	}
	else if (comDifficulty == MEDIUM)
	{
		updateTime();
		recordFile << endl << timeStamp << " Computer is set to MEDIUM(default) difficulty\n\n";
	}
	else if (comDifficulty == HARD)
	{
		updateTime();
		recordFile << endl << timeStamp << " Computer is set to HARD difficulty\n\n";
	}

	vsCom = true;
	setupPlayers();
	updateMap(BLANK);
	setupComputer();
	whoGoesFirst(COMPUTER);
	updateMap(PLAYER1);
	firstHalfTurn = true;	//set the turn to the first half
	turnNum++;				//update the turn number and change the board accordingly
	updateTime();
	recordFile << endl << timeStamp << " Turn " << turnNum << "\n\n";

	victory = false;
	while (!victory)			//while there is no victory
	{
		takeTurn();				//take turn
		checkForVictory();		//check for victory after the turn
	}

	updateMap(BLANK);			//revert the map to a blank state

	return;
}

void battleship::vsPlayer(void)
{
	//	tempFile.open("temp.txt", ios::out);					for creating player records
	updateTime();
	recordFile << endl << timeStamp << " Selected game mode vs Player\n\n";
	vsPlr = true;
	setupPlayers();
	updateMap(BLANK);
	whoGoesFirst(PLAYER2);
	firstHalfTurn = true;	//set the turn to the first half
	turnNum++;				//update the turn number and change the board accordingly
	updateTime();
	recordFile << endl << timeStamp << " Turn " << turnNum << "\n\n";

	victory = false;
	while (!victory)			//while there is no victory
	{
		takeTurn();				//take turn
		checkForVictory();		//check for victory after the turn
	}

	updateMap(BLANK);			//revert the map to a blank state

	return;
}

void battleship::takeTurn(void)
{
	string topText,
		bottomText1,
		bottomText2,
		boxText;

	int maxVal = 100,		//values for random number generator
		minVal = 0,
		hitChance = 0,		//chance for computer to hit the player
		hitAttempt = 0,		//variable to store for the attempt of hitting
		num1 = 0,			//hold turn number values
		num2 = 0;

	bool waitForInput = true;

	if (turnNum > 9 && turnNum < 20)
	{
		num1 = 1;
		num2 = (turnNum - 10);
	}
	else if (turnNum > 19 && turnNum < 30)
	{
		num1 = 2;
		num2 = (turnNum - 20);
	}
	else if (turnNum > 29 && turnNum < 40)
	{
		num1 = 3;
		num2 = (turnNum - 30);
	}
	else if (turnNum > 39 && turnNum < 50)
	{
		num1 = 4;
		num2 = (turnNum - 40);
	}
	else if (turnNum > 49 && turnNum < 60)
	{
		num1 = 5;
		num2 = (turnNum - 50);
	}
	else if (turnNum > 59 && turnNum < 70)
	{
		num1 = 6;
		num2 = (turnNum - 60);
	}
	else if (turnNum > 69 && turnNum < 80)
	{
		num1 = 7;
		num2 = (turnNum - 70);
	}
	else if (turnNum > 79 && turnNum < 90)
	{
		num1 = 8;
		num2 = (turnNum - 80);
	}
	else if (turnNum > 89 && turnNum < 100)
	{
		num1 = 9;
		num2 = (turnNum - 90);
	}
	else if (turnNum >= 100)
	{
		turnNum = 0;
	}

	if (turnNum <= 9)
	{
		manipPixel(11,4,(turnNum + 48));
	}
	else if (turnNum > 9)
	{
		manipPixel(12, 4, (num2 + 48));
		manipPixel(11, 4, ' ');
		manipPixel(10, 4, (num1 + 48));
	}
	displayImage();

	if (vsCom)
	{
		if (currentTurn == PLAYER1)
		{
			targetMode(PLAYER1);
		}
		else if (currentTurn == COMPUTER)
		{
			hitChance = ((rand() % (maxVal - minVal + 1)) + minVal);
			if (comDifficulty == EASY)
			{
				if (hitChance <= 20)
				{
					hitAttempt = HIT;
				}
				else if (hitChance > 20)
				{
					hitAttempt = MISS;
				}
			}
			else if (comDifficulty == MEDIUM)
			{
				if (hitChance <= 30)
				{
					hitAttempt = HIT;
				}
				else if (hitChance > 30)
				{
					hitAttempt = MISS;
				}
			}
			else if (comDifficulty == HARD)
			{
				if (hitChance <= 40)
				{
					hitAttempt = HIT;
				}
				else if (hitChance > 40)
				{
					hitAttempt = MISS;
				}
			}
			comAttack(hitAttempt);
			updateMap(PLAYER1);
			if (hitAttempt == HIT && shipSunk == NOTHING)
			{
				//designed to look like "COM >> A2 >> HIT
				boxText = "COM HIT ";
				boxText += vCord(attackH);
				boxText += hCord(attackW);
				addToInfoBox(boxText);
				topText = "COM >> ";
				topText += vCord(attackH);
				topText += hCord(attackW);
				topText += " >> HIT";
				bottomText1 = "The computer has hit your ";
				if (shipHit == PATROL)
				{
					bottomText1 += "patrol boat at ";
				}
				else if (shipHit == DESTROYER)
				{
					bottomText1 += "destroyer at ";
				}
				else if (shipHit == SUB)
				{
					bottomText1 += "submarine at ";
				}
				else if (shipHit == BATTLESHIP)
				{
					bottomText1 += "battleship at ";
				}
				else if (shipHit == CARRIER)
				{
					bottomText1 += "aircraft carrier at ";
				}
				bottomText1 += vCord(attackH);
				bottomText1 += hCord(attackW);
				bottomText2 = "Press ENTER to start your turn";
			}
			else if (hitAttempt == HIT && shipSunk != NOTHING)
			{
				boxText = "SUNK ";
				topText = "COM >> ";
				topText += vCord(attackH);
				topText += hCord(attackW);
				topText += " >> SINK >> ";
				bottomText1 = "The computer has sunk your ";
				if (shipSunk == PATROL)
				{
					boxText += "P-BOAT";
					topText += "PATROL BOAT";
					bottomText1 += "patrol boat at ";
				}
				else if (shipSunk == DESTROYER)
				{
					boxText += "DESTR";
					topText += "DESTROYER";
					bottomText1 += "destroyer at ";
				}
				else if (shipSunk == SUB)
				{
					boxText += "SUB";
					topText += "SUBMARINE";
					bottomText1 += "submarine at ";
				}
				else if (shipSunk == BATTLESHIP)
				{
					boxText += "BATTLE";
					topText += "BATTLESHIP";
					bottomText1 += "battleship at ";
				}
				else if (shipSunk == CARRIER)
				{
					boxText += "CARIR";
					topText += "AIRCRAFT CARRIER";
					bottomText1 += "aircraft carrier at ";
				}
				addToInfoBox(boxText);
				bottomText1 += vCord(attackH);
				bottomText1 += hCord(attackW);
				boxText = "COM SINK ";
				boxText += vCord(attackH);
				boxText += hCord(attackW);
				addToInfoBox(boxText);
				bottomText2 = "Press ENTER to start your turn";
			}
			else if (hitAttempt == MISS)
			{
				boxText = "COM MISS ";
				boxText += vCord(attackH);
				boxText += hCord(attackW);
				addToInfoBox(boxText);
				topText = "COM >> ";
				topText += vCord(attackH);
				topText += hCord(attackW);
				topText += " >> MISS";
				bottomText1 = "The computer tried to hit you at location ";
				bottomText1 += vCord(attackH);
				bottomText1 += hCord(attackW);
				bottomText2 = "Press ENTER to start your turn";
			}
			updateTime();
			recordFile << timeStamp << " " << topText << "\n";				//add computer attack to the records
			changeTopText(topText);
			changeBottomText(bottomText1, bottomText2);
			displayImage();
		}
		if (currentTurn == PLAYER1)				//swap the turn ownership to the other person
		{
			currentTurn = COMPUTER;
		}
		else if (currentTurn == COMPUTER)
		{
			while (waitForInput)
			{
				inputMode();
				if (keyPress == ENTER)
				{
					waitForInput = false;		//set the flag off
				}
			}
			currentTurn = PLAYER1;
		}
	}
	else if (vsPlr)
	{
		if (currentTurn == PLAYER1)
		{
			targetMode(PLAYER1);
		}
		else if (currentTurn == PLAYER2)
		{
			targetMode(PLAYER2);
		}
		if (currentTurn == PLAYER1)				//swap the turn ownership to the other person
		{
			currentTurn = PLAYER2;
		}
		else if (currentTurn == PLAYER2)
		{
			currentTurn = PLAYER1;
		}
	}
	shipHit = NOTHING;				//reset the ship hit variable to nothing

	if (firstHalfTurn)
	{
		firstHalfTurn = false;
	}
	else if (!firstHalfTurn)
	{
		boxText = "--Turn  ";
		boxText += to_string(turnNum);
		boxText += "--";
		addToInfoBox(boxText);
		boxText = " ";
		addToInfoBox(boxText);
		turnNum++;						//once the second half has gone, add another turn number
		updateTime();
		recordFile << endl << timeStamp << " Turn " << turnNum << "\n\n";
		firstHalfTurn = true;
	}

	return;
}

void battleship::comAttack(int attempt)
{
	bool lockOn = true;

	int wIdx = 0,
		hIdx = 0,
		minVal = 0,
		maxVal = 9,
	timesFound = 0;


	for (int hIndex = 0; hIndex < ARR_H; hIndex++)					//height loop
	{
		for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
		{
			if (p1Array[wIndex][hIndex] == NOTHING)                   	//if there are spots to miss...
			{
				timesFound++;											//add to the counter
			}
		}
	}
	if (timesFound < 1)											//if there are no more places to miss...
	{
		attempt = HIT;										//then it is a hit by default
	}


	if (attempt == HIT)			//if the computer is going to hit a target
	{
		while (lockOn)		//locking onto ship....
		{
			wIdx = ((rand() % (maxVal - minVal + 1)) + minVal);		//randomly generate width and height variables
			hIdx = ((rand() % (maxVal - minVal + 1)) + minVal);
			if ((wIdx >= 0 && wIdx <= 9) && (hIdx >= 0 && hIdx <= 9))	//ensure the coordinate is valid and does not go off map
			{
				for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
				{
					for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
					{
						if (wIndex == wIdx && hIndex == hIdx)
						{
							if (p1Array[wIndex][hIndex] == PATROL || p1Array[wIndex][hIndex] == DESTROYER ||		//if a ship is here
								p1Array[wIndex][hIndex] == SUB || p1Array[wIndex][hIndex] == BATTLESHIP ||
								p1Array[wIndex][hIndex] == CARRIER)
							{
								checkForSink(wIndex, hIndex, PLAYER1);
								p1Array[wIndex][hIndex] = HIT;
								attackH = hIndex;				//store attack coordinates
								attackW = wIndex;
								lockOn = false;
							}
						}
					}
				}
			}
		}
	}
	else if (attempt == MISS)
	{
		while (lockOn)		//locking onto nothing....
		{
			wIdx = ((rand() % (maxVal - minVal + 1)) + minVal);		//randomly generate width and height variables
			hIdx = ((rand() % (maxVal - minVal + 1)) + minVal);
			if ((wIdx >= 0 && wIdx <= 9) && (hIdx >= 0 && hIdx <= 9))	//ensure the coordinate is valid and does not go off map
			{
				for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
				{
					for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
					{
						if (wIndex == wIdx && hIndex == hIdx)
						{
							if (p1Array[wIndex][hIndex] == NOTHING)			//try to hit nothing
							{
								p1Array[wIndex][hIndex] = MISS;				//change the tile to miss
								attackH = hIndex;						//store attack coordinates
								attackW = wIndex;
								lockOn = false;
							}
						}
					}
				}
			}
		}

	}

	return;
}

void battleship::setupPlayers(void)
{
	bool waitForP1 = true,
		waitForRules = true;

	string bottomText1 = "Welcome to Battleship... A game of strategy",
		bottomText2 = "Please press ENTER to continue",
		topText = "Welcome to Battleship";

	changeBottomText(bottomText1, bottomText2);
	changeTopText(topText);
	displayImage();

	while (waitForP1)
	{
		inputMode();
		if (keyPress == ENTER)
		{
			waitForP1 = false;		//set the flag off
		}
	}

	bottomText1 = "To change the music to the next track, press S";
	bottomText2 = "To change the music to the previous track, press A";
	topText = "Press ENTER to continue";

	changeBottomText(bottomText1, bottomText2);
	changeTopText(topText);
	displayImage();

	waitForP1 = true;			//turn the flag back on
	while (waitForP1)
	{
		inputMode();
		if (keyPress == ENTER)
		{
			waitForP1 = false;		//set the flag off
		}
	}

	bottomText1 = "Would you like an explanation of the rules?";
	bottomText2 = "Press Y for yes and N for no";
	topText = "Press Y or N to continue";

	changeBottomText(bottomText1, bottomText2);
	changeTopText(topText);
	displayImage();

	waitForP1 = true;			//turn the flag back on
	while (waitForP1)
	{
		inputMode();
		if (keyPress == 'y')
		{
			waitForRules = true;
			while (waitForRules)
			{
				bottomText1 = "The goal of battleship is to sink your enemy ships.";
				bottomText2 = "before the enemy sinks your ships.";
				topText = "Press ENTER to continue";

				changeBottomText(bottomText1, bottomText2);
				changeTopText(topText);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			waitForRules = true;
			while(waitForRules)
			{
				bottomText1 = "One player will place their ships on this map without";
				bottomText2 = "the other player knowing the location of their ships.";

				changeBottomText(bottomText1, bottomText2);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			waitForRules = true;
			while (waitForRules)
			{
				bottomText1 = "Once both players have placed their ships,";
				bottomText2 = "both players will decide who gets to go first.";

				changeBottomText(bottomText1, bottomText2);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			waitForRules = true;
			while (waitForRules)
			{
				bottomText1 = "One player will then select a position to attack.";
				bottomText2 = "If the position selected is where the other player's";

				changeBottomText(bottomText1, bottomText2);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			waitForRules = true;
			while (waitForRules)
			{
				bottomText1 = "ship, then it will count as a HIT. Otherwise, it will";
				bottomText2 = "count as a MISS. If all positions of a ship have been";

				changeBottomText(bottomText1, bottomText2);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			waitForRules = true;
			while (waitForRules)
			{
				bottomText1 = "HIT, then it will be known to both players that the";
				bottomText2 = "specific ship has been SUNK. When all ships have been";

				changeBottomText(bottomText1, bottomText2);
				displayImage();
				inputMode();
				if (keyPress == ENTER)
				{
					waitForRules = false;		//set the flag off
				}
			}
			bottomText1 = "SUNK, then the other player will be victorious.";
			bottomText2 = "Would you like to read the rules again? Y / N";
			topText = "Press Y for yes or N for no to continue";

			changeBottomText(bottomText1, bottomText2);
			changeTopText(topText);
			displayImage();
		}
		else if (keyPress == 'n')
		{
			waitForP1 = false;		//set the flag off
		}
	}
	placeMode(PLAYER1);
	updateTime();
	recordFile << endl << timeStamp << " Player 1 has placed their ships\n\n";

	if (vsPlr)
	{
		updateMap(BLANK);
		waitForRules = true;
		while (waitForRules)
		{
			topText = "Player 2 Setup";
			bottomText1 = "It is now time for player 2 to set up their ships";
			bottomText2 = "Player 2, press ENTER to start setting up your ships";

			changeBottomText(bottomText1, bottomText2);
			changeTopText(topText);
			displayImage();
			inputMode();
			if (keyPress == ENTER)
			{
				waitForRules = false;		//set the flag off
			}
		}
		placeMode(PLAYER2);
		updateTime();
		recordFile << endl << timeStamp << " Player 2 has placed their ships\n\n";
	}

	return;
}

void battleship::setupComputer(void)
{
	placeMode(COMPUTER);	//just need to run one method for the computer
	updateTime();
	recordFile << endl << timeStamp << " Computer has placed their ships\n\n";
	return;
}

void battleship::whoGoesFirst(int secondPerson)	//just need to argument the second person
{
	string bottomText1,
		bottomText2,
		topText1;

	bool waitForInput = true;

	if (secondPerson == COMPUTER)
	{
		bottomText1 = "Press 1 if you want to go first, press 2 for random,";
		bottomText2 = "or press 3 if you want the computer to go first.";
	}
	else if (secondPerson == PLAYER2)
	{
		bottomText1 = "Press 1 if you want player 1 to go first, press 2 for";
		bottomText2 = "random, or press 3 if you want player 2 to go first.";
	}

	topText1 = "Who is going first?";
	changeTopText(topText1);
	changeBottomText(bottomText1, bottomText2);
	displayImage();

	while (waitForInput)
	{
		inputMode();
		if (keyPress == '1')
		{
			currentTurn = PLAYER1;
			waitForInput = false;
			updateTime();
			recordFile << endl << timeStamp << " Decided player 1 is going first\n\n";
		}
		else if (keyPress == '2')
		{
			int coinFlip = ((rand() % 3));			//flip a coin
//			randVal = ((rand() % (maxVal - minVal + 1)) + minVal);	//coinflip formula just in case i need it later
			if (coinFlip == 1)
			{
				currentTurn = PLAYER1;
				waitForInput = false;
				updateTime();
				recordFile << endl << timeStamp << " Decided player 1 is going first through a coin flip\n\n";
			}
			else if (coinFlip == 2)
			{
				if (secondPerson == COMPUTER)
				{
					currentTurn = COMPUTER;
					waitForInput = false;
					updateTime();
					recordFile << endl << timeStamp << " Decided computer is going first through a coin flip\n\n";
				}
				else if (secondPerson == PLAYER2)
				{
					currentTurn = PLAYER2;
					waitForInput = false;
					updateTime();
					recordFile << endl << timeStamp << " Decided player 2 is going first through a coin flip\n\n";
				}
			}
		}
		else if (keyPress == '3')
		{
			if (secondPerson == COMPUTER)
			{
				currentTurn = COMPUTER;
				waitForInput = false;
				updateTime();
				recordFile << endl << timeStamp << " Decided computer is going first\n\n";
			}
			else if (secondPerson == PLAYER2)
			{
				currentTurn = PLAYER2;
				waitForInput = false;
				updateTime();
				recordFile << endl << timeStamp << " Decided player 2 is going first\n\n";
			}
		}
	}

	if (currentTurn == PLAYER1)
	{
		topText1 =    "Player 1 is going first";
		bottomText1 = "Get Ready for Battleship!!!";
		bottomText2 = "Press ENTER to start your turn, player 1!";
	}
	else if (currentTurn == COMPUTER)
	{
		topText1 = "Computer is going first";
		bottomText1 = "Get Ready for Battleship!!!";
		bottomText2 = "Press ENTER to start the game";
	}
	else if (currentTurn == PLAYER2)
	{
		topText1 = "Player 2 is going first";
		bottomText1 = "Get Ready for Battleship!!!";
		bottomText2 = "Press ENTER to start your turn, player 2!";
	}

	changeTopText(topText1);
	changeBottomText(bottomText1, bottomText2);
	displayImage();

	waitForInput = true;
	while (waitForInput)
	{
		inputMode();
		if (keyPress == ENTER)
		{
			waitForInput = false;		//set the flag off
		}
	}

	return;
}

void battleship::checkForVictory()
{
	string bottomMessage1,
		bottomMessage2,
		topMessage;

	bool waitForInput = true,
		mapView = true;

	int timesFound = 0;

	if (vsCom)
	{
		timesFound = 0;
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (p1Array[wIndex][hIndex] == PATROL || p1Array[wIndex][hIndex] == DESTROYER ||	//if there is a ship present
					p1Array[wIndex][hIndex] == SUB || p1Array[wIndex][hIndex] == BATTLESHIP || 
					p1Array[wIndex][hIndex] == CARRIER)
				{
					timesFound++;
				}
			}
		}
		if (timesFound < 1)			//if no ships are found...
		{
			if (trackNum != 4)		//as long as the music isnt muted...
			{
				sndPlaySound("Halo4 End.wav", SND_ASYNC);		//plays defeat theme -not on loop
			}
			winner = COMPUTER;
			victory = true;
			bottomMessage1 = "The computer has sunk all of your ships...";		
			bottomMessage2 = "Press ENTER to continue or press M to view computer's map";
			topMessage = "DEFEAT::::::Computer is victorious:::::::DEFEAT";
			updateTime();
			recordFile << endl << timeStamp << " " << topMessage << "\n\n";				//add victory to the record 
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			waitForInput = true;
			while (waitForInput)
			{
				inputMode();
				if (keyPress == ENTER)
				{
					waitForInput = false;		//set the flag off
					updateTime();
					recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
				}
				else if (keyPress == 'm')
				{

					bottomMessage1 = "Now viewing player 1's map";
					bottomMessage2 = "Press M to go to computer's map or ENTER to continue";
					topMessage = "Player 1's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					updateMap(PLAYER1);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
						else if (keyPress == ENTER)
						{
							waitForInput = false;		//set the flag off
							mapView = false;
							updateTime();
							recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
						}
					}
					updateMap(COMPUTER);
					bottomMessage1 = "Now viewing computer's map";
					bottomMessage2 = "Press M to go to player 1's map or ENTER to continue";
					topMessage = "Computer's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					displayImage();
				}
			}
		}

		timesFound = 0;
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (comArray[wIndex][hIndex] == PATROL || comArray[wIndex][hIndex] == DESTROYER ||	//if there is a ship present
					comArray[wIndex][hIndex] == SUB || comArray[wIndex][hIndex] == BATTLESHIP ||
					comArray[wIndex][hIndex] == CARRIER)
				{
					timesFound++;
				}
			}
		}
		if (timesFound < 1)			//if no ships are found...
		{
			if (trackNum != 4)		//as long as the music isnt muted...
			{
				sndPlaySound("FF7 Victory.wav", SND_ASYNC);		//plays victory theme -not on loop
			}
			winner = PLAYER1;
			victory = true;
			bottomMessage1 = "You have sunk all of the computer's ships!!!";
			bottomMessage2 = "Press ENTER to continue or press M to view opponent's map";
			topMessage = "VICTORY:::::: PLAYER 1 :::::::VICTORY";
			updateTime();
			recordFile << endl << timeStamp << " " << topMessage << "\n\n";				//add victory to the record 
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			waitForInput = true;
			while (waitForInput)
			{
				inputMode();
				if (keyPress == ENTER)
				{
					waitForInput = false;		//set the flag off
					updateTime();
					recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
				}
				else if (keyPress == 'm')
				{

					bottomMessage1 = "Now viewing player 1's map";
					bottomMessage2 = "Press M to go to computer's map or ENTER to continue";
					topMessage = "Player 1's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					updateMap(PLAYER1);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
						else if (keyPress == ENTER)
						{
							waitForInput = false;		//set the flag off
							mapView = false;
							updateTime();
							recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
						}
					}
					updateMap(COMPUTER);
					bottomMessage1 = "Now viewing computer's map";
					bottomMessage2 = "Press M to go to player 1's map or ENTER to continue";
					topMessage = "Computer's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					displayImage();
				}
			}
		}
	}
	else if (vsPlr)
	{
		timesFound = 0;
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (p1Array[wIndex][hIndex] == PATROL || p1Array[wIndex][hIndex] == DESTROYER ||	//if there is a ship present
					p1Array[wIndex][hIndex] == SUB || p1Array[wIndex][hIndex] == BATTLESHIP ||
					p1Array[wIndex][hIndex] == CARRIER)
				{
					timesFound++;
				}
			}
		}
		if (timesFound < 1)			//if no ships are found...
		{
			if (trackNum != 4)		//as long as the music isnt muted...
			{
				sndPlaySound("FF7 Victory.wav", SND_ASYNC);		//plays victory theme -not on loop
			}
			winner = PLAYER2;
			victory = true;
			bottomMessage1 = "Player 2 has sunk all of Player 1's ships!!!!";
			bottomMessage2 = "Press ENTER to continue or press M to view opponent's map";
			topMessage = "VICTORY:::::: PLAYER 2 :::::::VICTORY";
			updateTime();
			recordFile << endl << timeStamp << " " << topMessage << "\n\n";				//add victory to the record 
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			waitForInput = true;
			while (waitForInput)
			{
				inputMode();
				if (keyPress == ENTER)
				{
					waitForInput = false;		//set the flag off
					updateTime();
					recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
				}
				else if (keyPress == 'm')
				{

					bottomMessage1 = "Now viewing player 1's map";
					bottomMessage2 = "Press M to go to computer's map or ENTER to continue";
					topMessage = "Player 1's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					updateMap(PLAYER1);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
						else if (keyPress == ENTER)
						{
							waitForInput = false;		//set the flag off
							mapView = false;
							updateTime();
							recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
						}
					}
					updateMap(PLAYER2);
					bottomMessage1 = "Now viewing player 2's map";
					bottomMessage2 = "Press M to go to player 1's map or ENTER to continue";
					topMessage = "Player 2's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					displayImage();
				}
			}
		}

		timesFound = 0;
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (p2Array[wIndex][hIndex] == PATROL || p2Array[wIndex][hIndex] == DESTROYER ||	//if there is a ship present
					p2Array[wIndex][hIndex] == SUB || p2Array[wIndex][hIndex] == BATTLESHIP ||
					p2Array[wIndex][hIndex] == CARRIER)
				{
					timesFound++;
				}
			}
		}
		if (timesFound < 1)			//if no ships are found...
		{
			if (trackNum != 4)		//as long as the music isnt muted...
			{
				sndPlaySound("FF7 Victory.wav", SND_ASYNC);		//plays victory theme -not on loop
			}
			winner = PLAYER1;
			victory = true;
			bottomMessage1 = "Player 1 has sunk all of Player 2's ships!!!!";
			bottomMessage2 = "Press ENTER to continue or press M to view opponent's map";
			topMessage = "VICTORY:::::: PLAYER 1 :::::::VICTORY";
			updateTime();
			recordFile << endl << timeStamp << " " << topMessage << "\n\n";				//add victory to the record 
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			waitForInput = true;
			while (waitForInput)
			{
				inputMode();
				if (keyPress == ENTER)
				{
					waitForInput = false;		//set the flag off
					updateTime();
					recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
				}
				else if (keyPress == 'm')
				{

					bottomMessage1 = "Now viewing player 1's map";
					bottomMessage2 = "Press M to go to computer's map or ENTER to continue";
					topMessage = "Player 1's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					updateMap(PLAYER1);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
						else if (keyPress == ENTER)
						{
							waitForInput = false;		//set the flag off
							mapView = false;
							updateTime();
							recordFile << endl << timeStamp << " End Game\n\n";				//add to the record 
						}
					}
					updateMap(PLAYER2);
					bottomMessage1 = "Now viewing player 2's map";
					bottomMessage2 = "Press M to go to player 1's map or ENTER to continue";
					topMessage = "Player 2's Map";
					changeTopText(topMessage);
					changeBottomText(bottomMessage1, bottomMessage2);
					displayImage();
				}
			}
		}
	}

//	playerFile.close();					when it gets to the point where I will end the record keeping
	return;
}

void battleship::changeTopText(string text)		//Be sure to be mindful of the spaces
{

	clearTopText();

	int stringLength = text.length(),			//determine string length
		evenOrOdd = 0,							//variable to determine if even or odd
		startingLocation = 0,					//variable for starting location of string
		stringIndex = 0;

	if (stringLength > 57)					//ensure it does not go above the size of the text box
	{
		cout << "Error: String is too long to add to the top."
			<< "\nProgram will now close.\n\n\n";
		system("pause");
		exit(0);
	}

	// "|-----------------------hello world------------------------|"
	//starts at 23 ends at 34 total of 58 length of string is 11
	//start at (29 - ((stringLength / 2) + 1 )) if odd
	//start at (29 - (stringLength /2)) if even
	//keep in mind that the boarders add an extra 1 to the display subscript

	//			topMessage = "Press enter to place your carrier";



	evenOrOdd = stringLength % 2;								//see if the length of the string is even or odd

	if (evenOrOdd == 1)										//if it is odd...
	{
		startingLocation = (29 - ((stringLength / 2) + 1));					//starting location for the top message
	}
	else if (evenOrOdd == 0)									//if it is even...
	{
		startingLocation = (29 - (stringLength / 2));							//starting location for the bottom message
	}

	char *charArray = nullptr;
	charArray = new char[stringLength];					//create dynamic array for moving the chars

	text.copy(charArray,stringLength);					//copy the string to the char array

	for (int width = 1; width < DISP_W; width++)		//a for loop starts at the first subscript
	{
		if (width >= (startingLocation + 1) && width <= (stringLength + startingLocation)) //if the current index is past the starting location
		{																				//and before it is supposed to end
			display[width][1] = charArray[stringIndex];								//copy the char array to the display
			stringIndex++;															//add 1 to the index
		}
	}

	delete[] charArray;

	return;
}

void battleship::clearTopText(void)		
{
	string blankText = "                                                          ";			//a string of a blank line

	char *charArray = nullptr;
	charArray = new char[58];					//create dynamic array for moving the chars

	blankText.copy(charArray, 58);						//copy the string to a char array

	for (int width = 1; width < 58; width++)
	{
		display[width][1] = charArray[width - 1];
	}

	delete[] charArray;

	return;
}

void battleship::changeBottomText(string line1, string line2)		//line 2 is not required to pass it has a blank default argument
{

	clearBottomText();					//clear text before adding more

	int stringLength1 = line1.length();			//determine string length
	int stringLength2 = line2.length(),			//determine string length
		evenOrOdd1 = 0,
		evenOrOdd2 = 0,
		startingLocation1 = 0,
		startingLocation2 = 0,
		stringIndex = 0;



	if (stringLength1 > 57 || stringLength2 > 57)					//ensure it does not go above the size of the text box
	{
		cout << "Error:String of line1 or line2 is too long to add to the bottom."
			<< "\nProgram will now close.\n\n\n";
		system("pause");
		exit(0);
	}

	char *charArray1 = nullptr;
	charArray1 = new char[stringLength1];					//create dynamic array for moving the chars
	char *charArray2 = nullptr;
	charArray2 = new char[stringLength2];

	line1.copy(charArray1, stringLength1);					//copy line1 to the char array1
	line2.copy(charArray2, stringLength2);					//copy line2 to the char array2

	// "|-----------------------hello world------------------------|"
	//starts at 23 ends at 34 total of 58 length of string is 11
	//start at (29 - ((stringLength / 2) + 1 )) if odd
	//start at (29 - (stringLength /2)) if even
	//keep in mind that the boarders add an extra 1 to the display subscript
	
	evenOrOdd1 = stringLength1 % 2;								//see if the length of the string is even or odd

	if (evenOrOdd1 == 1)										//if it is odd...
	{
		startingLocation1 = (29 - ((stringLength1 / 2) + 1));					//starting location for the top message
	}
	else if (evenOrOdd1 == 0)									//if it is even...
	{
		startingLocation1 = (29 - (stringLength1 / 2));							//starting location for the bottom message
	}

	for (int width = 1; width < DISP_W; width++)		//a for loop starts at the first subscript
	{
		if (width >= (startingLocation1 + 1) && width <= (stringLength1 + startingLocation1)) //if the current index is past the starting location
		{																				//and before it is supposed to end
			display[width][27] = charArray1[stringIndex];								//copy the char array to the display
			stringIndex++;															//add 1 to the index
		}
	}

	stringIndex = 0;

	evenOrOdd2 = stringLength2 % 2;								//see if the length of the string is even or odd

	if (evenOrOdd2 == 1)										//if it is odd...
	{
		startingLocation2 = (29 - ((stringLength2 / 2) + 1));					//starting location for the top message
	}
	else if (evenOrOdd2 == 0)									//if it is even...
	{
		startingLocation2 = (29 - (stringLength2 / 2));							//starting location for the bottom message
	}

	for (int width = 1; width < DISP_W; width++)		//a for loop starts at the first subscript
	{
		if (width >= (startingLocation2 + 1) && width <= (stringLength2 + startingLocation2)) //if the current index is past the starting location
		{																				//and before it is supposed to end
			display[width][28] = charArray2[stringIndex];								//copy the char array to the display
			stringIndex++;															//add 1 to the index
		}
	}

	delete[] charArray1;						//Delete the arrays
	delete[] charArray2;

	return;
}

void battleship::clearBottomText(void)
{
	string blankText = "                                                          ";			//a string of a blank line

	char *charArray = nullptr;
	charArray = new char[58];					//create dynamic array for moving the chars
				
	blankText.copy(charArray, 58);						//copy the blank string to a char array

	for (int width = 1; width < 58; width++)
	{
		display[width][27] = charArray[width - 1];			//copy the blank line to both lines
		display[width][28] = charArray[width - 1];
	}

	delete[] charArray;						//Delete the array

	return;
}

void battleship::addToInfoBox(string text)
{
	char lineCopy[12];

	int stringLength = text.length(),			//determine string length
		evenOrOdd = 0,							//variable to determine if even or odd
		startingLocation = 0,					//variable for starting location of string
		stringIndex = 0,
		line = 0;

	if (stringLength > 13)					//ensure it does not go above the size of the info box
	{
		cout << "Error: String is too long to add to the info Box."
			<< "\nProgram will now close.\n\n\n";
		system("pause");
		exit(0);
	}

	for (line = 19; line > 0; line--)
	{
		for (int width = 1; width < 13; width++)		//a for loop starts at the first subscript
		{
			lineCopy[width - 1] = display[width][line + 5];				//copies line above the one we are focusing on
		}
		if (line != 19)										//as long as the line is not set to 19
		{
			for (int idxW = 1; idxW < 13; idxW++)		//a for loop starts at the first subscript
			{
				display[idxW][line + 6] = lineCopy[idxW - 1];				//pastes copied line to the one below 
			}
			if (line == 0)									//if the line if the top line...
			{
				for (int wid = 1; wid < 13; wid++)		//a for loop starts at the first subscript
				{
					display[wid][line + 6] = ' ';				//pastes blank characters 
				}
			}
		}
	}



	// "|-hello world|"
	//starts at 1 ends at 12 total of 12 length of string is 11
	//start at (6 - ((stringLength / 2) + 1 )) if odd
	//start at (6 - (stringLength /2)) if even
	//keep in mind that the boarders add an extra 1 to the display subscript

	//			topMessage = "Press enter to place your carrier";

	evenOrOdd = stringLength % 2;								//see if the length of the string is even or odd

	if (evenOrOdd == 1)										//if it is odd...
	{
		startingLocation = (6 - ((stringLength / 2) + 1));					//starting location for the line that is about to be inserted 
	}
	else if (evenOrOdd == 0)									//if it is even...
	{
		startingLocation = (6 - (stringLength / 2));						//starting location for the line that is about to be inserted
	}

	char *charArray = nullptr;
	charArray = new char[stringLength];					//create dynamic array for moving the chars

	text.copy(charArray, stringLength);					//copy the string to the char array

	for (int width = 1; width < 13; width++)		//a for loop starts at the first subscript
	{
		display[width][6] = ' ';											//wipe the line before writing to it
	}

	for (int width = 1; width < 13; width++)		//a for loop starts at the first subscript
	{
		if (width >= (startingLocation + 1) && width <= (stringLength + startingLocation)) //if the current index is past the starting location
		{																				//and before it is supposed to end
			display[width][6] = charArray[stringIndex];								//copy the char array to the display
			stringIndex++;															//add 1 to the index
		}
	}

	delete[] charArray;

	return;
}

void battleship::navMode(void)
{
	int wIdx = 0,			//create variables for width and height index
		hIdx = 0;

	bool waitForP1 = true;

	while (waitForP1)
	{
		inputMode();
		if (keyPress == LEFT)
		{
			if (wIdx > 0)
			{
				wIdx--;
			}
		}
		else if (keyPress == UP)
		{
			if (hIdx > 0)
			{
				hIdx--;
			}
		}
		else if (keyPress == RIGHT)
		{
			if (wIdx < 9)
			{
				wIdx++;
			}
		}
		else if (keyPress == DOWN)
		{
			if (hIdx < 9)
			{
				hIdx++;
			}
		}
		else if (keyPress == ENTER)
		{

		}
		highlightBoard(wIdx,hIdx);
	}


	return;
}

void battleship::highlightBoard(int wIdx, int hIdx)
{
	
	char holder = 0;				//to hold the true value of the space in the display

	int boardW = 0,
		boardH = 0;

	boardH = (6 + (hIdx * 2));				//find these places on the display
	boardW = (20 + (wIdx * 4));

	holder = display[boardW][boardH];

	display[boardW][boardH] = '#';
	displayImage();
	display[boardW][boardH] = holder;

	return;
}

void battleship::placeMode(int selection)
{
	string topMessage,
		bottomMessage1,
		bottomMessage2;

	int shipW = 0,			//create variables for ship width and ship height
		shipH = 0;

	bool placingShips = true;
	bool waitingForAnswers = true;

	while (placingShips)
	{

		//place the carrier//
		shipW = 5;
		shipH = 1;

		if (selection != COMPUTER)						//if it is not a computer
		{
			bottomMessage1 = "Place your carrier. Use the arrow keys to navigate";		//placement instructions
			bottomMessage2 = "Press R to rotate your ship vertically or horizontally";
			topMessage = "press ENTER to place your carrier";
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, " + topMessage;
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, " + topMessage;
			}
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			playerPlaceShip(shipW, shipH, selection, CARRIER);	//human ship placement
		}
		else if (selection == COMPUTER)					//if it is a computer
		{
			comPlaceShip(shipW, shipH, CARRIER);					//computer ship placemement
		}

		//place the battleship//
		shipW = 4;
		shipH = 1;

		if (selection != COMPUTER)						//if it is not a computer
		{
			bottomMessage1 = "Place your battleship. Use the arrow keys to navigate";		//placement instructions
			bottomMessage2 = "Press R to rotate your ship vertically or horizontally";
			topMessage = "press ENTER to place your battleship";
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, " + topMessage;
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, " + topMessage;
			}
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			playerPlaceShip(shipW, shipH, selection, BATTLESHIP);	//human ship placement
		}
		else if (selection == COMPUTER)					//if it is a computer
		{
			comPlaceShip(shipW, shipH, BATTLESHIP);					//computer ship placemement
		}

		//place the submarine//
		shipW = 3;
		shipH = 1;

		if (selection != COMPUTER)						//if it is not a computer
		{
			bottomMessage1 = "Place your submarine. Use the arrow keys to navigate";		//placement instructions
			bottomMessage2 = "Press R to rotate your ship vertically or horizontally";
			topMessage = "press ENTER to place your submarine";
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, " + topMessage;
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, " + topMessage;
			}
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			playerPlaceShip(shipW, shipH, selection, SUB);	//human ship placement
		}
		else if (selection == COMPUTER)					//if it is a computer
		{
			comPlaceShip(shipW, shipH, SUB);					//computer ship placemement
		}

		//place the destroyer//
		shipW = 3;
		shipH = 1;

		if (selection != COMPUTER)						//if it is not a computer
		{
			bottomMessage1 = "Place your destroyer. Use the arrow keys to navigate";		//placement instructions
			bottomMessage2 = "Press R to rotate your ship vertically or horizontally";
			topMessage = "press ENTER to place your destroyer";
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, " + topMessage;
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, " + topMessage;
			}
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			playerPlaceShip(shipW, shipH, selection, DESTROYER);	//human ship placement
		}
		else if (selection == COMPUTER)					//if it is a computer
		{
			comPlaceShip(shipW, shipH, DESTROYER);					//computer ship placemement
		}

		//place the patrol boat//
		shipW = 2;
		shipH = 1;

		if (selection != COMPUTER)						//if it is not a computer
		{
			bottomMessage1 = "Place your patrol boat. Use the arrow keys to navigate";		//placement instructions
			bottomMessage2 = "Press R to rotate your ship vertically or horizontally";
			topMessage = "press ENTER to place your patrol boat";
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, " + topMessage;
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, " + topMessage;
			}
			changeTopText(topMessage);
			changeBottomText(bottomMessage1, bottomMessage2);
			displayImage();
			playerPlaceShip(shipW, shipH, selection, PATROL);	//human ship placement
		}
		else if (selection == COMPUTER)					//if it is a computer
		{
			comPlaceShip(shipW, shipH, PATROL);					//computer ship placemement
		}

		if (selection != COMPUTER)			//if it is a human, load and display messages, otherwise finish placing ships
		{
			if (selection == PLAYER1)
			{
				topMessage = "Player 1, would you like to continue?";
			}
			else if (selection == PLAYER2)
			{
				topMessage = "Player 2, would you like to continue?";
			}
			changeTopText(topMessage);
			bottomMessage1 = "Press Y to continue or press N to re-place your ships";
			changeBottomText(bottomMessage1);
			displayImage();
			waitingForAnswers = true;			//reset the waiting for answers flag

			while (waitingForAnswers)
			{
				inputMode();
				if (keyPress == 'y')
				{
					placingShips = false;
					waitingForAnswers = false;
				}
				else if (keyPress == 'n')
				{
					placingShips = true;
					waitingForAnswers = false;
					resetBoard(selection);				//reset game board and start over
					updateMap(selection);				//ensure we are showing the updated map
				}
			}
		}
		else if (selection == COMPUTER)
		{
			placingShips = false;
		}
	}
	return;
}

void battleship::targetMode(int selection)
{
	string botTxt1,
		botTxt2,
		boxText,
		topMsg;

	int wIdx = 0,			//create variables for width and height index
		hIdx = 0;

	bool waitForPlayer = true,
		mapView = true,
		waiting = true;

	if (vsCom)
	{
		botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
		botTxt2 = "a location, or press M to view your game board.";
		topMsg = "Target Mode";
		changeTopText(topMsg);
		changeBottomText(botTxt1, botTxt2);
		updateMap(PLAYER1ATT);
		displayImage();
		highlightBoard(wIdx, hIdx);

		while (waitForPlayer)
		{
			inputMode();
			if (keyPress == LEFT)
			{
				if (wIdx > 0)
				{
					wIdx--;
				}
			}
			else if (keyPress == UP)
			{
				if (hIdx > 0)
				{
					hIdx--;
				}
			}
			else if (keyPress == RIGHT)
			{
				if (wIdx < 9)
				{
					wIdx++;
				}
			}
			else if (keyPress == DOWN)
			{
				if (hIdx < 9)
				{
					hIdx++;
				}
			}
			else if (keyPress == ENTER)
			{
				if (comArray[wIdx][hIdx] == PATROL || comArray[wIdx][hIdx] == DESTROYER ||		//if a ship is present
					comArray[wIdx][hIdx] == SUB || comArray[wIdx][hIdx] == BATTLESHIP ||
					comArray[wIdx][hIdx] == CARRIER)
				{
					checkForSink(wIdx, hIdx, COMPUTER);
					comArray[wIdx][hIdx] = HIT;
					p1atkArray[wIdx][hIdx] = HIT;
					attackW = wIdx;			//Add coordinates for the attempted strike
					attackH = hIdx;

					if (shipSunk == NOTHING)
					{
						//designed to look like "COM >> A2 >> HIT
						boxText = "PLR1 HIT ";
						boxText += vCord(attackH);
						boxText += hCord(attackW);
						addToInfoBox(boxText);
						topMsg = "PLAYER 1 >> ";
						topMsg += vCord(attackH);
						topMsg += hCord(attackW);
						topMsg += " >> HIT";
						botTxt1 = "You have hit the computer at ";
						botTxt1 += vCord(attackH);
						botTxt1 += hCord(attackW);
						botTxt2 = "Press ENTER to start the computer's turn";
					}
					else if (shipSunk != NOTHING)
					{
						boxText = "SUNK ";
						topMsg = "PLAYER 1 >> ";
						topMsg += vCord(attackH);
						topMsg += hCord(attackW);
						topMsg += " >> SINK >> ";
						botTxt1 = "You have sunk the computer's ";
						if (shipSunk == PATROL)
						{
							boxText += "P-BOAT";
							topMsg += "PATROL BOAT";
							botTxt1 += "patrol boat at ";
						}
						else if (shipSunk == DESTROYER)
						{
							boxText += "DESTR";
							topMsg += "DESTROYER";
							botTxt1 += "destroyer at ";
						}
						else if (shipSunk == SUB)
						{
							boxText += "SUB";
							topMsg += "SUBMARINE";
							botTxt1 += "submarine at ";
						}
						else if (shipSunk == BATTLESHIP)
						{
							boxText += "BATTLE";
							topMsg += "BATTLESHIP";
							botTxt1 += "battleship at ";
						}
						else if (shipSunk == CARRIER)
						{
							boxText += "CARIR";
							topMsg += "AIRCRAFT CARRIER";
							botTxt1 += "aircraft carrier at ";
						}
						addToInfoBox(boxText);
						botTxt1 += vCord(attackH);
						botTxt1 += hCord(attackW);
						boxText = "PLR1 SINK ";
						boxText += vCord(attackH);
						boxText += hCord(attackW);
						addToInfoBox(boxText);
						botTxt2 = "Press ENTER to start the computer's turn";
					}
					updateTime();
					recordFile << timeStamp << " " << topMsg << "\n";				//update attack in the records
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					updateMap(PLAYER1ATT);
					displayImage();
					waiting = true;
					while (waiting)
					{
						inputMode();
						if (keyPress == ENTER)
						{
							waiting = false;
							waitForPlayer = false;
						}
					}
				}
				else if (comArray[wIdx][hIdx] == NOTHING)
				{
					comArray[wIdx][hIdx] = MISS;
					p1atkArray[wIdx][hIdx] = MISS;
					attackW = wIdx;			//Add coordinates for the attempted strike
					attackH = hIdx;

					//designed to look like "COM >> A2 >> HIT
					boxText = "PLR1 MISS ";
					boxText += vCord(attackH);
					boxText += hCord(attackW);
					addToInfoBox(boxText);
					topMsg = "PLAYER 1 >> ";
					topMsg += vCord(attackH);
					topMsg += hCord(attackW);
					topMsg += " >> MISS";
					botTxt1 = "You tried to hit the computer at ";
					botTxt1 += vCord(attackH);
					botTxt1 += hCord(attackW);
					botTxt2 = "Press ENTER to start the computer's turn";
					updateTime();
					recordFile << timeStamp << " " << topMsg << "\n";				//update for the records
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					updateMap(PLAYER1ATT);
					displayImage();
					waiting = true;
					while (waiting)
					{
						inputMode();
						if (keyPress == ENTER)
						{
							waiting = false;
							waitForPlayer = false;
						}
					}
				}
				else if (comArray[wIdx][hIdx] == HIT || comArray[wIdx][hIdx] == SINK ||	
						 comArray[wIdx][hIdx] == MISS)                     	     	//if it is a location that has already been hit
				{
					topMsg = "Press ENTER to continue";
					botTxt1 = "You have already selected this location to attack";
					botTxt2 = "Please pick another location";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					displayImage();
					waiting = true;
					while (waiting)
					{
						inputMode();
						if (keyPress == ENTER)
						{
							waiting = false;
						}
					}
					botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
					botTxt2 = "a location, or press M to view your game board.";
					topMsg = "Target Mode";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					displayImage();
					
				}

			}
			else if (keyPress == 'm')
			{
				botTxt1 = "Now viewing your own game board";		
				botTxt2 = "Press M to go back to the attack board";
				topMsg = "View Mode";
				changeTopText(topMsg);
				changeBottomText(botTxt1, botTxt2);
				updateMap(PLAYER1);
				displayImage();
				mapView = true;
				while (mapView)
				{
					inputMode();
					if (keyPress == 'm')
					{
						mapView = false;
					}
				}
				updateMap(PLAYER1ATT);
				botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
				botTxt2 = "a location, or press M to view your game board.";
				topMsg = "Target Mode";
				changeTopText(topMsg);
				changeBottomText(botTxt1, botTxt2);
				displayImage();
			}
			highlightBoard(wIdx, hIdx);
		}
	}
	else if (vsPlr)
	{
		if (selection == PLAYER1)
		{
			botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
			botTxt2 = "a location, or press M to view your game board.";
			topMsg = "Player 1 Target Mode";
			changeTopText(topMsg);
			changeBottomText(botTxt1, botTxt2);
			updateMap(PLAYER1ATT);
			displayImage();
			highlightBoard(wIdx, hIdx);
			while (waitForPlayer)
			{
				inputMode();
				if (keyPress == LEFT)
				{
					if (wIdx > 0)
					{
						wIdx--;
					}
				}
				else if (keyPress == UP)
				{
					if (hIdx > 0)
					{
						hIdx--;
					}
				}
				else if (keyPress == RIGHT)
				{
					if (wIdx < 9)
					{
						wIdx++;
					}
				}
				else if (keyPress == DOWN)
				{
					if (hIdx < 9)
					{
						hIdx++;
					}
				}
				else if (keyPress == ENTER)
				{
					if (p2Array[wIdx][hIdx] == PATROL || p2Array[wIdx][hIdx] == DESTROYER ||		//if a ship is present
						p2Array[wIdx][hIdx] == SUB || p2Array[wIdx][hIdx] == BATTLESHIP ||
						p2Array[wIdx][hIdx] == CARRIER)
					{
						checkForSink(wIdx, hIdx, PLAYER2);
						p2Array[wIdx][hIdx] = HIT;
						p1atkArray[wIdx][hIdx] = HIT;
						attackW = wIdx;			//Add coordinates for the attempted strike
						attackH = hIdx;

						if (shipSunk == NOTHING)
						{
							//designed to look like "COM >> A2 >> HIT
							boxText = "PLR1 HIT ";
							boxText += vCord(attackH);
							boxText += hCord(attackW);
							addToInfoBox(boxText);
							topMsg = "PLAYER 1 >> ";
							topMsg += vCord(attackH);
							topMsg += hCord(attackW);
							topMsg += " >> HIT";
							botTxt1 = "You have hit player 2 at ";
							botTxt1 += vCord(attackH);
							botTxt1 += hCord(attackW);
							botTxt2 = "Press ENTER to start player 2's turn";
						}
						else if (shipSunk != NOTHING)
						{
							boxText = "SUNK ";
							topMsg = "PLAYER 1 >> ";
							topMsg += vCord(attackH);
							topMsg += hCord(attackW);
							topMsg += " >> SINK >> ";
							botTxt1 = "You have sunk player 2's ";
							if (shipSunk == PATROL)
							{
								boxText += "P-BOAT";
								topMsg += "PATROL BOAT";
								botTxt1 += "patrol boat at ";
							}
							else if (shipSunk == DESTROYER)
							{
								boxText += "DESTR";
								topMsg += "DESTROYER";
								botTxt1 += "destroyer at ";
							}
							else if (shipSunk == SUB)
							{
								boxText += "SUB";
								topMsg += "SUBMARINE";
								botTxt1 += "submarine at ";
							}
							else if (shipSunk == BATTLESHIP)
							{
								boxText += "BATTLE";
								topMsg += "BATTLESHIP";
								botTxt1 += "battleship at ";
							}
							else if (shipSunk == CARRIER)
							{
								boxText += "CARIR";
								topMsg += "AIRCRAFT CARRIER";
								botTxt1 += "aircraft carrier at ";
							}
								addToInfoBox(boxText);
								botTxt1 += vCord(attackH);
								botTxt1 += hCord(attackW);
								boxText = "PLR1 SINK ";
								boxText += vCord(attackH);
								boxText += hCord(attackW);
								addToInfoBox(boxText);
								botTxt2 = "Press ENTER to start player 2's turn";

							}
							updateTime();
							recordFile << timeStamp << " " << topMsg << "\n";				//update attack in the records
							changeTopText(topMsg);
							changeBottomText(botTxt1, botTxt2);
							updateMap(PLAYER1ATT);
							displayImage();
							waiting = true;
							while (waiting)
							{
								inputMode();
								if (keyPress == ENTER)
								{
									waiting = false;
									waitForPlayer = false;
								}
							}


					}
					else if (p2Array[wIdx][hIdx] == NOTHING)
					{
						p2Array[wIdx][hIdx] = MISS;
						p1atkArray[wIdx][hIdx] = MISS;
						attackW = wIdx;			//Add coordinates for the attempted strike
						attackH = hIdx;

						//designed to look like "COM >> A2 >> HIT
						boxText = "PLR1 MISS ";
						boxText += vCord(attackH);
						boxText += hCord(attackW);
						addToInfoBox(boxText);
						topMsg = "PLAYER 1 >> ";
						topMsg += vCord(attackH);
						topMsg += hCord(attackW);
						topMsg += " >> MISS";
						botTxt1 = "You tried to hit player 2 at ";
						botTxt1 += vCord(attackH);
						botTxt1 += hCord(attackW);
						botTxt2 = "Press ENTER to start player 2's turn";
						updateTime();
						recordFile << timeStamp << " " << topMsg << "\n";				//update for the records
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						updateMap(PLAYER1ATT);
						displayImage();
						waiting = true;
						while (waiting)
						{
							inputMode();
							if (keyPress == ENTER)
							{
								waiting = false;
								waitForPlayer = false;
							}
						}
					}
					else if (p2Array[wIdx][hIdx] == HIT || p2Array[wIdx][hIdx] == SINK ||
						p2Array[wIdx][hIdx] == MISS)                     	     	//if it is a location that has already been hit
					{

						topMsg = "Press ENTER to continue";
						botTxt1 = "You have already selected this location to attack";
						botTxt2 = "Please pick another location";
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						displayImage();
						waiting = true;
						while (waiting)
						{
							inputMode();
							if (keyPress == ENTER)
							{
								waiting = false;
							}
						}
						botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
						botTxt2 = "a location, or press M to view your game board.";
						topMsg = "Player 1 Target Mode";
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						displayImage();
					}

				}
				else if (keyPress == 'm')
				{

					botTxt1 = "Now viewing your own game board";
					botTxt2 = "Press M to go back to the attack board";
					topMsg = "Player 1 View Mode";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					updateMap(PLAYER1);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
					}
					updateMap(PLAYER1ATT);
					botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
					botTxt2 = "a location, or press M to view your game board.";
					topMsg = "Player 1 Target Mode";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					displayImage();
				}
				highlightBoard(wIdx, hIdx);
			}
		}
		else if (selection == PLAYER2)
		{
			botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
			botTxt2 = "a location, or press M to view your game board.";
			topMsg = "Player 2 Target Mode";
			changeTopText(topMsg);
			changeBottomText(botTxt1, botTxt2);
			updateMap(PLAYER2ATT);
			displayImage();
			highlightBoard(wIdx, hIdx);

			while (waitForPlayer)
			{
				inputMode();
				if (keyPress == LEFT)
				{
					if (wIdx > 0)
					{
						wIdx--;
					}
				}
				else if (keyPress == UP)
				{
					if (hIdx > 0)
					{
						hIdx--;
					}
				}
				else if (keyPress == RIGHT)
				{
					if (wIdx < 9)
					{
						wIdx++;
					}
				}
				else if (keyPress == DOWN)
				{
					if (hIdx < 9)
					{
						hIdx++;
					}
				}
				else if (keyPress == ENTER)
				{
					if (p1Array[wIdx][hIdx] == PATROL || p1Array[wIdx][hIdx] == DESTROYER ||		//if a ship is present
						p1Array[wIdx][hIdx] == SUB || p1Array[wIdx][hIdx] == BATTLESHIP ||
						p1Array[wIdx][hIdx] == CARRIER)
					{
						checkForSink(wIdx, hIdx, PLAYER1);
						p1Array[wIdx][hIdx] = HIT;
						p2atkArray[wIdx][hIdx] = HIT;
						attackW = wIdx;			//Add coordinates for the attempted strike
						attackH = hIdx;

						if (shipSunk == NOTHING)
						{
							//designed to look like "COM >> A2 >> HIT
							boxText = "PLR2 HIT ";
							boxText += vCord(attackH);
							boxText += hCord(attackW);
							addToInfoBox(boxText);
							topMsg = "PLAYER 2 >> ";
							topMsg += vCord(attackH);
							topMsg += hCord(attackW);
							topMsg += " >> HIT";
							botTxt1 = "You have hit player 1 at ";
							botTxt1 += vCord(attackH);
							botTxt1 += hCord(attackW);
							botTxt2 = "Press ENTER to start player 1's turn";
						}
						else if (shipSunk != NOTHING)
						{
							boxText = "SUNK ";
							topMsg = "PLAYER 2 >> ";
							topMsg += vCord(attackH);
							topMsg += hCord(attackW);
							topMsg += " >> SINK >> ";
							botTxt1 = "You have sunk player 1's ";
							if (shipSunk == PATROL)
							{
								boxText += "P-BOAT";
								topMsg += "PATROL BOAT";
								botTxt1 += "patrol boat at ";
							}
							else if (shipSunk == DESTROYER)
							{
								boxText += "DESTR";
								topMsg += "DESTROYER";
								botTxt1 += "destroyer at ";
							}
							else if (shipSunk == SUB)
							{
								boxText += "SUB";
								topMsg += "SUBMARINE";
								botTxt1 += "submarine at ";
							}
							else if (shipSunk == BATTLESHIP)
							{
								boxText += "BATTLE";
								topMsg += "BATTLESHIP";
								botTxt1 += "battleship at ";
							}
							else if (shipSunk == CARRIER)
							{
								boxText += "CARIR";
								topMsg += "AIRCRAFT CARRIER";
								botTxt1 += "aircraft carrier at ";
							}
							addToInfoBox(boxText);
							botTxt1 += vCord(attackH);
							botTxt1 += hCord(attackW);
							boxText = "PLR2 SINK ";
							boxText += vCord(attackH);
							boxText += hCord(attackW);
							addToInfoBox(boxText);
							botTxt2 = "Press ENTER to start player 1's turn";
							}
							updateTime();
							recordFile << timeStamp << " " << topMsg << "\n";				//update attack in the records
							changeTopText(topMsg);
							changeBottomText(botTxt1, botTxt2);
							updateMap(PLAYER2ATT);
							displayImage();
							waiting = true;
							while (waiting)
							{
								inputMode();
								if (keyPress == ENTER)
								{
									waiting = false;
									waitForPlayer = false;
								}
							}
					}
					else if (p1Array[wIdx][hIdx] == NOTHING)
					{
						p1Array[wIdx][hIdx] = MISS;
						p2atkArray[wIdx][hIdx] = MISS;
						attackW = wIdx;			//Add coordinates for the attempted strike
						attackH = hIdx;

						//designed to look like "COM >> A2 >> HIT
						boxText = "PLR2 MISS ";
						boxText += vCord(attackH);
						boxText += hCord(attackW);
						addToInfoBox(boxText);
						topMsg = "PLAYER 2 >> ";
						topMsg += vCord(attackH);
						topMsg += hCord(attackW);
						topMsg += " >> MISS";
						botTxt1 = "You tried to hit player 1 at ";
						botTxt1 += vCord(attackH);
						botTxt1 += hCord(attackW);
						botTxt2 = "Press ENTER to start player 1's turn";
						updateTime();
						recordFile << timeStamp << " " << topMsg << "\n";				//update for the records
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						updateMap(PLAYER2ATT);
						displayImage();
						waiting = true;
						while (waiting)
						{
							inputMode();
							if (keyPress == ENTER)
							{
								waiting = false;
								waitForPlayer = false;
							}
						}
					}
					else if (p1Array[wIdx][hIdx] == HIT || p1Array[wIdx][hIdx] == SINK ||
						p1Array[wIdx][hIdx] == MISS)                     	     	//if it is a location that has already been hit
					{

						topMsg = "Press ENTER to continue";
						botTxt1 = "You have already selected this location to attack";
						botTxt2 = "Please pick another location";
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						displayImage();
						waiting = true;
						while (waiting)
						{
							inputMode();
							if (keyPress == ENTER)
							{
								waiting = false;
							}
						}
						botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
						botTxt2 = "a location, or press M to view your game board.";
						topMsg = "Player 2 Target Mode";
						changeTopText(topMsg);
						changeBottomText(botTxt1, botTxt2);
						displayImage();
					}

				}
				else if (keyPress == 'm')
				{

					botTxt1 = "Now viewing your own game board";
					botTxt2 = "Press M to go back to the attack board";
					topMsg = "Player 2 View Mode";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					updateMap(PLAYER2);
					displayImage();
					mapView = true;
					while (mapView)
					{
						inputMode();
						if (keyPress == 'm')
						{
							mapView = false;
						}
					}
					updateMap(PLAYER2ATT);
					botTxt1 = "Use the arrow keys to navigate, press ENTER to select";		//placement instructions
					botTxt2 = "a location, or press M to view your game board.";
					topMsg = "Player 2 Target Mode";
					changeTopText(topMsg);
					changeBottomText(botTxt1, botTxt2);
					displayImage();
				}
				highlightBoard(wIdx, hIdx);
			}
		}
	}

	return;
}

void battleship::checkForSink(int wIdx, int hIdx, int reciever)
{

	int timesFound = 0,
		seeking = 0;

	shipSunk = NOTHING;

	if (reciever == PLAYER1)
	{
		seeking = p1Array[wIdx][hIdx];
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (p1Array[wIndex][hIndex] == seeking)
				{
					timesFound++;
				}
			}
		}
		if (timesFound == 1)			//if it was only found one time (which is about to be hit)
		{
			shipSunk = seeking;			//this ship is going to be sunk
		}
		else if (timesFound > 1)		//if it was found more than once...
		{
			shipSunk = NOTHING;			//it will just be a hit
			shipHit = seeking;			//the ship that was not sunk will be marked at hit
		}
	}
	else if (reciever == PLAYER2)
	{
		seeking = p2Array[wIdx][hIdx];
		for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
		{
			for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
			{
				if (p2Array[wIndex][hIndex] == seeking)
				{
					timesFound++;
				}
			}
		}
		if (timesFound == 1)
		{
			shipSunk = seeking;
		}
		else if (timesFound > 1)
		{
			shipSunk = NOTHING;
			shipHit = seeking;			//the ship that was not sunk will be marked at hit
		}
	}
	else if (reciever == COMPUTER)
	{
		{
			seeking = comArray[wIdx][hIdx];
			for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
			{
				for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
				{
					if (comArray[wIndex][hIndex] == seeking)
					{
						timesFound++;
					}
				}
			}
			if (timesFound == 1)
			{
				shipSunk = seeking;
			}
			else if (timesFound > 1)
			{
				shipSunk = NOTHING;
				shipHit = seeking;			//the ship that was not sunk will be marked at hit
			}
		}
	}

	return;
}

void battleship::playerPlaceShip(int shipW, int shipH, int selection, int shipType)
{

	string topMessage = "";
	
	int wIdx = 0,			//create variables for width and height index
		hIdx = 0;

	bool prepingShip = true;
	bool shipInWay = false;

	highlightPlacement(wIdx, hIdx, shipW, shipH);

	while (prepingShip)
	{
		shipInWay = false;
		inputMode();
		if (keyPress == LEFT)
		{
			if (wIdx > 0)
			{
				wIdx--;
			}
		}
		else if (keyPress == UP)
		{
			if (hIdx > 0)
			{
				hIdx--;
			}
		}
		else if (keyPress == RIGHT)
		{
			if ((wIdx + shipW) <= 9)
			{
				wIdx++;
			}
		}
		else if (keyPress == DOWN)
		{
			if ((hIdx + shipH) <= 9)
			{
				hIdx++;
			}
		}
		else if (keyPress == 'r')
		{
			if ((wIdx + (shipH - 1)) <= 9 && (hIdx + (shipW - 1)) <= 9)
			{
				if (shipW > shipH)
				{
					shipH = shipW;
					shipW = 1;
				}
				else if (shipW < shipH)
				{
					shipW = shipH;
					shipH = 1;
				}
			}
		}
		else if (keyPress == ENTER && selection == PLAYER1)
		{
			for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
			{
				for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
				{
					if ((wIndex == wIdx && hIndex == hIdx) && shipW > shipH)
					{
						if (p1Array[wIndex][hIndex] == NOTHING && (!shipInWay))
						{
							for (int idx = 0; idx < shipW; idx++)
							{
								if (p1Array[wIndex + idx][hIndex] > NOTHING)			//search to see if there are ships where the ship will be placed
								{
									shipInWay = true;
									idx = shipW + 1;			         		//set the search index to the end of the for loop
								}
								else if (p1Array[wIndex + idx][hIndex] == NOTHING)
								{
									shipInWay = false;							//if there is nothing there, there is no ships in the way
								}
							}
							if (!shipInWay)						//if there is no ships in the way....
							{
								p1Array[wIndex][hIndex] = shipType;
								for (int idx = 0; idx < shipW; idx++)
								{
									p1Array[wIndex + idx][hIndex] = shipType;			//add the ships to the array
									prepingShip = false;
									updateMap(PLAYER1);
								}
							}
							else if (shipInWay)					//if there is a ship in the way....
							{
								topMessage = "You cannot place a ship on top of another";
								changeTopText(topMessage);
							}
						}
					}
				}
				if ((hIndex == hIdx && shipW < shipH) && (!shipInWay))
				{
					for (int idx = 0; idx < shipH; idx++)
					{
						if (p1Array[wIdx][hIndex + idx] > NOTHING)
						{
							shipInWay = true;			//set the ship in way flag to be true and 
							idx = shipH + 1;			//move to the end of the index
						}
						else if (p1Array[wIdx][hIndex + idx] == NOTHING)
						{
							shipInWay = false;				//if a ship was not found... set the flag to false
						}
					}
					if (shipInWay)
					{
						topMessage = "You cannot place a ship on top of another";
						changeTopText(topMessage);
					}
					else if (!shipInWay)
					{
						p1Array[wIdx][hIndex] = shipType;
						for (int idx = 0; idx < shipH; idx++)
						{
							p1Array[wIdx][hIndex + idx] = shipType;
							prepingShip = false;
							updateMap(PLAYER1);
						}
					}
				}
			}
		}
		else if (keyPress == ENTER && selection == PLAYER2)
		{
			for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
			{
				for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
				{
					if ((wIndex == wIdx && hIndex == hIdx) && shipW > shipH)
					{
						if (p2Array[wIndex][hIndex] == NOTHING && (!shipInWay))
						{
							for (int idx = 0; idx < shipW; idx++)
							{
								if (p2Array[wIndex + idx][hIndex] > NOTHING)			//search to see if there are ships where the ship will be placed
								{
									shipInWay = true;
									idx = shipW + 1;			         		//set the search index to the end of the for loop
								}
								else if (p2Array[wIndex + idx][hIndex] == NOTHING)
								{
									shipInWay = false;							//if there is nothing there, there is no ships in the way
								}
							}
							if (!shipInWay)						//if there is no ships in the way....
							{
								p2Array[wIndex][hIndex] = shipType;
								for (int idx = 0; idx < shipW; idx++)
								{
									p2Array[wIndex + idx][hIndex] = shipType;			//add the ships to the array
									prepingShip = false;
									updateMap(PLAYER2);
								}
							}
							else if (shipInWay)					//if there is a ship in the way....
							{
								topMessage = "You cannot place a ship on top of another";
								changeTopText(topMessage);
							}
						}
					}
				}
				if ((hIndex == hIdx && shipW < shipH) && (!shipInWay))
				{
					for (int idx = 0; idx < shipH; idx++)
					{
						if (p2Array[wIdx][hIndex + idx] > NOTHING)
						{
							shipInWay = true;			//set the ship in way flag to be true and 
							idx = shipH + 1;			//move to the end of the index
						}
						else if (p2Array[wIdx][hIndex + idx] == NOTHING)
						{
							shipInWay = false;				//if a ship was not found... set the flag to false
						}
					}
					if (shipInWay)
					{
						topMessage = "You cannot place a ship on top of another";
						changeTopText(topMessage);
					}
					else if (!shipInWay)
					{
						p2Array[wIdx][hIndex] = shipType;
						for (int idx = 0; idx < shipH; idx++)
						{
							p2Array[wIdx][hIndex + idx] = shipType;
							prepingShip = false;
							updateMap(PLAYER2);
						}
					}
				}
			}
		}
		highlightPlacement(wIdx, hIdx, shipW, shipH);
	}

	return;
}

void battleship::comPlaceShip(int shipW, int shipH, int shipType)
{
	int minVal1 = 0,
		maxVal1 = 9,
		minVal2 = 1,
		maxVal2 = 2,
		randValz = 0,
		randValx = 0,
		randValy = 0,
		wIdx = 0,			//create variables for width and height index
		hIdx = 0;

	bool prepingShip = true;
	bool shipInWay = false;

	while (prepingShip)
	{
		shipInWay = false;			//reset out ship in way flag

		randValx = ((rand() % (maxVal1 - minVal1 + 1)) + minVal1);			//generate an x coordinate value
		randValy = ((rand() % (maxVal1 - minVal1 + 1)) + minVal1);			//generate an y coordinate value
		randValz = ((rand() % (maxVal2 - minVal2 + 1)) + minVal2);			//flip a coin

		if (randValz == 2)						//if coinflip is tails... 
		{
			if (shipW > shipH)					//rotate the ship
			{
				shipH = shipW;
				shipW = 1;
			}
			else if (shipW < shipH)
			{
				shipW = shipH;
				shipH = 1;
			}
		}

		wIdx = randValx;				//set out random x and y values to the wIndex and hIndex
		hIdx = randValy;

		if ((wIdx >= 0 && ((wIdx + shipW) <= 9)) && (hIdx >= 0 && ((hIdx + shipH) <= 9)))	//ensure the coordinate is valid and does not go off map
		{
			for (int hIndex = 0; hIndex < ARR_H; hIndex++)				//height loop
			{
				for (int wIndex = 0; wIndex < ARR_W; wIndex++)						//width loop
				{
					if ((wIndex == wIdx && hIndex == hIdx) && shipW > shipH)
					{
						if (comArray[wIndex][hIndex] == NOTHING && (!shipInWay))
						{
							for (int idx = 0; idx < shipW; idx++)
							{
								if (comArray[wIndex + idx][hIndex] > NOTHING)	//search to see if there are ships where the ship will be placed
								{
									shipInWay = true;
									idx = shipW + 1;			         		//set the search index to the end of the for loop
								}
								else if (comArray[wIndex + idx][hIndex] == NOTHING)
								{
									shipInWay = false;							//if there is nothing there, there is no ships in the way
								}
							}
							if (!shipInWay)						//if there is no ships in the way....
							{
								comArray[wIndex][hIndex] = shipType;
								for (int idx = 0; idx < shipW; idx++)
								{
									comArray[wIndex + idx][hIndex] = shipType;			//add the ships to the array
									prepingShip = false;				//unflags the ship prep
								}
							}
						}
					}
				}
				if ((hIndex == hIdx && shipW < shipH) && (!shipInWay))
				{
					for (int idx = 0; idx < shipH; idx++)
					{
						if (comArray[wIdx][hIndex + idx] > NOTHING)
						{
							shipInWay = true;			//set the ship in way flag to be true and 
							idx = shipH + 1;			//move to the end of the index
						}
						else if (comArray[wIdx][hIndex + idx] == NOTHING)
						{
							shipInWay = false;				//if a ship was not found... set the flag to false
						}
					}
					if (!shipInWay)
					{
						comArray[wIdx][hIndex] = shipType;
						for (int idx = 0; idx < shipH; idx++)
						{
							comArray[wIdx][hIndex + idx] = shipType;
							prepingShip = false;
						}
					}
				}
			}
		}					
	}
	// if the value is invalid, the placement will loop and generate another random number

	return;
}

void battleship::highlightPlacement(int wIdx, int hIdx, int shipW,int shipH)
{

	char holder1 = 0,				//holds the values for the characters that will be swapped
		holder2 = 0;

	int boardW = 0,
		boardWmax = 0,
		boardH = 0,
		boardHmax = 0;

	boardH = (6 + (hIdx * 2));				//find these places on the display

	boardHmax = (6 + ((hIdx + (shipH - 1)) * 2));

	boardW = (20 + (wIdx * 4));

	boardWmax = (20 + ((wIdx + (shipW - 1)) * 4));


	holder1 = display[boardW][boardH];
	holder2 = display[boardWmax][boardHmax];


	display[boardW][boardH] = '#';
	display[boardWmax][boardHmax] = '#';
	displayImage();
	display[boardW][boardH] = holder1;
	display[boardWmax][boardHmax] = holder2;

	return;
}

void battleship::updateMap(int selection)
{
	if (selection == PLAYER1)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (p1Array[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (p1Array[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (p1Array[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (p1Array[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (p1Array[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (p1Array[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (p1Array[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (p1Array[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (p1Array[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}
			}
		}
	}
	else if (selection == PLAYER2)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (p2Array[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (p2Array[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (p2Array[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (p2Array[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (p2Array[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (p2Array[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (p2Array[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (p2Array[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (p2Array[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}
			}
		}
	}
	else if (selection == COMPUTER)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (comArray[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (comArray[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (comArray[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (comArray[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (comArray[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (comArray[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (comArray[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (comArray[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (comArray[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}

			}
		}
	}
	else if (selection == PLAYER1ATT)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (p1atkArray[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (p1atkArray[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (p1atkArray[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (p1atkArray[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (p1atkArray[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (p1atkArray[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (p1atkArray[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (p1atkArray[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (p1atkArray[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}
			}
		}
	}
	else if (selection == PLAYER2ATT)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (p2atkArray[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (p2atkArray[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (p2atkArray[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (p2atkArray[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (p2atkArray[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (p2atkArray[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (p2atkArray[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (p2atkArray[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (p2atkArray[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}
			}
		}
	}
	else if (selection == BLANK)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				if (blankArray[wIdx][hIdx] == NOTHING)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = ' ';
				}
				else if (blankArray[wIdx][hIdx] == PATROL)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'B';
				}
				else if (blankArray[wIdx][hIdx] == DESTROYER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '+';
				}
				else if (blankArray[wIdx][hIdx] == SUB)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '=';
				}
				else if (blankArray[wIdx][hIdx] == BATTLESHIP)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '$';
				}
				else if (blankArray[wIdx][hIdx] == CARRIER)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '@';
				}
				else if (blankArray[wIdx][hIdx] == HIT)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'X';
				}
				else if (blankArray[wIdx][hIdx] == MISS)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = 'O';
				}
				else if (blankArray[wIdx][hIdx] == SINK)
				{
					display[(20 + (wIdx * 4))][(6 + (hIdx * 2))] = '#';
				}
			}
		}
	}

	return;
}

void battleship::resetBoard(int selection)
{
	if (selection == PLAYER1)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				p1Array[wIdx][hIdx] = NOTHING;				//reset p1 array with all 0's
				p1atkArray[wIdx][hIdx] = NOTHING;
			}
		}
	}
	else if (selection == PLAYER2)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				p2Array[wIdx][hIdx] = NOTHING;				//reset p2 array with all 0's
				p2atkArray[wIdx][hIdx] = NOTHING;
			}
		}
	}
	else if (selection == COMPUTER)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				comArray[wIdx][hIdx] = NOTHING;				//reset com array with all 0's
			}
		}
	}
	else if (selection == BLANK)
	{
		for (int hIdx = 0; hIdx < ARR_H; hIdx++)
		{
			for (int wIdx = 0; wIdx < ARR_W; wIdx++)
			{
				blankArray[wIdx][hIdx] = NOTHING;				//reset blank array with all 0's
			}
		}
	}
	return;
}

string battleship::vCord(int attackH)
{
	if (attackH == 0)
	{
		return "A";
	}
	else if (attackH == 1)
	{
		return "B";
	}
	else if (attackH == 2)
	{
		return "C";
	}
	else if (attackH == 3)
	{
		return "D";
	}
	else if (attackH == 4)
	{
		return "E";
	}
	else if (attackH == 5)
	{
		return "F";
	}
	else if (attackH == 6)
	{
		return "G";
	}
	else if (attackH == 7)
	{
		return "H";
	}
	else if (attackH == 8)
	{
		return "I";
	}
	else if (attackH == 9)
	{
		return "J";
	}
	return "0";
}

string battleship::hCord(int attackW)
{
	attackW++;				//offset by 1 left
	if (attackW < 0)
	{
		attackW = 9;
	}
	else if (attackW > 9)
	{
		attackW = 0;
	}
	return to_string(attackW);
}

void battleship::changeSoundtrack(int change) //change the music soundtrack
{
	trackNum = trackNum + change;
	if (trackNum < 0)	//if track number is -1
	{
		trackNum = 4;	//loop around to the last track
	}
	else if (trackNum > 4)	//if track number is over 4
	{
		trackNum = 0;	//loop around to the first track
	}

	if (trackNum == 0)
	{
		sndPlaySound("Stars & Stripes.wav", SND_LOOP | SND_ASYNC);		//loops stars and stripes
	}
	else if (trackNum == 1)
	{
		sndPlaySound("Rufus Welcoming.wav", SND_LOOP | SND_ASYNC);		//loops rufus welcoming
	}
	else if (trackNum == 2)
	{
		sndPlaySound("SMB3 Airship.wav", SND_LOOP | SND_ASYNC);		//loops Airship theme
	}
	else if (trackNum == 3)
	{
		sndPlaySound("CCR Unf Inst.wav", SND_LOOP | SND_ASYNC);		//loops unfortunate son
	}
	else if (trackNum == 4)
	{
		PlaySound(NULL, 0, 0);										//stops playing music
	}


	return;
}

void battleship::updateTime(void)										//updates the time for the time stamp
{
	int totalSec = time(0),		//gets number of seconds that have elapsed since Jan, 1, 1970
		year = 0,
		month = 0,
		day = 0,
		hour = 0,
		minute = 0,
		second = 0,
		mon = 1;		//a counter for months

	totalSec += 2750400;	//offset this clock to give the correct time (not perfect by any means)
	
	while (totalSec > 0)
	{
		if (totalSec >= 31536000)		//seconds in a year
		{
			while (totalSec >= 31536000)
			{
				if ((year % 4) != 0)			//if leap year
				{
					totalSec -= 31536000;
				}
				else if ((year % 4) == 0)			//if leap year
				{
					totalSec -= 31622400;
				}
				year++;
			}
			year += 1970;

		}
		else if (totalSec < 31557600 && totalSec >= 2419200)		//seconds in a month
		{
			while ((totalSec < 31557600 && totalSec >= 2505600) && mon <= 12)
			{
				if (mon == 1)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 2)
				{
					if ((year % 4) != 0)			//if not leap year
					{
						totalSec -= 2419200;
					}
					else if ((year % 4) == 0)			//if leap year
					{
						totalSec -= 2505600;
					}
					month++;
				}
				else if (mon == 3)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 4)
				{
					totalSec -= 2592000;
					month++;
				}
				else if (mon == 5)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 6)
				{
					totalSec -= 2592000;
					month++;
				}
				else if (mon == 7)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 8)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 9)
				{
					totalSec -= 2592000;
					month++;
				}
				else if (mon == 10)
				{
					totalSec -= 2678400;
					month++;
				}
				else if (mon == 11)
				{
					totalSec -= 2592000;
					month++;
				}
				else if (mon == 12)
				{
					totalSec -= 2678400;
					month++;
				}
				mon++;
			}

		}
		else if (totalSec < 2592000 && totalSec >= 86400)		//seconds in a day
		{
			day = (totalSec / 86400);
			totalSec -= (day * 86400);
		}
		else if (totalSec < 86400 && totalSec >= 3600)		//seconds in an hour
		{
			hour = (totalSec / 3600);
			totalSec -= (hour * 3600);
		}
		else if (totalSec < 3600 && totalSec >= 60)		//seconds in an minute
		{
			minute = (totalSec / 60);
			totalSec -= (minute * 60);
		}
		else if (totalSec < 60)		//seconds less than a minute
		{
			second = totalSec;
			totalSec -= second;
		}
	}

	if (month == 1)
	{
		timeStamp = "Jan";
	}
	else if (month == 2)
	{
		timeStamp = "Feb";
	}
	else if (month == 3)
	{
		timeStamp = "Mar";
	}
	else if (month == 4)
	{
		timeStamp = "Apr";
	}
	else if (month == 5)
	{
		timeStamp = "May";
	}
	else if (month == 6)
	{
		timeStamp = "Jun";
	}
	else if (month == 7)
	{
		timeStamp = "Jul";
	}
	else if (month == 8)
	{
		timeStamp = "Aug";
	}
	else if (month == 9)
	{
		timeStamp = "Sep";
	}
	else if (month == 10)
	{
		timeStamp = "Oct";
	}
	else if (month == 11)
	{
		timeStamp = "Nov";
	}
	else if (month == 12)
	{
		timeStamp = "Dec";
	}
	timeStamp += " ";
	timeStamp += to_string(day);
	timeStamp += "  ";
	timeStamp += to_string(hour);
	timeStamp += ":";
	timeStamp += to_string(minute);
	timeStamp += ":";
	timeStamp += to_string(second);
	timeStamp += "  ";
	timeStamp += to_string(year);

	return;
}
