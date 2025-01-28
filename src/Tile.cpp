#include "Tile.h"

Tile::Tile(Color TileColor, int xy, bool IsSnake, bool IsFood){
    tileColor = TileColor;
    XY = xy;
    isSnake = IsSnake;
    isFood = IsFood;
}