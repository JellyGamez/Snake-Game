#include <bits/stdc++.h>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define print printf
#define scan scanf
#define refresh()
#define endwin()
#else
#include <unistd.h>
#include <ncurses.h>
#define print printw
#define scan scanw
#endif
using namespace std;
pair<int, int> tail[626];
int x[25][25], fruitLine, fruitColumn, headX, headY, length, score, highscore, speed = 75;
const int dim = 25;
char aux, printChar[4] = {' ', 'o', 'O', '*'};
bool gameOver, start;
#ifndef _WIN32
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif
void sleep(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}
int readnumber()
{
    int ans = 0;
#ifndef _WIN32
    nodelay(stdscr, FALSE);
    echo();
#endif

    char x[2000];
    do
    {
        print("Enter a new value for the time between screen updates (in milliseconds) : ");
        refresh();
        scan("%s", x);
        ans = strtol(x, NULL, 10);
        if (ans <= 0)
            print("Invalid input.\n");
    } while (ans <= 0);

#ifndef _WIN32
    noecho();
    nodelay(stdscr, TRUE);
#endif
    return ans;
}
void generateRandom()
{
    srand(time(0));
    fruitLine = rand() % dim;
    fruitColumn = rand() % dim;
    while (x[fruitLine][fruitColumn])
    {
        fruitLine = rand() % dim;
        fruitColumn = rand() % dim;
    }
    x[fruitLine][fruitColumn] = 3;
}
char opposite(char x)
{
    switch (x)
    {
    default:
        return ' ';
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
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    clear();
    refresh();
#endif
}
void reposition()
{
#ifdef _WIN32
    COORD cursorPosition;
    cursorPosition.X = cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
#else
    move(0, 0);
#endif
}
void printGame()
{
    print("\n\n");
    print("  ");
    for (int i = 0; i < dim + 2; i++)
        print("# ");
    print("\n");
    for (int i = 0; i < dim; i++)
    {
        print("  # ");
        for (int j = 0; j < dim; j++)
        {
            print("%c ", printChar[x[i][j]]);
        }
        print("#");
        switch (i)
        {
        case 7:
            print("          Change the snake speed - c");
            break;
        case 8:
            print("          New game - n");
            break;
        case 9:
            print("          Quit - q");
            break;
        case 11:
            print("          Up - w");
            break;
        case 12:
            print("          Down - s");
            break;
        case 13:
            print("          Left - a");
            break;
        case 14:
            print("          Right - d");
            break;
        case 16:
            print("          Score - %d", score);
            break;
        case 17:
            print("          Highscore - %d", highscore);
        }
        print("\n");
    }
    print("  ");
    for (int i = 0; i < dim + 2; i++)
        print("# ");
    sleep(speed);
    reposition();
}
void newGame()
{
    clearScreen();
    headX = 12;
    headY = 6;
    length = 4;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
            x[i][j] = 0;
    }
    score = start = 0;
    aux = ' ';
    tail[0] = make_pair(headX, headY);
    for (int i = 1; i < length; i++)
    {
        tail[i] = make_pair(headX, headY - i);
        x[tail[i].first][tail[i].second] = 1;
    }
    x[headX][headY] = 2;
    generateRandom();
}
void control(char x)
{
    switch (x)
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
    x[tail[length - 1].first][tail[length - 1].second] = 0;
    for (int i = length; i >= 0; i--)
        tail[i] = tail[i - 1];
    tail[0] = make_pair(headX, headY);
    x[tail[0].first][tail[0].second] = 2;
    x[tail[1].first][tail[1].second] = 1;
}
void eatApple()
{
    x[tail[length].first][tail[length].second] = 1;
    length++;
    score++;
    generateRandom();
}
void hitWall()
{
    if (headX < 0 || headX == 25 || headY < 0 || headY == 25)
        gameOver = 1;
}
void hitBody()
{
    for (int i = 1; i < length - 1; i++)
        if (tail[i].first == headX && tail[i].second == headY)
        {
            gameOver = 1;
            break;
        }
}
int main()
{
#ifndef _WIN32
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
#endif
    newGame();
    while (1)
    {
        if (x[fruitLine][fruitColumn] == 2)
            eatApple();
        printGame();
        if (kbhit())
        {
            char x = getch();
            switch (x)
            {
            case 'n':
                if (score > highscore)
                    highscore = score;
                newGame();
                clearScreen();
                continue;
            case 'q':
                clearScreen();
                endwin();
                return 0;
            case 'c':
            {
                clearScreen();
                speed = readnumber();
                clearScreen();
                continue;
            }
            }
            if (!start && x != 's' && x != 'd' && x != 'w')
                continue;
            if (x != 'a' && x != 'w' && x != 's' && x != 'd')
            {
                control(aux);
            }
            else if (x != opposite(aux))
            {
                control(x);
                aux = x;
            }
            else
                control(aux);
            if (!start)
                start = 1;
        }
        else
            control(aux);
        hitWall();
        hitBody();
        if (gameOver)
        {
            clearScreen();
            print("Game Over!\n");
            if (score > highscore)
            {
                highscore = score;
                print("New highscore - %d", score);
            }
            else
                print("Score - %d", score);
            print("\nStarting new game");
            refresh();
            gameOver = 0;
            sleep(500);
            for (int i = 0; i < 3; i++)
            {
                print(".");
                refresh();
                sleep(500);
            }
            newGame();
        }
        if (start)
            continueMovement();
    }
    endwin();
    return 0;
}
