#include <iostream>
#include <string>

class View
{

public:
    View();
    ~View();
    void init();
    bool validateMenuInput(int input);
    void processInput();
    std::string selectPlayer1();
    std::string selectPlayer2();
    std::string createFileDir();
    void printCredits();
};