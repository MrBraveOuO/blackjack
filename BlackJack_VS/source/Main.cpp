// Programmer: Vladislav Shulman
// Final Project
// Blackjack

// Feel free to use any and all parts of this program and claim it as your own work

//FINAL DRAFT

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>                //Used for srand((unsigned) time(NULL)) command
#include <process.h>             //Used for system("cls") command

#define spade 06                 //Used to print spade symbol
#define club 05                  //Used to print club symbol
#define diamond 04               //Used to print diamond symbol
#define heart 03                 //Used to print heart symbol
#define RESULTS "Blackjack.txt"  //File name is Blackjack
typedef struct card {
	const char *face;
	const char *suit;
}Card;
char name[50];
//Global Variables
int k;
int l;
int d;
int won;
int loss;
int cash = 500;
int bet;
int random_card;
int player_total = 0;
int dealer_total;

void saveboard();
void boardsort();
//Function Prototypes
int tface(const char * i);
void showcard(Card * const wPlay, Card * const Dealer, int  p_sheet, int  d_sheet);//圖形化顯示出電腦手牌以及玩家手牌  
void fillDeck(Card * const wDeck, const char *wFace[], const char * wSuit[]);//設定出52張不同花色和數字的牌 
void shuffle(Card * const wDeck);//打亂其排列順序 
void deal(const Card * const wDeck);//顯示出Card的排序 
int givepcard(Card * const wDeck, Card * const wPlay, int * t_sheet, int * p_sheet);//給玩家發一張牌，同時計算牌之得點 
int givedcard(Card * const wDeck, Card * const Dealer, int * t_sheet, int * d_sheet);//給電腦發一張牌，同時計算牌之得點
int betting();       //Asks user amount to bet
void asktitle();     //Asks user to continue
void rules();        //Prints "Rules of Vlad's Blackjack" menu
void play();         //Plays game
void stay(Card * const wDeck, Card * const wPlay, Card * const Dealer, int *t_sheet, int p_sheet, int *d_sheet);         //Function for when user selects 'Stay'
void cash_test();    //Test for if user has cash remaining in purse
void askover();      //Asks if user wants to continue playing
void fileresults();  //Prints results into Blackjack.txt file in program directory
void Delay(unsigned int secs) //延遲副程式 
{
	unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);
}
//Main Function
int main(void)
{
	int choice1;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=================================================================================\n");
	printf("		$$$$    $         $      $$$$   $   $     $$$$$$$$      $\n");
	printf("		$   $   $        $ $    $       $  $             $    $ $\n");
	printf("		$$$$    $       $   $   $       $$$              $   $  $\n");
	printf("		$   $   $       $$$$$   $       $  $             $      $\n");
	printf("		$$$$    $$$$$   $   $    $$$$   $   $     $$$$$$$$      $\n");

	printf("		    $$$$$     $      $$$$   $   $         $             $\n");
	printf("		       $     $ $    $       $  $          $             $\n");
	printf("		       $    $   $   $       $$$           $             $\n");
	printf("		    $  $    $$$$$   $       $  $          $             $\n");
	printf("		     $$$    $   $    $$$$   $   $         $$$$$$$$   $$$$$$$\n");
	printf("==================================================================================\n");
	printf("\n");
	printf("\n");
	asktitle();

	printf("\n");
	printf("\n");
	system("pause");
	return(0);
} //end program

void asktitle() // Function for asking player if they want to continue
{
	char choice1;
	int choice2;

	printf("\n               		  Are You Ready?");
	printf("\n               		 ----------------");
	printf("\n                     	       (Y/N)\n                        ");
	scanf("\n%c", &choice1);

	while ((choice1 != 'Y') && (choice1 != 'y') && (choice1 != 'N') && (choice1 != 'n')) // If invalid choice entered
	{
		printf("\n");
		printf("Incorrect Choice. Please Enter Y for Yes or N for No.\n");
		scanf("%c", &choice1);
	}


	if ((choice1 == 'Y') || (choice1 == 'y')) // If yes, continue. Prints menu.
	{
		system("cls");
		printf("\nEnter 1 to Begin the Greatest Game Ever Played.");
		printf("\nEnter 2 to See a Complete Listing of Rules.");
		printf("\nEnter 3 to Exit Game. (Not Recommended)");
		printf("\nChoice: ");
		scanf("%d", &choice2); // Prompts user for choice
		if ((choice2 < 1) || (choice2 > 3)) // If invalid choice entered
		{
			printf("\nIncorrect Choice. Please enter 1, 2 or 3\n");
			scanf("%d", &choice2);
		}
		switch (choice2) // Switch case for different choices
		{
		case 1: // Case to begin game
			system("cls");

			play();

			break;

		case 2: // Case to see rules
			system("cls");
			rules();
			break;

		case 3: // Case to exit game
			printf("\nYour day could have been perfect.");
			printf("\nHave an almost perfect day!\n\n");
			system("pause");
			exit(0);
			break;

		default:
			printf("\nInvalid Input");
		} // End switch case
	} // End if loop



	else if ((choice1 == 'N') || (choice1 == 'n')) // If no, exit program
	{
		printf("\nYour day could have been perfect.");
		printf("\nHave an almost perfect day!\n\n");
		system("pause");
		exit(0);
	}

	return;
} // End function

void rules() //Prints "Rules of Vlad's Blackjack" list
{
	char choice1;
	int choice2;

	printf("\n           RULES of VLAD's BLACKJACK");
	printf("\n          ---------------------------");
	printf("\nI.");
	printf("\n     Thou shalt not question the odds of this game.");
	printf("\n      %c This program generates cards at random.", spade);
	printf("\n      %c If you keep losing, you are very unlucky!\n", diamond);

	printf("\nII.");
	printf("\n     Each card has a value.");
	printf("\n      %c Number cards 1 to 10 hold a value of their number.", spade);
	printf("\n      %c J, Q, and K cards hold a value of 10.", diamond);
	printf("\n      %c Ace cards hold a value of 11", club);
	printf("\n     The goal of this game is to reach a card value total of 21.\n");

	printf("\nIII.");
	printf("\n     After the dealing of the first two cards, YOU must decide whether to HIT or STAY.");
	printf("\n      %c Staying will keep you safe, hitting will add a card.", spade);
	printf("\n     Because you are competing against the dealer, you must beat his hand.");
	printf("\n     BUT BEWARE!.");
	printf("\n      %c If your total goes over 21, you will LOSE!.", diamond);
	printf("\n     But the world is not over, because you can always play again.\n");
	printf("\n%c%c%c YOUR RESULTS ARE RECORDED AND FOUND IN SAME FOLDER AS PROGRAM %c%c%c\n", spade, heart, club, club, heart, spade);
	printf("\nWould you like to go the previous screen? (I will not take NO for an answer)");
	printf("\n                  (Y/N)\n                    ");
	scanf("\n%c", &choice1);

	while ((choice1 != 'Y') && (choice1 != 'y') && (choice1 != 'N') && (choice1 != 'n')) // If invalid choice entered
	{
		printf("\n");
		printf("Incorrect Choice. Please Enter Y for Yes or N for No.\n");
		scanf("%c", &choice1);
	}


	if ((choice1 == 'Y') || (choice1 == 'y')) // If yes, continue. Prints menu.
	{
		system("cls");
		asktitle();
	} // End if loop



	else if ((choice1 == 'N') || (choice1 == 'n')) // If no, convinces user to enter yes
	{
		system("cls");
		printf("\n                 I told you so.\n");
		asktitle();
	}

	return;
} // End function


void play() //Plays game
{
	int p = 0; // holds value of player_total
	int i = 1; // counter for asking user to hold or stay (aka game turns)
	char choice3;
	Card deck[52];
	Card play[5];
	Card dealer[5];
	const char *face[13] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	const char *suit[] = { "Heart","Diamonds","Clubs","Spades" };
	int t_sheet = 0;
	int p_sheet = 0;
	int d_sheet = 0;
	srand(time(NULL));
	fillDeck(deck, face, suit);
	shuffle(deck);
	cash = cash;
	cash_test();
	givepcard(deck, play, &t_sheet, &p_sheet);
	player_total = p + l; //Computes player total
	p = player_total;
	printf("\nYour Total is %d\n", p); //Prints player total
	givedcard(deck, dealer, &t_sheet, &d_sheet);
	dealer_total = dealer_total + d;
	showcard(play, dealer, p_sheet, d_sheet);
	Delay(1);
	printf("\nCash: $%d\n", cash); //Prints amount of cash user has
	betting(); //Prompts user to enter bet amount

	while (i <= 21) //While loop used to keep asking user to hit or stay at most twenty-one times
				 //  because there is a chance user can generate twenty-one consecutive 1's
	{
		if (p == 21) //If user total is 21, win
		{
			printf("\nYour Total is %d\n", p);
			printf("\nDealer Total is %d\n", dealer_total);
			printf("\nUnbelievable! You Win!\n");
			won = won + 1;
			cash = cash + bet;
			printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
			dealer_total = 0;
			askover();
		}

		if (p > 21) //If player total is over 21, loss
		{
			printf("\nYour Total is %d\n", p);
			printf("\nDealer Total is %d\n", dealer_total);
			printf("\nWoah Buddy, You Went WAY over.\n");
			loss = loss + 1;
			printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
			dealer_total = 0;
			askover();
		}

		if (p <= 21) //If player total is less than 21, ask to hit or stay
		{
			printf("\n\nWould You Like to Hit or Stay?");

			scanf("%c", &choice3);
			while ((choice3 != 'H') && (choice3 != 'h') && (choice3 != 'S') && (choice3 != 's')) // If invalid choice entered
			{
				printf("\n");
				printf("Please Enter H to Hit or S to Stay.\n");
				scanf("%c", &choice3);
			}


			if ((choice3 == 'H') || (choice3 == 'h')) // If Hit, continues
			{
				givepcard(deck, play, &t_sheet, &p_sheet);
				player_total = p + l;
				p = player_total;
				showcard(play, dealer, p_sheet, d_sheet);
				printf("\nYour Total is %d\n", p);
				printf("\nDealer Total is %d\n", dealer_total);
				if (dealer_total == 21) //Is dealer total is 21, loss
				{
					printf("\nDealer Has the Better Hand. You Lose.\n");
					loss = loss + 1;
					cash = cash - bet;
					printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
					dealer_total = 0;
					askover();
				}

				if (dealer_total > 21) //If dealer total is over 21, win
				{
					printf("\nDealer Has Went Over!. You Win!\n");
					won = won + 1;
					cash = cash + bet;
					printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
					dealer_total = 0;
					askover();
				}
			}
			if ((choice3 == 'S') || (choice3 == 's')) // If Stay, does not continue
			{
				printf("\nYou Have Chosen to Stay at %d. Wise Decision!\n", player_total);
				stay(deck, play, dealer,&t_sheet, p_sheet,&d_sheet);
			}
		}
		i++; //While player total and dealer total are less than 21, re-do while loop
	} // End While Loop
} // End Function

void stay(Card * const wDeck, Card * const wPlay, Card * const Dealer, int *t_sheet, int p_sheet, int *d_sheet) //Function for when user selects 'Stay'
{
	givedcard(wDeck, Dealer, t_sheet, d_sheet);
	dealer_total = dealer_total + d;
	showcard(wPlay, Dealer, p_sheet, *d_sheet);
	if (dealer_total >= 17)
	{
		if (dealer_total > 21) //If dealer's total is more than 21, win
		{
			printf("\nUnbelievable! You Win!\n");
			won = won + 1;
			cash = cash + bet;
			printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
			dealer_total = 0;
			askover();
		}
		else if (player_total >= dealer_total) //If player's total is more than dealer's total, win
		{
			printf("\nUnbelievable! You Win!\n");
			won = won + 1;
			cash = cash + bet;
			printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
			dealer_total = 0;
			askover();
		}
		else if (player_total < dealer_total) //If player's total is less than dealer's total, loss
		{
			printf("\nDealer Has the Better Hand. You Lose.\n");
			loss = loss + 1;
			cash = cash - bet;
			printf("\nYou have %d Wins and %d Losses. Awesome!\n", won, loss);
			dealer_total = 0;
			askover();
		}
	}
	else
	{
		stay(wDeck, wPlay, Dealer, t_sheet, p_sheet, d_sheet);
	}

} // End Function

void cash_test() //Test for if user has cash remaining in purse
{
	if (cash <= 0) //Once user has zero remaining cash, game ends and prompts user to play again
	{
		printf("You Are Bankrupt. Game Over");
		cash = 500;
		askover();
	}
} // End Function

int betting() //Asks user amount to bet
{
	printf("\n\nEnter Bet: $");
	scanf("%d", &bet);

	if (bet > cash) //If player tries to bet more money than player has
	{
		printf("\nYou cannot bet more money than you have.");
		printf("\nEnter Bet: ");
		scanf("%d", &bet);
		return bet;
	}
	else return bet;
} // End Function

void askover() // Function for asking player if they want to play again
{
	char choice1;

	printf("\nWould You Like To Play Again?");
	printf("\nPlease Enter Y for Yes or N for No\n");
	scanf("\n%c", &choice1);

	while ((choice1 != 'Y') && (choice1 != 'y') && (choice1 != 'N') && (choice1 != 'n')) // If invalid choice entered
	{
		printf("\n");
		printf("Incorrect Choice. Please Enter Y for Yes or N for No.\n");
		scanf("%c", &choice1);
	}


	if ((choice1 == 'Y') || (choice1 == 'y')) // If yes, continue.
	{
		system("cls");
		play();
	}

	else if ((choice1 == 'N') || (choice1 == 'n')) // If no, exit program
	{
		fileresults();
		printf("\nBYE!!!!\n\n");
		system("pause");
		exit(0);
	}
	return;
} // End function

void fileresults() //Prints results into Blackjack.txt file in program directory
{
	FILE *fpresults; //File pointer is fpresults
	fpresults = fopen(RESULTS, "w"); //Creates file and writes into it
	if (fpresults == NULL) // what to do if file missing from directory
	{
		printf("\nError: File Missing\n");
		system("pause");
		exit(1);
	}
	else
	{
		fprintf(fpresults, "\n\t RESULTS");
		fprintf(fpresults, "\n\t---------\n");
		fprintf(fpresults, "\nYou Have Won %d Times\n", won);
		fprintf(fpresults, "\nYou Have Lost %d Times\n", loss);
		fprintf(fpresults, "\nKeep Playing and Set an All-Time Record!");
	}
	fclose(fpresults);
	return;
}
void fillDeck(Card * const wDeck, const char *wFace[], const char * wSuit[])
{
	int i;

	for (i = 0; i <= 51; i++)
	{
		wDeck[i].face = wFace[i % 13];
		wDeck[i].suit = wSuit[i / 13];
	}
}
void shuffle(Card * const wDeck)
{
	int i;
	int j;
	Card temp;

	for (i = 0; i <= 51; i++)
	{
		j = rand() % 52;

		temp = wDeck[i];
		wDeck[i] = wDeck[j];
		wDeck[j] = temp;
	}
}
void deal(const Card * const wDeck)
{
	int i;

	for (i = 0; i <= 51; i++)
	{
		printf("%s of %-8s%s", wDeck[i].face, wDeck[i].suit, (i + 1) % 4 ? " " : "\n");
	}
}
int givepcard(Card * const wDeck, Card * const wPlay, int * t_sheet, int * p_sheet)
{
	wPlay[*p_sheet].face = wDeck[*t_sheet].face;
	wPlay[*p_sheet].suit = wDeck[*t_sheet].suit;
	if (wPlay[*p_sheet].face == "A") {
		if (player_total <= 10)
			l = 11;
		else if (player_total > 10)
			l = 1;
	}
	else if (wPlay[*p_sheet].face == "J" || wPlay[*p_sheet].face == "Q" || wPlay[*p_sheet].face == "K")
		l = 10;
	else
		l = tface(wPlay[*p_sheet].face);
	*p_sheet = *p_sheet + 1;
	*t_sheet = *t_sheet + 1;
	return l;
}
int givedcard(Card * const wDeck, Card * const wDealer, int * t_sheet, int * d_sheet)
{
	wDealer[*d_sheet].face = wDeck[*t_sheet].face;
	wDealer[*d_sheet].suit = wDeck[*t_sheet].suit;

	if (wDealer[*d_sheet].face == "A") {
		if (dealer_total <= 10)
			d = 11;
		else if (dealer_total > 10)
			d = 1;
	}
	else if (wDealer[*d_sheet].face == "J" || wDealer[*d_sheet].face == "Q" || wDealer[*d_sheet].face == "K")
		d = 10;
	else
		d = tface(wDealer[*d_sheet].face);
	*d_sheet = *d_sheet + 1;
	*t_sheet = *t_sheet + 1;
	return d;
}
void showcard(Card * const wPlay, Card * const Dealer, int  p_sheet, int  d_sheet)
{
	system("cls");
	int i;
	printf("\n電腦手牌:\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("------------    ");
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|%-8s  |    ", Dealer[i].suit);
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|    %2s    |    ", Dealer[i].face);
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("|  %8s|    ", Dealer[i].suit);
	}
	printf("\n");
	for (i = 0; i < d_sheet; i++)
	{
		printf("------------    ");
	}

	printf("\n玩家手牌:\n");
	Delay(1);

	for (i = 0; i < p_sheet; i++)
	{
		printf("------------    ");
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|%-8s  |    ", wPlay[i].suit);
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|    %2s    |    ", wPlay[i].face);
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|          |    ");
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("|  %8s|    ", wPlay[i].suit);
	}
	printf("\n");
	for (i = 0; i < p_sheet; i++)
	{
		printf("------------    ");
	}

}// End Function

int tface(const char * i) {
	int z;
	if (i == "2")
		z = 2;
	else if (i == "3")
		z = 3;
	else if (i == "4")
		z = 4;
	else if (i == "5")
		z = 5;
	else if (i == "6")
		z = 6;
	else if (i == "7")
		z = 7;
	else if (i == "8")
		z = 8;
	else if (i == "9")
		z = 9;
	else if (i == "10")
		z = 10;
	return z;

		
}