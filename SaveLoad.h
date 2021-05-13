#include "Board.h"
#include "Player.h"
#include "LinkedList.h"
#include "GameModel.h"

#include <string>

#define NUM_PLAYERS 2

class SaveLoad
{
private:
    GameModel* gameModelPtr;

public:
    SaveLoad();
    ~SaveLoad();
    bool save(Board board, std::string fileName, Player* player1, Player* player2, TileBag* tileBag, std::string currentPlayer);

    bool load(std::string filePath);
    bool loadFile(std::ifstream& input);



    Player getPlayer1() const;
    Player getPlayer2() const;

    Board getLoadedBoard();
    LinkedList getLoadedTileBag();
    std::string getCurrentPlayer();
};