class Snake
{
private:
    /* data */
public:
    int DIRECTION;
    // DIRECTIONS :
    // 1 = UP
    // 2 = RIGHT
    // 3 = DOWN
    // 4 = LEFT
    int X, Y;
    Snake(int x, int y);
};

Snake::Snake(int x, int y)
{
    X = x;
    Y = y;

}
