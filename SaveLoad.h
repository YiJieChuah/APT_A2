#include "Board.h"
#include "Player.h"
#include <string>

class SaveLoad
{

public:
    SaveLoad();
    ~SaveLoad();
    bool save(Board board, std::string fileName, Player player1, Player player2);
    bool load(std::string fileName);
};