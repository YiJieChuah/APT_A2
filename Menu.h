#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H
#include <string>

class Menu {
public:
    Menu();
    void mainMenu();

    std::string selectPlayer1();
    std::string selectPlayer2();
    // TODO: We are no longer using cin for file input
    // std::string createFileDir();
    bool loadFile(std::string filePath);

    void printCredits();
};

#endif //ASSIGN2_MENU_H