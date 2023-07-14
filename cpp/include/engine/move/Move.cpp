#include "Move.h"

Move::Move(Piece* piece, const Position& old_position, const Position& new_position)
{
    _piece = piece;
    _old_position = old_position;
    _new_position = new_position;
}

Piece* Move::_get_piece_ptr() const
{
    return _piece;
}

Position Move:: _get_old_position() const
{
    return _old_position;
}

Position Move::_get_new_position() const
{
    return _new_position;
}
