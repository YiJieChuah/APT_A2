#include "Board.h"
#include "Player.h"
#include "LinkedList.h"
#include <string>

class SaveLoad
{
private:
    Board board;

    Player loadedPlayer1;
    Player loadedPlayer2;

    LinkedList loadedTileBag;
    std::string currentPlayer;

public:
    SaveLoad();
    ~SaveLoad();
    bool save(Board board, std::string fileName, Player player1, Player player2, LinkedList tileBag, std::string currentPlayer);
    bool load(std::string fileName);
    std::string createTileString(LinkedList list);

    Player getPlayer1();
    Player getPlayer2();

    Board getLoadedBoard();
    LinkedList getLoadedTileBag();
    std::string getCurrentPlayer();
};