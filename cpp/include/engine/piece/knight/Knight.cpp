#include "Knight.h"

Knight::Knight(Position position) : Piece(position) {}

Piece::PIECE Knight::_getID() const {
    return PIECE::KNIGHT;
}

Position* Knight::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Define the possible knight move offsets
    int offsets[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    // Iterate over the offsets and generate potential moves
    for (const auto& offset : offsets) {
        int dx = offset[0];
        int dy = offset[1];

        int x = _position._horizontal + dx;
        int y = _position._vertical + dy;

        // Check if the potential move is within the bounds of the board
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            Position move(x, y);

            // Check if the move is valid
            if (_isMoveValid(move)) {
                legalMoves.push_back(move);
            }
        }
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* Knight::_getLegalAttackMoves() const {
    return _getLegalMoves();
}

Position* Knight::_getAllLegalMoves() const {
    return _getLegalMoves();
}

bool Knight::_canTake(const Piece& piece) const {
    return _isMoveValid(piece._getPosition());
}

bool Knight::_canMove(const Position& position) const {
    return _isMoveValid(position);
}

Position* Knight::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* Knight::_getUnprocessedAttackMoves() const {
    return _getLegalMoves();
}

Position* Knight::_processMoves(const Position*& moves) const {
    return moves;
}

bool Knight::_isMoveValid(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontal < 0 || position._horizontal >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;
    }

    // Check if the destination square is empty or occupied by an opponent's piece
    if (_board->isSquareOccupiedByFriendly(position, _isBlack)) {
        return false;
    }

    // Calculate the absolute difference in horizontal and vertical positions
    int dx = abs(position._horizontal - _position._horizontal);
    int dy = abs(position._vertical - _position._vertical);

    // Check if the move follows the "L" shape pattern of a Knight
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1)) {
        return true;
    }

    return false;
}
