
#include "Board.h"

#include <iostream>
#include <string>
#include <memory>

Board::Board()
{
    // Adding empty tiles to a 2d vector that reperesents the board.
    for (int row = 0; row < BOARD_DIMENSIONS; row++)
    {
        std::vector<Tile> boardRow(BOARD_DIMENSIONS, Tile());
        board.push_back(boardRow);
    }
}


Board::~Board() {}

/**
 * There cannot be duplicate tiles in a line.
 * Minimum number of point a player can score is 2.
 */
void Board::addTile(Tile tile, int posX, int posY)
{
    try {
        if (tileIsValid(tile, posX, posY))
        {
            board[posY][posX] = tile;
            std::cout << "Score : " << calculateScore(posX, posY) << std::endl;;
        }
        else {
            throw "Invalid tile placement. Try another.";
        }
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
    }
}

Tile Board::getTile(int row, int col)
{
    Tile tile = board[row][col];
    return tile;
}

int Board::getTile(Tile)
{
    return 0;
}

bool Board::tileIsValid(Tile tileToAdd, int posX, int posY) {
    bool isValid = true;

    // Keep original tile for later reset
    Tile origTile = board[posY][posX];

    Tile currTile = origTile;
    // Check if position already has a tile
    if (!currTile.isEmpty()) {
        isValid = false;
    }

    //temporary tile addition to accomodate for validation
    board[posY][posX] = tileToAdd;

    std::vector<Tile> vertLine = getLine(posX, posY, true);
    if (vertLine.size() > 1) {
        if (checkLineForDuplicates(vertLine) ||
            !(hasMatchingAttr(vertLine, tileToAdd))) {
            isValid = false;
        }
    }

    std::vector<Tile> horiLine = getLine(posX, posY, false);
    if (horiLine.size() > 1) {
        if (checkLineForDuplicates(horiLine) ||
            !(hasMatchingAttr(horiLine, tileToAdd))) {
            isValid = false;
        }
    }
    //Reset tile after validations are done
    board[posY][posX] = origTile;
    return isValid;
}

Tile Board::getTileNeighbour(int posX, int posY, Direction dir) {
    Tile neighbour;

    if ((dir == NORTH) && (posY != 0)) {
        neighbour = board[posY - 1][posX];
    }
    else if ((dir == EAST) && (posX != BOARD_DIMENSIONS - 1)) {
        neighbour = board[posY][posX + 1];
    }
    else if ((dir == SOUTH) && (posY != BOARD_DIMENSIONS - 1)) {
        neighbour = board[posY + 1][posX];
    }
    else if ((dir == WEST) && (posX != 0)) {
        neighbour = board[posY][posX - 1];
    }

    return neighbour;
}

std::vector<Tile> Board::getLine(int posX, int posY, bool checkVert) {
    std::vector<Tile> line(0);
    Tile currTile = board[posY][posX];

    //Gets the vector by traversing north and then adding as it goes down.
    if (checkVert) {
        int currPosY = posY;
        while (!getTileNeighbour(posX, currPosY, NORTH).isEmpty()) {
            --currPosY;
            currTile = board[currPosY][posX];
        }
        while (!currTile.isEmpty()) {
            line.push_back(currTile);
            ++currPosY;
            currTile = board[currPosY][posX];
        }
    }
    else {
        int currPosX = posX;
        while (!getTileNeighbour(currPosX, posY, WEST).isEmpty()) {
            --currPosX;
            currTile = board[posY][currPosX];
        }
        while (!currTile.isEmpty()) {
            line.push_back(currTile);
            ++currPosX;
            currTile = board[posY][currPosX];
        }

    }
    return line;
}

bool Board::checkLineForDuplicates(std::vector<Tile> line) {
    bool dupsExist = false;

    for (unsigned int i = 0; i < line.size(); i++) {
        Tile currTile = line[i];
        for (unsigned int j = i + 1; j < line.size(); j++) {
            if (currTile.equals(line[j])) {
                dupsExist = true;
            }
        }
    }

    return dupsExist;
};


bool Board::hasMatchingAttr(std::vector<Tile> line, Tile tileToCheck) {
    bool isMatching = true;

    for (Tile tile : line) {
        //Cannot compare againts a duplicate
        if (!tileToCheck.equals(tile)) {
            if (tile.colour != tileToCheck.colour &&
                tile.shape != tileToCheck.shape)
            {
                isMatching = false;
            }
        }
    }
    return isMatching;

}

int Board::calculateScore(int posX, int posY) {
    Tile addedTile = board[posY][posX];
    int totalScore = 0;

    std::vector<Tile> vertLine = getLine(posX, posY, true);
    std::vector<Tile> horiLine = getLine(posX, posY, false);

    if (vertLine.size() > 1) {
        totalScore += vertLine.size();
    }
    if (horiLine.size() > 1) {
        totalScore += horiLine.size();
    }

    return totalScore;
};



void Board::printBoard()
{
    std::cout << "   ";
    // Printing the column numbers.
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        if (i > 9)
        {
            std::cout << i << " ";
        }
        else
        {
            std::cout << i << "  ";
        }
    }
    std::cout << std::endl
        << "  -";

    // Printing the line below the comlumn numbers.
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        std::cout << "---";
    }
    std::cout << std::endl;


    char alphabet = 'A';
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        //iterate through alphabets by adding to char
        std::cout << alphabet++ << " |";
        for (int j = 0; j < BOARD_DIMENSIONS; j++)
        {
            // If the tile is a exists, print it, otherwise print an empty space.
            if (!board[i][j].isEmpty())
            {
                std::cout << board[i][j].toString() << "|";
            }
            else
            {
                std::cout << "  |";
            }
        }
        std::cout << std::endl;
    }
}
