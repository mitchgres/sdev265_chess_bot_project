#include "piece/Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

// Piece class implementation

Piece::Piece(Position position) : _position(position), _isBlack(false) {}

Position Piece::_getPosition() const {
    return _position;
}

void Piece::_setPosition(const Position& newPosition) {
    _position = newPosition;
}

bool Piece::_isBlack() const {
    return _isBlack;
}
