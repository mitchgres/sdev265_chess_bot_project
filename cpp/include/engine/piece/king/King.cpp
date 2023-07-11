#include "King.h"

King::King(Position position) : Piece(position) {}

Piece::PIECE King::_getID() const {
    return PIECE::KING;
}

Position* King::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Define the directions in which the King can move
    int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // horizontal and vertical moves
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // diagonal moves
    };

    // Iterate over the directions and generate moves
    for (const auto& direction : directions) {
        int dx = direction[0];
        int dy = direction[1];
        int x = _position._horizontial + dx;
        int y = _position._vertical + dy;

        Position move(x, y);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* King::_getLegalAttackMoves() const {
    return _getLegalMoves();
}

Position* King::_getAllLegalMoves() const {
    std::vector<Position> allMoves;

    Position* legalMoves = _getLegalMoves();
    Position* legalAttackMoves = _getLegalAttackMoves();

    // Append legal moves and legal attack moves to allMoves
    for (int i = 0; legalMoves[i].isValid(); i++) {
        allMoves.push_back(legalMoves[i]);
    }

    for (int i = 0; legalAttackMoves[i].isValid(); i++) {
        allMoves.push_back(legalAttackMoves[i]);
    }

    delete[] legalMoves;
    delete[] legalAttackMoves;

    // Convert the vector to a dynamic array and return
    Position* allMovesArray = new Position[allMoves.size()];
    std::copy(allMoves.begin(), allMoves.end(), allMovesArray);
    return allMovesArray;
}

bool King::_canTake(const Piece& piece) const {
    return _isMoveValid(piece._getPosition());
}

bool King::_canMove(const Position& position) const {
    return _isMoveValid(position);
}

Position* King::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* King::_getUnprocessedAttackMoves() const {
    return _getLegalAttackMoves();
}

Position* King::_processMoves(const Position*& moves) const {
    return moves;
}

bool King::_isMoveValid(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;
    }

    // Check if the destination square is occupied by a friendly piece
    if (_board->isSquareOccupiedByFriendly(position, _isBlack)) {
        return false;
    }

    // Calculate the absolute difference in horizontal and vertical positions
    int dx = abs(position._horizontial - _position._horizontial);
    int dy = abs(position._vertical - _position._vertical);

    // Check if the move is within the King's movement range
    if (dx <= 1 && dy <= 1) {
        return true;
    }

    return false;
}
