#include "Menu.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Menu *menu = new Menu();
    int selection = menu->mainMenu();

    string player1;
    string player2;
    if (selection == 1)
    {
        player1 = menu->selectPlayer1();
        player2 = menu->selectPlayer2();

        // FOR TESTING ONLY!
        cout << player1 << endl;
        cout << player2 << endl;
    }

    return 0;
}
