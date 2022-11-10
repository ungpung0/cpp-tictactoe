#include <iostream>
#include <Windows.h>
#include "TicTacToe.h"

enum TicTacToe::commands {
    COMMAND_HELP = 1,
    COMMAND_PLAY,
    COMMAND_STAT,
    COMMAND_REPLAY,
    COMMAND_EXIT
};

void TicTacToe::showHelp() {
    system("cls");
    std::cout << "[커맨드 설명]\n" << std::endl;
    std::cout << "1 :: 커맨드에 대한 설명을 보여줍니다.\n" << std::endl;
    std::cout << "2 :: 행과 열을 입력하여 게임을 진행합니다.\n" << std::endl;
    std::cout << "3 :: 현재 게임의 상황을 출력합니다.\n" << std::endl;
    std::cout << "4 :: 현재 게임을 초기화합니다.\n" << std::endl;
    std::cout << "5 :: 틱택토 게임을 종료합니다." << std::endl;
}

bool* TicTacToe::checkWinn(int* sumOne, int* sumTwo) {
    if (abs(*sumOne) == 3 || abs(*sumTwo) == 3)
        return (bool*) false;
    else
        return (bool*) true;
}

bool* TicTacToe::checkGame(int board[][LENGTH], bool* condition, int* col, int* row) {
    int sumOne = 0;
    int sumTwo = 0;

    // 가로/세로 체크.
    for (int i = 0; i < LENGTH; i++) {
        sumOne += board[*col][i];
        sumTwo += board[i][*row];
        if (abs(sumOne) == 3 || abs(sumTwo) == 3)
            *condition = false;
    }
    if (*condition == false) {
        return condition;
    }

    // 정대각/역대각 체크.
    if ((*col + *row) % 2 == 0) {
        sumOne = 0, sumTwo = 0;
        for (int i = 0; i < LENGTH; i++) {
            sumOne += board[i][i];
            sumTwo += board[i][(LENGTH - 1) - i];
            if (abs(sumOne) == 3 || abs(sumTwo) == 3)
                *condition = false;
        }
    }

    return condition;
}

void TicTacToe::showStatus(int board[][LENGTH], bool* condition, char* player) {
    system("cls");
    std::cout << "[현재 보드판]" << std::endl;
    std::cout << "   [0][1][2]" << std::endl;

    for (int i = 0; i < LENGTH; i++) {
        std::cout << "[" << i << "]";
        for (int j : board[i]) {
            if (j == 1)
                std::cout << "[O]";
            else if (j == -1)
                std::cout << "[X]";
            else
                std::cout << "[ ]";
        }
        std::cout << std::endl;
    }

    std::cout << "\n[게임 상태]" << std::endl;

    if (*condition == true) {
        std::cout << "게임이 아직 진행중입니다." << std::endl;
    }
    else {
        if (*player == '\0')
            std::cout << "게임이 무승부로 끝났습니다." << std::endl;
        else
            std::cout << *player << " 의 승리로 게임이 끝났습니다.";
    }
}

char* TicTacToe::playGame(int board[][LENGTH], bool* condition, char* player, int* turn) {
    system("cls");
    TicTacToe::showStatus(board, condition, player);

    if (*turn == 0) {
        while (true) {
            std::cout << "\n선공 플레이어를 입력해주세요. ('O', 'X')" << std::endl;
            std::cout << "플레이어 > ";
            std::cin >> player;

            if (*player == 'O' || *player == 'X') {
                std::cout << *player << " 의 선공으로 게임을 시작합니다." << std::endl;
                *turn = *turn + 1;
                *condition = true;
                break;
            }
            else {
                std::cout << "잘못된 플레이어를 입력했습니다." << std::endl;
            }
        }
    }

    if (*condition == true) {
        std::cout << "\n" << *player << " 의 차례입니다." << std::endl;

        while (true) {
            int col = -1, row = -1;
            std::cout << "행과 열을 입력하세요." << std::endl;
            std::cout << "행 > ";
            std::cin >> col;
            std::cout << "열 > ";
            std::cin >> row;

            if (col >= LENGTH || row >= LENGTH) {
                std::cout << "잘못된 인덱스 입니다." << std::endl;
                continue;
            }
            else if (board[col][row] != 0) {
                std::cout << "점유된 인덱스 입니다." << std::endl;
                continue;
            }
            else {
                *turn = *turn + 1;
                board[col][row] = (*player == 'O') ? 1 : -1;
                condition = TicTacToe::checkGame(board, condition, &col, &row);
                *player = (*player == 'O' && *condition == true) ? 'X' : 'O';
                
                if (*turn == MAX) {
                    *condition = false;
                    *player = '\0';
                }
                break;
            }
        }
    }
    else {
        std::cout << " 게임을 재시작 하세요." << std::endl;
    }

    return player;
}



void TicTacToe::replayGame(int board[][LENGTH], bool* condition, char* player, int* turn) {
    system("cls");
    std::cout << "[게임 초기화]" << std::endl;
    std::cout << "게임을 초기화하겠습니까? (Y, N)" << std::endl;

    while (true) {
        std::cout << "입력 > ";
        char answer = '\0';
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            for (int i = 0; i < LENGTH; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    board[i][j] = 0;
                }
            }

            *player = '\0';
            *turn = 0;
            *condition = true;

            std::cout << "초기화가 끝났습니다." << std::endl;
            break;
        }
        else if (answer == 'n' || answer == 'N') {
            std::cout << "초기화하지 않습니다." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 문자 입니다. 다시 입력하세요.\n" << std::endl;
            continue;
        }
    }
}


void TicTacToe::exitGame() {
    system("cls");
    std::cout << "게임을 종료합니다. 재미있게 즐기셨나요? ;)";
}

void TicTacToe::showMenu() {
    system("cls");
    std::cout << "=============================================" << std::endl;
    std::cout << "//           LETS PLAY TICTACTOE!          //" << std::endl;
    std::cout << "//           Created By juwon              //" << std::endl;
    std::cout << "//                      Input '1' to HELP. //" << std::endl;
    std::cout << "=============================================" << std::endl;

    while (true) {
        int command;
        std::cout << "\n커맨드 > ";
        std::cin >> command;

        if (command == COMMAND_HELP) {
            TicTacToe::showHelp();
            continue;
        }
        else if (command == COMMAND_PLAY) {
            TicTacToe::playGame(board, &condition, &player, &turn);
            continue;
        }
        else if (command == COMMAND_STAT) {
            TicTacToe::showStatus(board, &condition, &player);
            continue;
        }
        else if (command == COMMAND_REPLAY) {
            TicTacToe::replayGame(board, &condition, &player, &turn);
            continue;
        }
        else if (command == COMMAND_EXIT) {
            TicTacToe::exitGame();
            break;
        }
        else {
            std::cout << "잘못된 번호 입니다. 다시 입력하세요." << std::endl;
            continue;
        }
    }
}