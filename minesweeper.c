#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<unistd.h>
int number;
int bomb;
void welcomenote()
{
    char str[11]="MINESWEEPER";
    int i,j;
    printf("\n\n\n\n");
    for(i=0;i<11;i++)
    {
        printf("\t\t\t\t");
        printf("| %c 💥|\n",str[i]);
        usleep(200000);
        
    }
    system("clear"); 
}
void move(int *x, int *y) 
{ 
    printf("\n\n\t\t\t\t(ROW , COLUMN) :  "); 
    scanf("%d %d",x,y);
    return; 
}
int validity(int row, int col) 
{ 
    return (row >= 0) && (row < number) && (col >= 0) && (col < number); 
} 
int blast (int row, int col, char board[][25]) 
{ 
    if (board[row][col] == 'X') 
        return 1; 
    else
        return 0; 
} 
void printBoard(char user[][25]) 
{ 
    int i, j; 
    printf ("\n\n    \t\t\t\t"); 
    for (i=0; i<number; i++) 
       {
         printf ("%d ", i); 
       }
    printf ("\t\n\n"); 
    for (i=0; i<number; i++) 
    { 
        printf ("\t\t\t%d   ", i); 
        printf("    ");
        for (j=0; j<number; j++)
        {
            printf ("%c ", user[i][j]); 
        }
        printf ("\n"); 
    } 
} 
  
int Adjbomb(int row, int col, int mines[][2],  char original[][25]) 
{ 
    int i; 
    int c=0; 
        if (validity(row-1, col) == 1) 
        { 
               if (blast (row-1, col, original) == 1) 
               c++; 
        } 
        if (validity(row+1, col) == 1) 
        { 
               if (blast (row+1, col, original) == 1) 
               c++; 
        }
        if (validity(row, col+1) == 1) 
        { 
            if (blast (row, col+1, original) == 1) 
               c++; 
        } 
        if (validity(row, col-1) == 1) 
        { 
               if (blast (row, col-1,original) == 1) 
               c++; 
        } 
        if (validity(row-1, col+1) == 1) 
        { 
            if (blast (row-1, col+1,original) == 1) 
               c++; 
        } 
        if (validity(row-1, col-1) == 1) 
        { 
             if (blast (row-1, col-1,original) == 1) 
               c++; 
        } 
        if (validity(row+1, col+1) == 1) 
        { 
               if (blast (row+1, col+1,original) == 1) 
               c++; 
        } 
        if (validity(row+1, col-1) == 1) 
        { 
            if (blast (row+1, col-1, original) == 1) 
               c++; 
        } 
  return c; 
} 
int Minesweeper(char user[][25], char original[][25],int mines[][2], int row, int col, int *direction) 
{ 
    if (user[row][col] != '-') 
        return 0; 
    int i, j; 
    if (original[row][col] == 'X') 
    { 
        user[row][col]='X'; 
        for (i=0; i<bomb; i++) 
            user[mines[i][0]][mines[i][1]]='X'; 
  
        printBoard (user); 
        printf ("\n\t\t\t\tB.O.M.B BLAST💥! You lost!\n"); 
        return 1 ; 
    } 
    else
     { 
        int count = Adjbomb(row, col, mines, original); 
        (*direction)--; 
  
        user[row][col] = count + '0'; 
  
        if (!count) 
        { 
            if (validity(row-1, col) == 1) 
            { 
                   if (blast (row-1, col, original) == 0) 
                   Minesweeper(user, original, mines, row-1, col, direction); 
            }
            if (validity(row+1, col) == 1) 
            { 
                   if (blast (row+1, col, original) == 0) 
                    Minesweeper(user, original, mines, row+1, col, direction); 
            } 
            if (validity(row, col+1) == 1) 
            { 
                if (blast (row, col+1, original) == 0) 
                    Minesweeper(user, original, mines, row, col+1, direction); 
            } 
            if (validity(row, col-1) == 1) 
            { 
                   if (blast (row, col-1, original) == 0) 
                    Minesweeper(user, original, mines, row, col-1, direction); 
            } 
            if (validity(row-1, col+1) == 1) 
            { 
                if (blast (row-1, col+1, original) == 0) 
                    Minesweeper(user, original, mines, row-1, col+1, direction); 
            }
            if (validity(row-1, col-1) == 1) 
            { 
                 if (blast (row-1, col-1, original) == 0) 
                    Minesweeper(user, original, mines, row-1, col-1, direction); 
            } 
            if (validity(row+1, col+1) == 1) 
            { 
                 if (blast (row+1, col+1, original) == 0) 
                    Minesweeper(user, original, mines, row+1, col+1, direction); 
            } 
            if (validity(row+1, col-1) == 1) 
            { 
                if (blast (row+1, col-1, original) == 0) 
                    Minesweeper(user, original, mines, row+1, col-1, direction); 
            } 
        } 
      return 0; 
    } 
} 
void position(int mines[][2], char original[][25]) 
{ 
    int arr[625]; 
    memset (arr, 0, 625); 
    for (int i=0; i<bomb; ) 
     { 
        int random = rand() % (number*number); 
        int x = random / number; 
        int y = random % number; 
        if (arr[random] == 0) 
        { 
            mines[i][0]= x; 
            mines[i][1] = y; 
            original[mines[i][0]][mines[i][1]] = 'X'; 
            arr[random] = 1; 
            i++; 
        } 
    } 
  
    return; 
} 
void initialise(char original[][25], char user[][25]) 
{ 
    srand(time (NULL)); 
    for (int i=0; i<number; i++) 
    { 
        for (int j=0; j<number; j++) 
        { 
            user[i][j] = original[i][j] = '-'; 
        } 
    } 
  
    return; 
} 
void change(int row, int col, char board[][25]) 
{ 
    for (int i=0; i<number; i++) 
    { 
        for (int j=0; j<number; j++) 
            { 
    
                if (board[i][j] != 'X') 
                { 
                    board[i][j] = 'X'; 
                    board[row][col] = '-'; 
                    return; 
                } 
            } 
    } 
    return; 
} 
void play () 
{ 
    int finish = 0; 
    char original[25][25], user[25][25]; 
  
    int direction= number* number - bomb, x, y; 
    int mines[99][2]; 
  
    initialise (original, user); 
    position(mines, original); 
  
    int k= 0; 
    while (finish == 0) 
     { 
        system("clear"); 
        printBoard (user); 
        move(&x, &y); 
  
         
        if (k == 0) 
        { 
            
            if (blast (x, y, original) == 1) 
                change(x, y, original); 
        } 
  
        k++; 
  
        finish = Minesweeper(user, original, mines, x, y, &direction); 
  
        if ((finish == 0) && (direction == 0)) 
         { 
            printf ("\n\t\t\t\tCONGRATULATIONS You won !\n"); 
            finish = 1; 
         } 
    } 
    return; 
} 
  

void Level () 
{ 
    int level;
    printf("\n\n\n");
    printf ("\t\t\t\tL.E.V.E.L.S\n"); 
    printf ("\t\t\t\tCLICK '1' if you are SMART (8 X 8)\n"); 
    printf ("\t\t\t\tCLICK '2' if you are SMARTER (16 X 16)\n"); 
    printf ("\t\t\t\tCLICK '3' if you are SMARTEST (24 X 24)\n"); 
    scanf ("\t\t\t\t%d", &level); 
    switch(level)
    {
        case 1:
          number = 8; 
          bomb = 10; 
          break;
        case 2:
          number = 16; 
          bomb = 40;
          break;
        case 3:
          number = 20; 
          bomb = 99;
          break;
    }
} 
int main() 
{ 
    welcomenote();
    Level(); 
    system("clear");
    play(); 
    return (0); 
}