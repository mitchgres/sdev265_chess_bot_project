#include "Rook.h"
#include "../Piece.h"

Rook::Rook(Position position) : Piece(position) {}

Piece::PIECE Rook::_getID() const {
    return PIECE::ROOK;
}

Position* Rook::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Legal moves along horizontal ranks
    for (int i = _position._horizontial - 1; i >= 0; i--) {
        Position move(i, _position._vertical);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
    }

    for (int i = _position._horizontial + 1; i < 8; i++) {
        Position move(i, _position._vertical);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
    }

    // Legal moves along vertical files
    for (int i = _position._vertical - 1; i >= 0; i--) {
        Position move(_position._horizontial, i);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
    }

    for (int i = _position._vertical + 1; i < 8; i++) {
        Position move(_position._horizontial, i);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* Rook::_getLegalAttackMoves() const {
    return _getLegalMoves();
}

Position* Rook::_getAllLegalMoves() const {
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

bool Rook::_canTake(const Piece& piece) const {
    return _isMoveValid(piece._getPosition());
}

bool Rook::_canMove(const Position& position) const {
    return _isMoveValid(position);
}

Position* Rook::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* Rook::_getUnprocessedAttackMoves() const {
    return _getLegalAttackMoves();
}

Position* Rook::_processMoves(const Position*& moves) const {
    return moves;
}

bool Rook::_isBlocked(const Position& position) const {
    // Calculate the direction of movement
    int dx = position._horizontial - _position._horizontial;
    int dy = position._vertical - _position._vertical;

    // Determine the direction of movement along ranks or files
    int directionX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int directionY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int x = _position._horizontial + directionX;
    int y = _position._vertical + directionY;

    // Move along the horizontal or vertical path until reaching the final destination
    while (x != position._horizontial || y != position._vertical) {
        // Check if the square is occupied by a piece
        if (_board->isSquareOccupied(Position(x, y))) {
            return true;  // The path is blocked
        }

        // Move further along the path
        x += directionX;
        y += directionY;
    }

    return false;  // The path is not blocked
}

bool Rook::_isMoveValid(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;  // Move is outside the board
    }

    // Check if the destination square is occupied by a friendly piece
    if (_board->isSquareOccupiedByFriendly(position, _isBlack)) {
        return false;
    }

    // Check if the move follows the movement pattern of a Rook 
    if (position._horizontial != _position._horizontial &&
        position._vertical != _position._vertical) {
        return false;
    }

    // Check if the move is blocked by any piece along the horizontal or vertical path
    if (_isBlocked(position)) {
        return false;
    }

    return true;
}
