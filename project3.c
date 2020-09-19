/****************************************************
 * 4/12/2020
 * ICSI 333
 * Project 3: Minesweeper
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/******************************************************
                Functions Declarations
*******************************************************/
void createGameBoard();
void printGameBoard();
void printRealBoard();
void createMines();
int nearByMines();
int revealCells();
void flagCell();
void removeFlag();


/******************************************************
                Global Variables
*******************************************************/
int height,width;
char **gameBoard;
char **realBoard;

int main(int argc, char *argv[]){
   
    height = atoi(argv[1]);
    width = atoi(argv[2]);

   gameBoard = malloc(height * sizeof(char*));
   
   for (int i = 0; i < height; i++){
       gameBoard[i] = malloc(width*sizeof(char));
   }
   
   realBoard = malloc(height * sizeof(char*));
   
   for (int i = 0; i < height; i++){
       realBoard[i] = malloc(width*sizeof(char));
   }

  int runGame = 1;
  int x,y;
  char userInput;

  createGameBoard();
  createMines();
  printGameBoard();

/*************************************************************************************
 * Ask the user which command they would like to prefer. If the user chooses to flag
 * a spot as a mine, input the coordinates and set the flag to ^ indicating it has been
 * flagged. The user can also remove the flag. If the user chooses to assert a spot is
 * mine free, if the input coordinates are not a mine(*), recursively reveal spots on
 * the gameBoard. If a mine has been found, print the realBoard and terminate the game.
 * 
 * **********************************************************************************/
  while(runGame == 1){
     
    printf("(F) flag a spot as a mine, (R) remove a flag, (A) assert that a spot is mine free, (Q)uit) \n");
    scanf("%c",&userInput);

    if(userInput == 'F' || userInput == 'f'){
      printf("ENTER HORIZONTAL COORDINATE: \n");
      scanf("%d",&x);
      
      printf("Enter VERTICAL COORDINATE: \n");
      scanf("%d",&y);
      flagCell(x,y);
      printGameBoard();
    }
        
    if(userInput == 'A' || userInput == 'a'){
            
      printf("ENTER HORIZONTAL COORDINATE: \n");
      scanf("%d",&x);
      
      printf("Enter VERTICAL COORDINATE: \n");
      scanf("%d",&y);
        
      if(realBoard[x][y]=='*'){
        printf("GAME OVER!\n");
        printRealBoard();
        runGame = 0;
      }
      else{
        revealCells(x,y);
        printGameBoard();
       }
    }

    if(userInput == 'R' || userInput == 'r'){
      removeFlag(x,y);
      printGameBoard();
    }

    if (userInput == 'Q' || userInput == 'q')
    {
      runGame = 0;
    } 
  }
   printf("END GAME\n");
   free(realBoard);
   free(gameBoard);
   
   return 0;
}

void createGameBoard(){
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gameBoard[i][j] = '#';
        }
        puts(" ");    
    } 
}

//gameboard for user to see during game play
void printGameBoard(){
    for (int i = 0; i < height; i++)
    {
       for (int j = 0; j < width; j++)
       {
           printf("%c ",gameBoard[i][j]);
       }
        puts(" ");   
    }
}

//internal board that contains mine positions
void printRealBoard(){
    for (int i = 0; i <height; i++)
    {
       for (int j = 0; j < width; j++)
       {
           printf("%c ",realBoard[i][j]);
       }
        puts(" ");   
    }
}

void createMines(){
    for (int i = 0; i < height; i++)
    {
        for ( int j = 0; j < width; j++)
        {
            realBoard[i][j] = '#';
        }
    }

    srand(time(0));
    for (int i = 0; i < height; i++)
    {
        int randomPosition = rand() % height;
        realBoard[randomPosition][i] = '*';
    }
}


/******************************************
 * Check top, bottom, left, right cells for
 * mines
 *                  | 
 *              --- # ---
 *                  |
 ******************************************/

int nearByMines(int x, int y){

    int minesCounter = 0;
    if(realBoard[x+1][y] == '*'){
        minesCounter++;
    }
    if (realBoard[x][y+1] == '*')
    {
        minesCounter++;
    }
    if (realBoard[x-1][y] == '*')
    {
        minesCounter++;
    }
    if (realBoard[x][y-1] == '*')
    {
        minesCounter++;
    }
    return minesCounter;
}

/********************************************
 * Take an x and y coordinate from the user
 * and set that position on the user gameBoard
 * to ^ to indicate a flag has been placed
 * 
 * *******************************************/

void flagCell(int x, int y){
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      gameBoard[x][y] = '^';
    } 
  }
}

void removeFlag(int x, int y){
  if(gameBoard[x][y] == '^'){
    gameBoard[x][y] = '#';
  }
}


/*************************************************************************************
 * Base Case:
 * First we must check if the user entered x and y coordinates are valid by making sure
 * they are greater than 0 and they are less than the defined height and width of the
 * board
 * Recursion: 
 * In order to reveal the cells, we must first check how many mines are near the user
 * entered cell. After calculating the number of mines, the cells are set # if no mines 
 * if there are no mines around the cell, reveal the cells: 
 *                  | 
 *              --- # ---
 *                  |
 * stop once checkMines >= 1
 * ***********************************************************************************/

int revealCells(int x, int y){
    int checkMines=0;
    if((x < 0 || x >= height) || (y < 0 || y >= width) || (gameBoard[x][y] != '#')){
        return 0;
    }
    else{
      checkMines = nearByMines(x,y);
      gameBoard[x][y] = '>';                         
      if(checkMines < 1){
        revealCells(x+1,y);
        revealCells(x,y+1);
        revealCells(x-1,y);
        revealCells(x,y-1);
      }
    }
    return 1;
}

