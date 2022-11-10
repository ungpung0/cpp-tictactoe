#pragma once

#define LENGTH 3
#define MAX 10

class TicTacToe {
    /*
        board     : (O, X)�� ���� (1, -1)�� �����Ͽ� �����ϴ� 2���� �迭.
        turn      : ���� ���� �����ϴ� int ����.
        player    : ���� �÷��̾ �����ϴ� char ����.
        condition : ������ ���¸� �����ϴ� bool ����.
    */
    int board[LENGTH][LENGTH] = { 0 };
    int turn = 0;
    char player = '\0';
    bool condition = true;

public:
    /*
        [�Լ� ����]
        commands     : showMenu()���� ����� ������ �ڷ���.
        showMenu()   : Ŀ�ǵ带 �Է��ϴ� �޴��� ȣ���ϴ� �Լ�.
        showHelp()   : ���α׷����� Ŀ�ǵ��� ������ ����ϴ� �Լ�.
        showStatus() : ������ ���� ������, ���¸� ����ϴ� �Լ�.
        checkGame()  : ������ �¸��� �˻��Ͽ� bool*�� ��ȯ�ϴ� �Լ�.
        playGame()   : ��� ���� �Է��Ͽ� ������ �����ϴ� �Լ�.
        replayGame() : ������ �ʱ�ȭ�ϴ� �Լ�.
        exitGame()   : ������ �����ϴ� �Լ�.
    */
    enum commands;
    void showMenu();
    void showHelp();
    void showStatus(int board[][LENGTH], bool* condition, char* player);
    bool* checkWinn(int* sumOne, int* sumTwo);
    bool* checkGame(int board[][LENGTH], bool* condition, int* col, int* row);
    char* playGame(int board[][LENGTH], bool* condition, char* player, int* turn);
    void replayGame(int board[][LENGTH], bool* condition, char* player, int* turn);
    void exitGame();
};