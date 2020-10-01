#ifndef POSITION_H
#define POSITION_H

struct Position {
        int row, col;
        Position()
        {
                row = col = 0;
        }
        Position(int r, int c)
        {
                row = r;
                col = c;
        }
        Position north()
        {
                return Position(row - 1, col);
        }
        Position south()
        {
                return Position(row + 1, col);
        }
        Position east()
        {
                return Position(row, col + 1);
        }
        Position west()
        {
                return Position(row, col - 1);
        }
        bool inBounds(int rowLimit, int colLimit)
        {
                return (0 < row) and (row < rowLimit)
                        and (0 < col) and (col < colLimit);
        }
};

#endif
