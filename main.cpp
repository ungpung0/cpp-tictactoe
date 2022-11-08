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
        std::cout << "커맨드 > ";
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
                std::cout << "(에러) 잘못된 번호 입니다." << std::endl;
                continue;
        }
    }
}

void showHelp() {
    system("cls");
    std::cout << "[명령어 헬프 메뉴]" << std::endl;
    std::cout << "0 :: 명령어에 대한 설명을 보여줍니다." << std::endl;
    std::cout << "1 :: 틱택토에 행과 열을 입력합니다." << std::endl;
    std::cout << "2 :: 게임의 상황을 보여줍니다." << std::endl;
    std::cout << "3 :: 게임을 초기화 합니다." << std::endl;
    std::cout << "4 :: 게임을 종료합니다." << std::endl;
}

bool* checkCondition(int board[][LENGTH], int* col, int* row, bool* condition) {
    int sumOne = 0;
    int sumTwo = 0;

    // 가로/세로 체크.
    for(int i = 0; i < LENGTH; i++) {
        sumOne += board[*col][i];
        sumTwo += board[i][*row];
        if(abs(sumOne) == 3 || abs(sumTwo) == 3)
            *condition = false;
    }

    // 정대각/역대각 체크.
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
        std::cout << std::endl << player << " 의 차례입니다." << std::endl;
        int col = -1, row = -1;
        std::cout << "행과 열을 입력해주세요." << std::endl;
        std::cout << "행 > ";
        std::cin >> col;
        std::cout << "열 > ";
        std::cin >> row;

        if(col >= LENGTH || row >= LENGTH) {
            std::cout << "(에러) 잘못된 인덱스 입니다.";
        }
        else if(board[col][row] != 0) {
            std::cout << "(에러) 점유된 인덱스 입니다.";
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
        std::cout << "게임이 끝난 상태입니다.";
        return player;
    }
}

void showGame(int board[][LENGTH], bool* condition, char* player) {
    system("cls");
    std::cout << "[현재 보드판]" << std::endl;
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
        std::cout << "게임이 아직 진행중입니다.";
    }else {
        if(*player == '\0')
            std::cout << "게임이 무승부로 끝났습니다." << std::endl;
        else
            std::cout << *player << " 의 승리로 게임이 끝났습니다.";
    }
}

void replay(int board[][LENGTH], char* player, int *turn, bool* condition) {
    system("cls");
    std::cout << "게임을 초기화 합니다." << std::endl;

    for(int i = 0; i < LENGTH; i++) {
        for(int j = 0; j < LENGTH; j++) {
            board[i][j] = 0;
        }
    }
    *player = 'O';
    *turn = 1;
    *condition = true;

    std::cout << "초기화가 끝났습니다." << std::endl;
}

void exitGame() {
    system("cls");
    std::cout << "게임을 종료합니다.";
}