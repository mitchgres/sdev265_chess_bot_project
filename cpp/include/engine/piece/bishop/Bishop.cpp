#include "Bishop.h"
#include "./piece/Piece.h"

Bishop::Bishop(Position position) : Piece(position) {}

Piece::PIECE Bishop::_getID() const {
    return PIECE::BISHOP;
}

Position* Bishop::_getLegalMoves() const {
    // Implement logic to generate legal moves for the Bishop
    return nullptr;
}

Position* Bishop::_getLegalAttackMoves() const {
    // Implement logic to generate legal attack moves for the Bishop
    return nullptr;
}

Position* Bishop::_getAllLegalMoves() const {
    // Implement logic to generate all legal moves for the Bishop
    return nullptr;
}

bool Bishop::_canTake(const Piece& piece) const {
    // Implement logic to check if the Bishop can take the given piece
    return false;
}

bool Bishop::_canMove(const Position& position) const {
    // Implement logic to check if the Bishop can move to the given position
    return false;
}

Position* Bishop::_getUnprocessedMoves() const {
    // Implement logic to generate unprocessed moves for the Bishop
    return nullptr;
}

Position* Bishop::_getUnprocessedAttackMoves() const {
    // Implement logic to generate unprocessed attack moves for the Bishop
    return nullptr;
}

Position* Bishop::_processMoves(const Position*& moves) const {
    // Implement logic to process the moves for the Bishop
    return nullptr;
}
