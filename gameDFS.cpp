#include<bits/stdc++.h>
#include<istream>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 //(25*25-99)

int SIDE,MINES;
vector<vector<int>>flag;

// TO CHECK IF A MINE IS PLACED THERE OR NOT
bool isMine(int row,int col, char board[][MAXSIDE])
{
  if(board[row][col]=='*')
    return true;
  else
    return false;
}

//TO CHECK IF A ROW OR COL LIES WITHIN THE GIVEN CHOSEN ARENA
bool isValid(int row,int col)
{
  return (row>=0)&&(row<SIDE)&&(col>=0)&&(col<SIDE);
}

//ASKING THE USER TO CHOOSE THE DIFFICULTY LEVEL AND SETTING THE FLAGS OF THE CHOSEN CELLS AS -1.
void chooseDifficultyLevel(){
  int level;
  cout<<"Enter the difficulty level"<<endl;
  cout<<"Press 0 for BEGINNER"<<endl;
  cout<<"Press 1 for INTERMEDIATE"<<endl;
  cout<<"Press 2 for ADVANCED"<<endl;
  cin>>level;
  if(level==BEGINNER)
  {
    SIDE=9;MINES=10;
  }
  if(level==INTERMEDIATE)
  {
    SIDE=16;MINES=40;
  }
  if(level==ADVANCED)
  {
    SIDE=24;MINES=99;
  }
for(int i=0;i<SIDE;i++)
{
    vector<int>v1;
    for(int j=0;j<SIDE;j++)
   {
    v1.push_back(-1);
   }
   flag.push_back(v1);
}

  return;
}

//TO DISPLAY THE USER BOARD AS '-' BEFORE HIS FIRST MOVE
void initialise(char realBoard[][MAXSIDE],char myBoard[][MAXSIDE])
{
  srand(time(NULL));
  for(int i=0;i<SIDE;i++)
  {
    for(int j=0;j<SIDE;j++)
    {
      myBoard[i][j]=realBoard[i][j]='-';
    }
  }
}

//PLACING RANDOM MINES ON THE BOARD
void placeMines(int mines[][2],char realBoard[][MAXSIDE]){
  bool mark[MAXSIDE*MAXSIDE];
  memset(mark,false,sizeof(mark));

  //Creating random mines
  for(int i=0;i<MINES;)
  {
    int random=rand()%(SIDE*SIDE);
    int x= random/SIDE;
    int y= random%SIDE;
//Add the mine if no mine is placed at this position on the board
    if(mark[random]==false)
    {
      mines[i][0]=x;
      mines[i][1]=y;

      realBoard[mines[i][0]][mines[i][1]]='*';
      mark[random]=true;
      i++;
    }
  }
  return;
}

//TO DISPLAY THE USER BOARD
void printBoard(char realBoard[][MAXSIDE])
{
  cout<<"  ";
  for(int i=0;i<SIDE;i++)
  cout<<i<<" ";
  cout<<endl;
  for(int i=0;i<SIDE;i++)
  {
    cout<<i<<" ";
    for (int j=0;j<SIDE;j++)
    cout<<realBoard[i][j]<<" ";

    cout<<endl;
  }
}

//THIS FUNCTION DISPLAYS THE PLACED MINES(A CHEATSHEET :))
void cheatMinesweeper(char realBoard[][MAXSIDE])
{
   cout<<"the mines location are"<<endl;
    printBoard(realBoard);
    return;
}

//COUNTS THE NUMBER OF MINES IN THE 8 ADJACENT BLOCKS OF THE MINE
int countAdjacentMines(int row,int col,int mines[][2],char realBoard[][MAXSIDE])
{
  int i;
  int count=0;

  if(isValid(row-1,col)==true)
  {
    if(isMine(row-1,col,realBoard)==true)
    count++;
  }
  if(isValid(row+1,col)==true)
  {
    if(isMine(row+1,col,realBoard)==true)
    count++;
  }
  if(isValid(row,col+1)==true)
  {
    if(isMine(row,col+1,realBoard)==true)
    count++;
  }
  if(isValid(row,col-1)==true)
  {
    if(isMine(row,col-1,realBoard)==true)
    count++;
  }
  if(isValid(row-1,col+1)==true)
  {
    if(isMine(row-1,col+1,realBoard)==true)
    count++;
  }
  if(isValid(row-1,col-1)==true)
  {
    if(isMine(row-1,col-1,realBoard)==true)
    count++;
  }
  if(isValid(row+1,col+1)==true)
  {
    if(isMine(row+1,col+1,realBoard)==true)
    count++;
  }
  if(isValid(row+1,col-1)==true)
  {
    if(isMine(row+1,col-1,realBoard)==true)
    count++;
  }
  return count;
}

//ASKING THE USER TO INPUT HIS MOVE
void makeMove(int *x, int *y)
{
  cout<<"Enter your move, (row,column)->"<<endl;
  cin>> *x >> *y;
}

/*THIS IS A "CONNECTED COMPONENT GRAPH USING DFS" APPROACH
  IF A BLOCK IS SELECTED BY THE USER SET ITS FLAG AS 1
  ITERATE OVER THE ADJACENT BLOCKS OF THE SELECTED MINE
  KEEP ON ITERATING TILL YOU THERE IS 0 ADJACENT MINES
  WHEN MORE THAN 1 ADJACENT MINE IS PRESENT DISPLAY IT AND STOP ITERATING FURTHER FOR THAT BLOCK
   */
int DFS(char myBoard[][MAXSIDE],char realBoard[][MAXSIDE],int row,int col,int count,int mines[][2])
{
    if(isValid(row,col))
    {
        if(flag[row][col]==-1 && isMine(row,col,realBoard)==false)
       {
        count++;
        flag[row][col]=1;
        //myBoard[row][col]='1';
        int adjacentMines=countAdjacentMines(row,col,mines,realBoard);
        if(adjacentMines==0)
        {
        myBoard[row][col]=adjacentMines+'0';
        DFS(myBoard,realBoard,row-1,col,count,mines);
        DFS(myBoard,realBoard,row,col-1,count,mines);
        DFS(myBoard,realBoard,row,col+1,count,mines);
        DFS(myBoard,realBoard,row+1,col,count,mines);
        }
        else
            myBoard[row][col]=adjacentMines+'0';
       }
    }
    return count;
}

//THIS FUNCTION CHECKS IF A USER HAS SELECTED A MINE OR A DFS APPROCAH HAS TO BE IMPLEMENTED
//IF THE USER SELECTS A RIGHT BLOCK THEN CALL DFS FUNCTION
bool playMinesweeperUtil(char myBoard[][MAXSIDE],char realBoard[][MAXSIDE],int mines[][2],int row,int col,int *movesLeft)
{
  if(myBoard[row][col]!='-')
  return(false);

  int i,j;

  if(realBoard[row][col]=='*')
  {
    myBoard[row][col]='*';

    for(i=0;i<MINES;i++)
    myBoard[mines[i][0]][mines[i][1]]='*';

    printBoard(myBoard);
    cout<<"You Lost"<<endl;
    return(true);
  }
  else
  {
    int count=0;
    int movesCompleted=DFS(myBoard,realBoard,row,col,count,mines);
    movesLeft-=movesCompleted;
    return false;
  }
}



void playMinesweeper(){
  bool gameOver=false;
  char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
  int movesLeft= SIDE * SIDE - MINES,x,y;
  int mines[MAXMINES][2];

  initialise(realBoard,myBoard);

  placeMines(mines,realBoard);

  cheatMinesweeper(realBoard);


  while(gameOver==false)
  {
    cout<<"Current status of board"<<endl;
    printBoard(myBoard);
    makeMove(&x,&y);

    gameOver=playMinesweeperUtil(myBoard,realBoard,mines,x,y,&movesLeft);

    if((gameOver==false)&&(movesLeft==0))
    {
      cout<<"You won!"<<endl;
      gameOver=true;
    }
  }
}



int main(){
  chooseDifficultyLevel();
  playMinesweeper();
  return (0);
}
