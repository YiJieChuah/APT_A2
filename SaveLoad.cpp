#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>

#include "Board.h"
#include "Player.h"
#include "SaveLoad.h"

SaveLoad::SaveLoad(GameModel* gameModelPtr)
{
    this->gameModelPtr = gameModelPtr;
}

SaveLoad::~SaveLoad() {}


bool SaveLoad::save(std::string fileName) 
{
    bool saved = false;
    // saves in the old file format if the number of players is 2
    if (gameModelPtr->getNumPlayers() > 2){
        saved = newSave(fileName);
    }else{
        saved = oldSave(fileName);
    }

    return saved;
}

/**
 * Takes input from vaious places and puts it all into one .save file.
 * @return True if save was successful, otherwise false.
 */
bool SaveLoad::newSave(std::string fileName)
{
    bool saved = false;
    // Opens or creates the file.
    std::ofstream saveFile("saves/" + fileName + ".save");

    // Checking if the file was opened.
    if (saveFile.is_open())
    {
        // First line will indicate number of players
        saveFile << "<new>" << std::endl;
        saveFile << gameModelPtr->getNumPlayers() << std::endl;

        // Inserting player details.
        for (Player* player : gameModelPtr->getPlayers()) {
            saveFile << player->getName() << std::endl;
            saveFile << player->getScore() << std::endl;
            saveFile << player->handToString() << std::endl;
        }

        // Inserting board details.
        Board* board = gameModelPtr->getBoard();
        saveFile << board->getBoardDimensions() << "," << board->getBoardDimensions() << std::endl;
        saveFile << board->getSaveFormat() << std::endl;
        board = nullptr;

        TileBag* tileBag = gameModelPtr->getTileBag();
        for (int i = 0; i < tileBag->getTiles()->size(); i++)
        {
            saveFile << tileBag->getTiles()->get(i)->colour;
            saveFile << tileBag->getTiles()->get(i)->shape;
            if (i != tileBag->getTiles()->size() - 1)
            {
                saveFile << ",";
            }
        }
        tileBag = nullptr;

        saveFile << std::endl;

        saveFile << gameModelPtr->getCurrentPlayerName() << std::endl;
        saveFile.close();
        saved = true;
    }
    return saved;
}

bool SaveLoad::oldSave(std::string fileName)
{
    Player* player1 = gameModelPtr->getPlayers()[0];
    Player* player2 = gameModelPtr->getPlayers()[1];
    Board* board = gameModelPtr->getBoard();
    TileBag* tileBag = gameModelPtr->getTileBag();

    bool saved = false;
    try
    {
        std::ofstream saveFile("saves/" + fileName + ".save");

        // Checking if the file was opened.
        if (saveFile.is_open())
        {
            // Inserting player details.
            saveFile << player1->getName() << std::endl;
            saveFile << player1->getScore() << std::endl;
            saveFile << player1->handToString() << std::endl;

            saveFile << player2->getName() << std::endl;
            saveFile << player2->getScore() << std::endl;
            saveFile << player2->handToString() << std::endl;

            // Inserting board details.
            saveFile << board->getBoardDimensions() << "," << board->getBoardDimensions() << std::endl;
            saveFile << board->getSaveFormat() << std::endl;

            for (int i = 0; i < tileBag->getTiles()->size(); i++)
            {
                saveFile << tileBag->getTiles()->get(i)->colour;
                saveFile << tileBag->getTiles()->get(i)->shape;
                if (i != tileBag->getTiles()->size() - 1)
                {
                    saveFile << ",";
                }
            }

            saveFile << std::endl;

            saveFile << gameModelPtr->getCurrentPlayerName() << std::endl;
            saveFile.close();
            saved = true;
        }
        else
        {
            throw "Error saving file!";
        }
    }
    catch(const char* msg)
    {
        std::cout << msg << std::endl;
    }

    //cleanup. no delete called because SaveLoad does not own any of GameModel's objects
    player1 = nullptr;
    player2 = nullptr;
    board = nullptr;
    tileBag = nullptr;

    return saved;
}

bool SaveLoad::load(std::string filePath)
{
    bool loaded = false;

    std::ifstream file(filePath);
    std::cin.ignore();

    if (!file) {
        if (!std::cin.eof()) {
            std::cout << "No Such File." << std::endl;
        }
    }
    else {
        bool isNewFormat = false;
        std::string line;
        if (!getline(file, line).eof()){
            if (line == "<new>"){
                isNewFormat = true;
            }
        }

        if (isNewFormat){
            if (newLoadFile(file)) {
                std::cout << "File Loaded!" << std::endl;
                loaded = true;
            }
            else {
                std::cout << "Error loading file" << std::endl;
            }
        }
        else{
            if (oldLoadFile(file, line)) {
                std::cout << "File Loaded!" << std::endl;
                loaded = true;
            }
            else {
                std::cout << "Error loading file" << std::endl;
            }
        }
        
    }

    file.close();
    return loaded;
}

bool SaveLoad::newLoadFile(std::ifstream& input) {
    bool loaded = false;

    std::string line;
    int readIdx = 0;
    int numPlayers = 0;

    //Reading in first line for number of players
    if (!getline(input, line).eof()) {
        try {
            numPlayers = std::stoi(line);
        }
        catch (std::invalid_argument& e) {
            // if no conversion could be done
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Error occured while reading in number of players"
                << std::endl;
        }
        ++readIdx;
    }

    for (int i = 0; i < numPlayers; i++)
    {
        Player player;
        int playerLineRead = 0;
        while (playerLineRead <= 2) {
            getline(input, line);
            if (playerLineRead == 0) {
                player.setName(line);
            }
            else if (playerLineRead == 1) {
                player.setScore(stoi(line));
            }
            else {
                std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
                player.setHand(initTiles(tilesStr));
                gameModelPtr->addPlayerToGame(new Player(player));
            }
            ++playerLineRead;
        }
        // Increments everytime a player is added to the game
        ++readIdx;
    }

    // Reading the rest of the file
    while (!getline(input, line).eof())
    {
        if (readIdx == 1 + numPlayers) {
            //Supposed to handle board dimensions
            //They are fixed at 26 for base gameplay so placeholder for now
        }
        else if (readIdx == 2 + numPlayers) {
            std::vector<std::string> tokens = splitByDelimiter(line, ',');

            for (std::string token : tokens) {
                std::vector<std::string> tileLocInfo = splitByDelimiter(token, '@');

                //trim
                tileLocInfo[0].erase(0, tileLocInfo[0].find_first_not_of(' '));
                std::string tileStr = tileLocInfo[0];
                std::string tileLocStr = tileLocInfo[1];

                int posX = std::stoi(tileLocStr.substr(1, tileLocStr.size()));
                int posY = tileLocStr[0] - 'A';

                Tile* tile = strToTile(tileStr);
                gameModelPtr->getBoard()->addTileForLoad(*tile, posX, posY);
                delete tile;
            }
        }
        else if (readIdx == 3 + numPlayers) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            gameModelPtr->setTileBag(initTiles(tilesStr));

        }
        else if (readIdx == 4 + numPlayers)
        {
            gameModelPtr->setCurrentPlayer(line);
            loaded = true;
        }
        ++readIdx;
    }
    return loaded;
}

bool SaveLoad::oldLoadFile(std::ifstream& input, std::string firstLine) {
    bool loaded = false;
    std::string line;
    int lineNum = 1;
    Player player1;
    Player player2;

    // necessary because to check if the file is old/new, first line has to already be read in
    player1.setName(firstLine);

    while (!getline(input, line).eof())
    {
        //Cnotinue player 1 Load
        if (lineNum == 1) {
            player1.setScore(stoi(line));
        }
        else if (lineNum == 2) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            player1.setHand(initTiles(tilesStr));
            gameModelPtr->addPlayerToGame(new Player(player1));
        }

        //Player 2 Load
        else if (lineNum == 3) {
            player2.setName(line);
        }
        else if (lineNum == 4) {
            player2.setScore(stoi(line));
        }
        else if (lineNum == 5) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            // LinkedList* hand = initHand(tilesStr);
            player2.setHand(initTiles(tilesStr));
            // hand = nullptr;

            gameModelPtr->addPlayerToGame(new Player(player2));
        }

        else if (lineNum == 6) {
            //Supposed to handle board dimensions
            //They are fixed at 26 for base gameplay so placeholder for now
        }
        else if (lineNum == 7) {
            std::vector<std::string> tokens = splitByDelimiter(line, ',');

            for (std::string token : tokens) {
                std::vector<std::string> tileLocInfo = splitByDelimiter(token, '@');

                //trim
                tileLocInfo[0].erase(0, tileLocInfo[0].find_first_not_of(' '));
                std::string tileStr = tileLocInfo[0];
                std::string tileLocStr = tileLocInfo[1];

                int posX = std::stoi(tileLocStr.substr(1, tileLocStr.size()));
                int posY = tileLocStr[0] - 'A';

                Tile* tile = strToTile(tileStr);
                gameModelPtr->getBoard()->addTileForLoad(*tile, posX, posY);
                delete tile;
            }
        }
        else if (lineNum == 8) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            gameModelPtr->setTileBag(initTiles(tilesStr));

        }
        else if (lineNum == 9)
        {
            gameModelPtr->setCurrentPlayer(line);
            loaded = true;
        }
        ++lineNum;
    }
    return loaded;
}


std::vector<std::string> SaveLoad::splitByDelimiter(const std::string& line,
    char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


LinkedList* SaveLoad::initTiles(std::vector<std::string> tilesStr) {
    LinkedList* tiles = new LinkedList();
    for (std::string tileStr : tilesStr) {
        tiles->add_back(strToTile(tileStr));
    }
    return tiles;
}


Tile* SaveLoad::strToTile(std::string tileStr) {
    Colour colour = tileStr[0];
    std::string shapeStr = tileStr.substr(1, tileStr.size());
    Shape shape = stoi(shapeStr);
    return new Tile(colour, shape);
}