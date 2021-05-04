#include "Menu.cpp"

#include "Board.cpp"

using namespace std;

int main(int argc, char const *argv[])
{

    Board *board1 = new Board();

    board1->printBoard();

    Menu *menu = new Menu();
    menu->mainMenu();

    return 0;
}
