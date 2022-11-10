#pragma once

#define LENGTH 3
#define MAX 10

class TicTacToe {
    /*
        board     : (O, X)를 각각 (1, -1)로 대응하여 저장하는 2차원 배열.
        turn      : 현재 턴을 저장하는 int 변수.
        player    : 현재 플레이어를 저장하는 char 변수.
        condition : 게임의 상태를 저장하는 bool 변수.
    */
    int board[LENGTH][LENGTH] = { 0 };
    int turn = 0;
    char player = '\0';
    bool condition = true;

public:
    /*
        [함수 설명]
        commands     : showMenu()에서 사용할 열거형 자료형.
        showMenu()   : 커맨드를 입력하는 메뉴를 호출하는 함수.
        showHelp()   : 프로그램에서 커맨드의 설명을 출력하는 함수.
        showStatus() : 게임의 현재 보드판, 상태를 출력하는 함수.
        checkGame()  : 게임의 승리를 검사하여 bool*로 반환하는 함수.
        playGame()   : 행과 열을 입력하여 게임을 진행하는 함수.
        replayGame() : 게임을 초기화하는 함수.
        exitGame()   : 게임을 종료하는 함수.
    */
    enum commands;
    void showMenu();
    void showHelp();
    void showStatus(int board[][LENGTH], bool* condition, char* player, int* turn);
    bool* checkWinn(int* sumOne, int* sumTwo);
    bool* checkGame(int board[][LENGTH], bool* condition, int* col, int* row);
    char* playGame(int board[][LENGTH], bool* condition, char* player, int* turn);
    void replayGame(int board[][LENGTH], bool* condition, char* player, int* turn);
    void exitGame();
};