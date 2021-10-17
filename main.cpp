#include <iostream>
#include <cstring>
using namespace std;

int index1;
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //the positions on the board

int is_full() //check if the board is full
{
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X')
            if (board[i] != 'O')
                return 0;
    return 1;
}

/*
This function verify who is the winner of the game.
- the first player_won verify if the human being won;
- the second one pc_won verify if the CPU won
*/
char is_winning(char player, char pc)
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == player))
            return player;
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == pc))
            return pc;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == player))
            return player;
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == pc))
            return pc;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == player))
    {
        return player;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == pc))
    {
        return pc;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == player))
    {
        return player;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == pc))
    {
        return pc;
    }
    return '\0';
}

// Print the TIC-TAC-TOE board
void draw_board()
{
    cout << endl;
    cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
    cout << "-----" << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
    cout << "-----" << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
}

// Minimax algorithm for the game mode 1vPC
int minimax(bool flag, char player, char pc)
{

    int max_val = -1000, min_val = 1000;
    int i, j, value = 1;
    if (is_winning(player, pc) == pc)
    {
        return 10;
    }
    else if (is_winning(player, pc) == player)
    {
        return -10;
    }
    else if (is_full() == 1)
    {
        return 0;
    }
    int score[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; //if score[i]=1 then it is empty

    for (i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            if (min_val > max_val) // reverse of pruning condition
            {
                if (flag == true)
                {
                    board[i] = pc;
                    value = minimax(false, player, pc);
                }
                else
                {
                    board[i] = player;
                    value = minimax(true, player, pc);
                }
                board[i] = ' ';
                score[i] = value;
            }
        }
    }

    if (flag == true)
    {
        max_val = -1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] > max_val && score[j] != 1)
            {
                max_val = score[j];
                index1 = j;
            }
        }
        return max_val;
    }
    if (flag == false)
    {
        min_val = 1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] < min_val && score[j] != 1)
            {
                min_val = score[j];
                index1 = j;
            }
        }
        return min_val;
    }
}

int main()
{
    int move, choice;
    cout << "-------------------------TIC TAC TOE----------------------------------------\n";
    cout << "Choosing the game mode\n Type 1v1 or 1vPC:\n";
    char s[10];
    gets(s);
    if (strcmp(s, "1vPC") == 0)
    {
        cout << "The first to move is X. If you want to be the first, type 1. Else type 2\n";
        cin >> choice;
        char player, pc;
        if (choice == 1)
        {
            player = 'X';
            pc = 'O';
        }
        else
        {
            player = 'O';
            pc = 'X';
        }

        if (choice == 1)
        {
            draw_board();
        up:
            cout << endl
                 << "Enter the move:";
            cin >> move;
            if (board[move - 1] == ' ')
            {
                board[move - 1] = player;
                draw_board();
            }
            else
            {
                cout << endl
                     << "Invalid Move......Try different move";
                goto up;
            }
        }

        while (true)
        {

            cout << endl
                 << "CPU MOVE....";
            minimax(true, player, pc);
            board[index1] = pc;
            draw_board();
            if (is_winning(player, pc) == pc)
            {
                cout << endl
                     << "CPU WON.....";
                break;
            }
            if (is_full() == 1)
            {
                cout << endl
                     << "Draw....";
                break;
            }
        again:
            cout << endl
                 << "Enter the move:";
            cin >> move;
            if (board[move - 1] == ' ')
            {
                board[move - 1] = player;
                draw_board();
            }
            else
            {
                cout << endl
                     << "Invalid Move......Try different move";
                goto again;
            }
            if (is_winning(player, pc) == player)
            {
                cout << endl
                     << "You Won......";
                break;
            }
            if (is_full() == 1)
            {
                cout << endl
                     << "Draw....";
                break;
            }
        }
    }
    else if (strcmp(s, "1v1") == 0)
    {
        cout << "Player 1 - X\nPlayer 2 - O";
        char player_1 = 'X', player_2 = 'O';
        while (true)
        {
            draw_board();
        again1:
            cout << endl
                 << "First player move:";
            cin >> move;
            if (board[move - 1] == ' ')
            {
                board[move - 1] = player_1;
                draw_board();
            }
            else
            {
                cout << endl
                     << "Invalid Move......Try different move";
                goto again1;
            }
            if (is_winning(player_1, player_2) == player_1)
            {
                cout << endl
                     << "PLAYER 1 WON.....";
                break;
            }
            if (is_full() == 1)
            {
                cout << endl
                     << "Draw....";
                break;
            }
        again2:
            cout << endl
                 << "Second player move:";
            cin >> move;
            if (board[move - 1] == ' ')
            {
                board[move - 1] = player_2;
                draw_board();
            }
            else
            {
                cout << endl
                     << "Invalid Move......Try different move";
                goto again2;
            }
            if (is_winning(player_1, player_2) == player_2)
            {
                cout << endl
                     << "PLAYER 2 Won......";
                break;
            }
            if (is_full() == 1)
            {
                cout << endl
                     << "Draw....";
                break;
            }
        }
    }
}
