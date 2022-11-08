#include <iostream>
#include <windows.h>

#define LENGTH 3
#define MAX 9

void showMenu();
void showHelp();
void showGame(int board[][LENGTH], bool* condition, char* player);
bool* checkCondition(int board[][LENGTH], int* col, int* row, bool* condition);
char* playGame(int board[][LENGTH], bool* condition, char* player, int* turn);
void replay(int board[][LENGTH], char* player, int *turn);
void exitGame();

int main() {
    showMenu();
    return 0;
}

enum commands {
    COMMAND_HELP,
    COMMAND_PLAY,
    COMMAND_DISPLAY,
    COMMAND_REPLAY,
    COMMAND_EXIT
};

void showMenu() {
    std::cout << "=============================================" << std::endl;
    std::cout << "//           LETS PLAY TICTACTOE!          //" << std::endl;
    std::cout << "//           Created By juwon              //" << std::endl;
    std::cout << "//                      Input '0' to HELP. //" << std::endl;
    std::cout << "=============================================" << std::endl;

    int board[LENGTH][LENGTH] = {0};
    int turn = 1;
    char player = 'O';
    bool condition = true;

    while(true) {
        int command;
        std::cout << "Ŀ�ǵ� > ";
        std::cin >> command;

        switch(command) {
            case COMMAND_HELP:
                showHelp();
                continue;
            case COMMAND_PLAY:
                player = *playGame(board, &condition, &player, &turn);
                continue;
            case COMMAND_DISPLAY:
                showGame(board, &condition, &player);
                continue;
            case COMMAND_REPLAY:
                replay(board, &player, &turn);
                continue;
            case COMMAND_EXIT:
                exitGame();
                break;
            default:
                std::cout << "(����) �߸��� ��ȣ �Դϴ�." << std::endl;
                continue;
        }
    }
}

void showHelp() {
    system("cls");
    std::cout << "[��ɾ� ���� �޴�]" << std::endl;
    std::cout << "0 :: ��ɾ ���� ������ �����ݴϴ�." << std::endl;
    std::cout << "1 :: ƽ���信 ��� ���� �Է��մϴ�." << std::endl;
    std::cout << "2 :: ������ ��Ȳ�� �����ݴϴ�." << std::endl;
    std::cout << "3 :: ������ �ʱ�ȭ �մϴ�." << std::endl;
    std::cout << "4 :: ������ �����մϴ�." << std::endl;
}

bool* checkCondition(int board[][LENGTH], int* col, int* row, bool* condition) {
    int sumOne = 0;
    int sumTwo = 0;

    // ����/���� üũ.
    for(int i = 0; i < LENGTH; i++) {
        sumOne += board[*col][i];
        sumTwo += board[i][*row];
        if(abs(sumOne) == 3 || abs(sumTwo) == 3)
            *condition = false;
    }

    // ���밢/���밢 üũ.
    if((*col + *row) % 2 == 0) {
        for(int i = 0; i < LENGTH; i++) {
            sumOne += board[i][i];
            sumTwo += board[i][(LENGTH - 1) - i];
            if(abs(sumOne) == 3 || abs(sumTwo) == 3)
               *condition = false;
        }
    }

    return condition;
}

char* playGame(int board[][LENGTH], bool* condition, char* player, int* turn) {
    system("cls");
    showGame(board, condition, player);

    if(*condition == true) {
        std::cout << std::endl << player << " �� �����Դϴ�." << std::endl;
        int col = -1, row = -1;
        std::cout << "��� ���� �Է����ּ���." << std::endl;
        std::cout << "�� > ";
        std::cin >> col;
        std::cout << "�� > ";
        std::cin >> row;

        if(col >= LENGTH || row >= LENGTH) {
            std::cout << "(����) �߸��� �ε��� �Դϴ�.";
        }
        else if(board[col][row] != 0) {
            std::cout << "(����) ������ �ε��� �Դϴ�.";
        }
        else {
            *turn = *turn + 1;
            board[col][row] = (*player == 'O') ? 1 : -1;
            condition = checkCondition(board, &col, &row, condition);
            if(*condition == true)
                *player = (*player == 'O') ? 'X' : 'O';
            else if(*turn == MAX)
                *player = '\0';
            return player;
        }
    }
    else {
        std::cout << "������ ���� �����Դϴ�.";
        return player;
    }
}

void showGame(int board[][LENGTH], bool* condition, char* player) {
    system("cls");
    std::cout << "[���� ������]" << std::endl;
    std::cout << "   (0)(1)(2)" << std::endl;

    for(int i = 0; i < LENGTH; i++) {
        std::cout << "(" << i << ")";
        for(int j : board[i]) {
            if(j == 1)
                std::cout << "(O)";
            else if(j == -1)
                std::cout << "(X)";
            else
                std::cout << "(*)";
        }
        std::cout << std::endl;
    }

    if(*condition == true) {
        std::cout << "������ ���� �������Դϴ�.";
    }else {
        if(*player == '\0')
            std::cout << "������ ���ºη� �������ϴ�." << std::endl;
        else
            std::cout << *player << " �� �¸��� ������ �������ϴ�.";
    }
}

void replay(int board[][LENGTH], char* player, int *turn, bool* condition) {
    system("cls");
    std::cout << "������ �ʱ�ȭ �մϴ�." << std::endl;

    for(int i = 0; i < LENGTH; i++) {
        for(int j = 0; j < LENGTH; j++) {
            board[i][j] = 0;
        }
    }
    *player = 'O';
    *turn = 1;
    *condition = true;

    std::cout << "�ʱ�ȭ�� �������ϴ�." << std::endl;
}

void exitGame() {
    system("cls");
    std::cout << "������ �����մϴ�.";
}