#include "SnakeGlobal.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <algorithm>

#include "Snake.h"
#include "Food.h"

using namespace std;

Snake snake({ WIDTH / 3, HEIGHT / 2 }, 1);
Food food;
HANDLE hConsole;
bool bMovingLR = true;

void board()
{
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1) cout << "#";
            else if (i == snake_pos.Y && j == snake_pos.X) cout << "O";
            else if (snake.bIsBodyPartAtPos({ (SHORT)j, (SHORT)i })) cout << "o";
            else if (i == food_pos.Y && j == food_pos.X) cout << "*";
            else cout << " ";
        }
        cout << "#\n";
    }
}

int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 800, 800, TRUE); // 800 width, 800 height

    srand(time(NULL));

    int score = 0;

    int startingSpeed = 250;
    int currentSpeed;

    bool game_over = false;

    while (!game_over)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

        board();
        if (_kbhit())
        {
            switch (_getch())
            {
                case 'w': if(bMovingLR) snake.change_dir('u');
                    bMovingLR = false;
                    break;

                case 's': if(bMovingLR) snake.change_dir('d');
                    bMovingLR = false;
                    break;

                case 'a': if(!bMovingLR) snake.change_dir('l');
                    bMovingLR = true;
                    break;

                case 'd': if(!bMovingLR) snake.change_dir('r');
                    bMovingLR = true;
                    break;
            }
        }
        snake.move_snake();

        if (snake.eaten(food.get_pos()))
        {
            // food.gen_food();
            while (snake.bIsBodyPartAtPos(food.get_pos()) || (food.get_pos().X == snake.get_pos().X && food.get_pos().Y == snake.get_pos().Y))
            {
                food.gen_food();
            }
            snake.grow();
            score++;
        }

        if (snake.collided())
        {
            game_over = true;

            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { snake.get_pos().X + 16, snake.get_pos().Y });
            cout << "X";

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, HEIGHT + 2 });
            cout << "\t\tScore: " << score << endl;
        }

        currentSpeed = std::clamp(startingSpeed - (score * 10), 100, startingSpeed);

        Sleep(currentSpeed);
    }
}