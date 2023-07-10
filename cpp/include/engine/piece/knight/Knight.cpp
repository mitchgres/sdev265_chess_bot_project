#include "Knight.h"

Knight::Knight(Position position) : Piece(position) {}

Piece::PIECE Knight::_getID() const {
    return PIECE::KNIGHT;
}

Position* Knight::_getLegalMoves() const {
    // Implement logic to generate legal moves for the Knight
    return nullptr;
}

Position* Knight::_getLegalAttackMoves() const {
    // Implement logic to generate legal attack moves for the Knight
    return nullptr;
}

Position* Knight::_getAllLegalMoves() const {
    // Implement logic to generate all legal moves for the Knight
    return nullptr;
}

bool Knight::_canTake(const Piece& piece) const {
    // Implement logic to check if the Knight can take the given piece
    return false;
}

bool Knight::_canMove(const Position& position) const {
    // Implement logic to check if the Knight can move to the given position
    return false;
}

Position* Knight::_getUnprocessedMoves() const {
    // Implement logic to generate unprocessed moves for the Knight
    return nullptr;
}

Position* Knight::_getUnprocessedAttackMoves() const {
    // Implement logic to generate unprocessed attack moves for the Knight
    return nullptr;
}

Position* Knight::_processMoves(const Position*& moves) const {
    // Implement logic to process the moves for the Knight
    return nullptr;
}
