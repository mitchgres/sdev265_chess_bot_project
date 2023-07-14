#include "../piece/Piece.h"
#include "../position/Position.h"

/// @brief Representation of the movement that a piece will make on the board. Previous & New Location, and the moved piece.
struct Move {
    Piece _piece;
    Position _old_position;
    Position _new_position;
}