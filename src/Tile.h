#include <raylib.h>
class Tile
{
private:
    /* data */
public:
    Color tileColor;
    bool isSnake;
    bool isFood;
    int XY;
    Tile(Color tileColor = WHITE, int XY = 200, bool isSnake = false, bool isFood = false);
};
