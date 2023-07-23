#include "Position.h"

Position::Position(short horizontial, short vertical){
    _horizontial = horizontial;
    _vertical = vertical;
}

Position::Position()
{
    Position(-1, -1);
}

bool Position::operator== (const Position other_position) const {
    // If the horizontial and vertical are the same then the positions are the same.
    if (other_position._horizontial == _horizontial && other_position._vertical == _vertical){
        return true;
    }
    else {
        return false;
    }
}
