#include "Bishop.h"
#include "./piece/Piece.h"

Bishop::Bishop(Position position) : Piece(position) {}

Piece::PIECE Bishop::_getID() const {
    return PIECE::BISHOP;
}

Position* Bishop::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Define the directions in which the Bishop can move diagonally
    int directions[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    // Iterate over the directions and generate moves until blocked or out of bounds
    for (const auto& direction : directions) {
        int dx = direction[0];
        int dy = direction[1];
        int x = _position._horizontial + dx;
        int y = _position._vertical + dy;

        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            Position move(x, y);
            if (_isMoveValid(move)) {
                legalMoves.push_back(move);
            }

            // Check if the Bishop is blocked by another piece
            if (_isBlocked(move)) {
                break;
            }

            // Move further along the diagonal
            x += dx;
            y += dy;
        }
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* Bishop::_getLegalAttackMoves() const {
    return _getLegalMoves();
}

Position* Bishop::_getAllLegalMoves() const {
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

bool Bishop::_canTake(const Piece& piece) const {
    return _isMoveValid(piece._getPosition());
}

bool Bishop::_canMove(const Position& position) const {
    return _isMoveValid(position);
}

Position* Bishop::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* Bishop::_getUnprocessedAttackMoves() const {
    return _getLegalAttackMoves();
}

Position* Bishop::_processMoves(const Position*& moves) const {
    return moves;
}

bool Bishop::_isBlocked(const Position& position) const {
    // Calculate the direction of movement
    int dx = position._horizontial - _position._horizontial;
    int dy = position._vertical - _position._vertical;

    // Determine the direction of the diagonal
    int directionX = (dx > 0) ? 1 : -1;
    int directionY = (dy > 0) ? 1 : -1;

    int x = _position._horizontial + directionX;
    int y = _position._vertical + directionY;

    // Move across the diagonal path until reaching the final destination
    while (x != position._horizontial && y != position._vertical) {
        // Check if the square is occupied by a piece
        if (_board->isSquareOccupied(Position(x, y))) {
            return true;  // The diagonal path is blocked
        }

        // Move further along the diagonal path
        x += directionX;
        y += directionY;
    }

    return false;  // The diagonal path is not blocked
}

bool Bishop::_isMoveValid(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;  // Move is outside the board
    }

    // Check if the destination square is occupied by a friendly piece
    if (_board->isSquareOccupiedByFriendly(position, _isBlack)) {
        return false;  // Move is blocked by a friendly piece
    }

    // Calculate the absolute difference in horizontal and vertical positions
    int dx = abs(position._horizontial - _position._horizontial);
    int dy = abs(position._vertical - _position._vertical);

    // Check if the move follows the diagonal movement pattern of a Bishop
    if (dx != dy) {
        return false;
    }

    // Check if the move is blocked by any piece along the diagonal path
    if (_isBlocked(position)) {
        return false;
    }

    return true;
}
