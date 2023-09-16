#include <iostream>
#include <cstdlib>
using namespace std;

enum enChoice {Stone = 1 ,Paper = 2 ,Scissor = 3};

enum enWinner {Player = 1 ,Pc = 2 ,NoWinner = 3};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

enChoice ReadPlayerChoice()
{
	short PlayerChoice = 0;

	do
	{
		cout << "Enter Your Choice [1]:Stone ,[2]:Paper ,[3]:Scissor\n";

		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enChoice)PlayerChoice;
}

enChoice GetPcChoice()
{
	return (enChoice)RandomNumber(1, 3);
}

string PrintChoice(enChoice Choice)
{
	string arrChoice[3] = { "Stone" ,"Paper" ,"Scissor" };

	return arrChoice[Choice - 1];
}

enWinner WhoWonTheRound(enChoice PlayerChoice, enChoice PcChoice)
{
	if (PlayerChoice == PcChoice)
		return enWinner::NoWinner;
	switch (PlayerChoice)
	{
	case enChoice::Paper:
		if (PcChoice == enChoice::Scissor)
		{
			return enWinner::Pc;
		}
		break;
	case enChoice::Scissor:
		if (PcChoice == enChoice::Stone)
		{
			return enWinner::Pc;
		}
		break;
	case enChoice::Stone:
		if (PcChoice == enChoice::Paper)
		{
			return enWinner::Pc;
		}
		break;
	default:
		return enWinner::Player;
	}
	return enWinner::Player;	
}

string PrintWinner(enWinner Winner)
{
	string arrWinner[3] = { "Player" ,"Computer" ,"No Winner" };

	return arrWinner[Winner - 1];
}

void SetScreenColor(enWinner Winner)
{
	if (Winner == enWinner::Player)
		system("color 2F");
	else if (Winner == enWinner::Pc)
	{
		system("color 4F");
		cout << "\a";
	}
	else
		system("color 6F");
}

short ReadHowManyRounds()
{
	short NumberOfRounds = 0;

	do
	{
		cout << "Enter Number Of Rounds 1 to 10 \n";
		cin >> NumberOfRounds;

	} while (NumberOfRounds < 1 || NumberOfRounds > 10);

	return NumberOfRounds;
}

struct stRound
{
	enChoice PlayerChoice;
	enChoice PcChoice;
	enWinner RoundWinner;
};

struct stGameResults
{
	stRound RoundList[100];
	int GameRound = 0;
	short PlayerWonTimes = 0;
	short PcWonTimes = 0;
	short DrawTimes = 0;
	enWinner FinalWinner;
};

enWinner WhoWonTheGame(short PlayerWonTimes, short PcWonTimes)
{
	if (PlayerWonTimes == PcWonTimes)
		return enWinner::NoWinner;
	else if (PlayerWonTimes > PcWonTimes)
		return enWinner::Player;
	else
		return enWinner::Pc;
}

stRound FillRound(stRound& Round )
{
	Round.PlayerChoice = ReadPlayerChoice();
	Round.PcChoice = GetPcChoice();
	Round.RoundWinner = WhoWonTheRound(Round.PlayerChoice ,Round.PcChoice);

	return Round;
}

void GenerateRounds(stGameResults& GameResults, stRound Round ,short NumberOfRounds )
{
	{
		GameResults.RoundList[NumberOfRounds] = FillRound(Round);
	}
}

void PrintRound(stGameResults& GameResults ,short NumberOfRounds ,short RoundNumber)
{
	cout << "\n______________Round[" << RoundNumber + 1 << "]______________\n\n";

	cout << "Player Choice   : " << PrintChoice(GameResults.RoundList[NumberOfRounds]
		.PlayerChoice) << endl;
	cout << "Computer Choice : " << PrintChoice (GameResults.RoundList[NumberOfRounds]
		.PcChoice) << endl;
	cout << "Winner is       : [" << PrintWinner (GameResults.RoundList[NumberOfRounds]
		.RoundWinner) << "]" <<  endl;

	SetScreenColor(GameResults.RoundList[NumberOfRounds]
		.RoundWinner);

	cout << "____________________________________\n\n";

	enWinner WhoTheWinner = GameResults.RoundList[NumberOfRounds].RoundWinner;

	switch (WhoTheWinner)
	{
	case enWinner::Player:
		GameResults.PlayerWonTimes++;
		break;
	case enWinner::Pc:
		GameResults.PcWonTimes++;
		break;
	default:
		GameResults.DrawTimes++;
		break;
	}
}

void PrintRoundAndFillResults(stGameResults& GameResults ,stRound& Round ,short NumberOfRounds)
{
	GameResults.GameRound = NumberOfRounds;


	for (short RoundNumber = 0; RoundNumber < NumberOfRounds; RoundNumber++)
	{
		cout << "\nRound [" << RoundNumber + 1 << "] Begins : " << endl;
		GenerateRounds(GameResults, Round, NumberOfRounds);
		PrintRound(GameResults, NumberOfRounds ,RoundNumber);
	}
}

string Tabs(short Number)
{
	for (short i = 1; i <= Number; i++)
	{
		string t = "";
		t = t + "\t";
		return t;
	}
}

void PrintGameOverScreen()
{
	cout << Tabs(4) << "_____________________________________________________________\n\n";

	cout << Tabs(4) << "                + + + G A M E . O V E R + + +\n\n";

	cout << Tabs(4) << "_____________________________________________________________\n\n";
}

void PrintWelcomScreen()
{
	cout << Tabs(4) << "***********************************************************\n\n";

	cout << Tabs(4) << "           S T O N E . P A P E R . S C I S S O R\n";

	cout << Tabs(4) << "                        G A M E\n\n";

	cout << Tabs(4)  << "***********************************************************\n\n";
}

void PrintResults(stGameResults GameResults)
{
	cout << Tabs(4) << "__________________________[Game Results]_____________________\n\n";

	cout << Tabs(4) << "Game Rounds      : " <<  GameResults.GameRound << endl;
	cout << Tabs(4) << "Player Won Times : " << GameResults.PlayerWonTimes << endl;
	cout << Tabs(4) << "Pc Won Times     : " << GameResults.PcWonTimes << endl;
	cout << Tabs(4) << "Draw Time        : " << GameResults.DrawTimes << endl;
    GameResults.FinalWinner = WhoWonTheGame(GameResults.PlayerWonTimes, GameResults.PcWonTimes);
	cout << Tabs(4) << "Final Winner     : " << PrintWinner(GameResults.FinalWinner) << endl;

	SetScreenColor(GameResults.FinalWinner);

	cout << Tabs(4) << "_____________________________________________________________\n\n";
}

void PlayGame(stGameResults GameResults)
{
	stRound Round;

	PrintWelcomScreen();
	PrintRoundAndFillResults(GameResults, Round , ReadHowManyRounds());
	PrintGameOverScreen();
	PrintResults(GameResults);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	stGameResults GameResults;
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayGame(GameResults);
		cout << "Do You Want To Play Again [Y]:Yes ,[N]:No ?\n";
		
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}



