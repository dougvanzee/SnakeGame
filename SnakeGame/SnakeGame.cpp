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
bool bMovingLR = true; // Used to keep user from having snake turn 180 degrees back on itself.

void draw_board()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // reset cursor to beginning of console

    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    // Draw loop
    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#"; // Tab over and draw first wall in row
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1) cout << "#"; // Draw wall
            else if (i == snake_pos.Y && j == snake_pos.X) cout << "O"; // Draw snake head
            else if (snake.bIsBodyPartAtPos({ (SHORT)j, (SHORT)i })) cout << "o"; // Draw snake body part
            else if (i == food_pos.Y && j == food_pos.X) cout << "*"; // Draw food
            else cout << " "; // Draw empty space on board 
        }
        cout << "#\n"; // Draw last wall in row and go to next line
    }
}

int main()
{
    // resize console window
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, 800, 800, TRUE); // 800 width, 800 height

    srand(time(NULL));

    int score = 0;

    int startingSpeed = 250;
    int currentSpeed;

    bool game_over = false;

    // Main loop of game
    while (!game_over)
    {
        draw_board();

        if (_kbhit()) // Detect keyboard input
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
            // Get random position of food that isn't overlapping with snake
            while (snake.bIsBodyPartAtPos(food.get_pos()) || (food.get_pos().X == snake.get_pos().X && food.get_pos().Y == snake.get_pos().Y))
            {
                food.gen_food();
            }
            snake.grow();
            score++;
        }

        if (snake.collided()) // Snake collides with wall or own body
        {
            game_over = true;

            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Change console text color to red
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { snake.get_pos().X + 16, snake.get_pos().Y }); // Move cursor to "approximate" collision position
            cout << "X"; // Draw red X where collision was detected

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, HEIGHT + 2 }); // Move cursor to below the game board
            cout << "\t\tScore: " << score << endl; // Draw final score
        }

        currentSpeed = std::clamp(startingSpeed - (score * 10), 100, startingSpeed); // Increase speed each time food is eaten.

        Sleep(currentSpeed); // Creates game speed
    }
}