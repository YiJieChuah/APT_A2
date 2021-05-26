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

    std::vector<std::string> splitByDelimiter(const std::string& line,
        char delimiter);

public:
    SaveLoad(GameModel* gameModelPtr);
    ~SaveLoad();

    bool save(std::string fileName);
    bool newSave(std::string fileName);
    bool oldSave(std::string fileName);

    LinkedList* initTiles(std::vector<std::string> tilesStr);
    Tile* strToTile(std::string tile);

    bool load(std::string filePath);

    bool newLoadFile(std::ifstream& input);
    bool oldLoadFile(std::ifstream& input, std::string firstLine);

};