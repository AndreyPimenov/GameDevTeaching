/*
В этом коде программы представлена простая реализация игры «Змейка».
Игрок управляет змейкой, используя клавиши W (вверх), A (влево), S (вниз) и D (вправо), и должен съесть как можно больше фруктов,
чтобы увеличить свой счет. Если змейка ударяется об стену или свой собственный хвост, игра заканчивается.
Программа также добавляет небольшую задержку между обновлениями экрана, чтобы сделать игру более плавной.

*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>

using namespace std;

const int width = 13;
const int height = 13;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool GameOver = false;

void Setup()
{
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    //system("pause");
    system("cls"); // использование команды cls для очистки экрана
    cout << "Score: " << score << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
}

void Input()
{
    if (_kbhit()) // если клавиша была нажата
    {
        switch (_getch()) // получение клавишы
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            GameOver = true;
        }
                
    
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!GameOver)//(dir != STOP)
    {
        Draw();
        Input();
        Logic();
        Sleep(240); // добавить чуть-чуть задержки
    }
    return 0;
}
