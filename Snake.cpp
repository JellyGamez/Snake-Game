#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
pair<int,int> tail[626];
int x[25][25],fruitLine,fruitColumn,headX,headY,length,score,highscore,speed=75;
const int dim=25;
char aux,printChar[4]= {' ','o','O','*'};
bool gameOver,start;
void generateRandom()
{
    srand(time(0));
    fruitLine=rand()%dim;
    fruitColumn=rand()%dim;
    while (x[fruitLine][fruitColumn])
    {
        fruitLine=rand()%dim;
        fruitColumn=rand()%dim;
    }
    x[fruitLine][fruitColumn]=3;
}
char opposite(char x)
{
    switch(x)
    {
    case 'w':
        return 's';
    case 'a':
        return 'd';
    case 's':
        return 'w';
    case 'd':
        return 'a';
    }
}
void ClearScreen()
{
    COORD cursorPosition;
    cursorPosition.X=cursorPosition.Y=0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void printGame()
{
    for (int i=0; i<dim+2; i++)
        cout<<"# ";
    cout<<'\n';
    for (int i=0; i<dim; i++)
    {
        cout<<"# ";
        for (int j=0; j<dim; j++)
        {
            cout<<printChar[x[i][j]]<<' ';
        }
        cout<<"#";
        switch (i)
        {
        case 7:
            cout<<"             Change the snake speed - c";
            break;
        case 8:
            cout<<"             New game - n";
            break;
        case 9:
            cout<<"             Quit - q";
            break;
        case 11:
            cout<<"             Up - w";
            break;
        case 12:
            cout<<"             Down - s";
            break;
        case 13:
            cout<<"             Left - a";
            break;
        case 14:
            cout<<"             Right - d";
            break;
        case 16:
            cout<<"             Score - "<<score;
            break;
        case 17:
            cout<<"             Highscore - "<<highscore;
        }
        cout<<'\n';
    }
    for (int i=0; i<dim+2; i++)
        cout<<"# ";
    Sleep(speed);
    ClearScreen();
}
void newGame()
{
    ClearScreen();
    headX=12;
    headY=6;
    length=4;
    for (int i=0; i<25; i++)
    {
        for (int j=0; j<25; j++)
            x[i][j]=0;
    }
    score=start=0;
    aux=' ';
    tail[0]=make_pair(headX,headY);
    for (int i=1; i<length; i++)
    {
        tail[i]=make_pair(headX,headY-i);
        x[tail[i].first][tail[i].second]=1;
    }
    x[headX][headY]=2;
    generateRandom();
}
void control(char x)
{
    switch(x)
    {
    case 'w':
        headX--;
        break;
    case 'a':
        headY--;
        break;
    case 's':
        headX++;
        break;
    case 'd':
        headY++;
        break;
    }
}
void continueMovement()
{
    x[tail[length-1].first][tail[length-1].second]=0;
    for (int i=length; i>=0; i--)
        tail[i]=tail[i-1];
    tail[0]=make_pair(headX,headY);
    x[tail[0].first][tail[0].second]=2;
    x[tail[1].first][tail[1].second]=1;
}
void eatApple()
{
    x[tail[length].first][tail[length].second]=1;
    length++;
    score++;
    generateRandom();
}
void hitWall()
{
    if (headX<0||headX==25||headY<0||headY==25)
        gameOver=1;
}
void hitBody()
{
    for (int i=1; i<length-1; i++)
        if (tail[i].first==headX&&tail[i].second==headY)
        {
            gameOver=1;
            break;
        }
}
int main()
{
    newGame();
    while (1)
    {
        if (x[fruitLine][fruitColumn]==2)
            eatApple();
        printGame();
        if (_kbhit())
        {
            char x=_getch();
            switch(x)
            {
            case 'n':
                if (score>highscore)
                    highscore=score;
                newGame();
                system("cls");
                continue;
            case 'q':
                system("cls");
                return 0;
            case 'c':
            {
                system("cls");
                cout<<"Enter a new value for the time between screen updates (in milliseconds) : ";
                cin>>speed;
                system("cls");
                continue;
            }
            }
            if (!start&&x!='s'&&x!='d'&&x!='w')
                continue;
            if (x!='a'&&x!='w'&&x!='s'&&x!='d')
            {
                control(aux);
            }
            else if (x!=opposite(aux))
            {
                control(x);
                aux=x;
            }
            else
                control(aux);
            if (!start)
                start=1;
        }
        else
            control(aux);
        hitWall();
        hitBody();
        if (gameOver)
        {
            system("cls");
            cout<<"Game Over!\n";
            if (score>highscore)
            {
                highscore=score;
                cout<<"New highscore - "<<score;
            }
            else
                cout<<"Score - "<<score;
            cout<<"\nStarting new game";
            gameOver=0;
            Sleep(500);
            for (int i=0; i<3; i++)
            {
                cout<<'.';
                Sleep(500);
            }
            newGame();
        }
        if (start)
            continueMovement();
    }
}
