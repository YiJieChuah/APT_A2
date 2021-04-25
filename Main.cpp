#include "Menu.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Menu *menu = new Menu();
    int selection = menu->mainMenu();

    cout << selection << endl;

    return 0;
}
