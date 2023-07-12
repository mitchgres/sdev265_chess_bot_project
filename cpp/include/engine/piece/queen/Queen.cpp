#include "Queen.h"
#include "../Piece.h"

Queen::Queen(Position position) : Piece(position) {}

Piece::PIECE Queen::_getID() const {
    return PIECE::QUEEN;
}

Position* Queen::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Generate legal moves along horizontal
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

    // Generate legal moves along vertical
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

    // Generate legal moves along positive diagonal
    int x = _position._horizontial + 1;
    int y = _position._vertical - 1;
    while (x < 8 && y >= 0) {
        Position move(x, y);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
        x++;
        y--;
    }

    x = _position._horizontial - 1;
    y = _position._vertical + 1;
    while (x >= 0 && y < 8) {
        Position move(x, y);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
        x--;
        y++;
    }

    // Generate legal moves along negative diagonal
    x = _position._horizontial - 1;
    y = _position._vertical - 1;
    while (x >= 0 && y >= 0) {
        Position move(x, y);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
        x--;
        y--;
    }

    x = _position._horizontial + 1;
    y = _position._vertical + 1;
    while (x < 8 && y < 8) {
        Position move(x, y);
        if (_isMoveValid(move)) {
            legalMoves.push_back(move);
        }
        if (_isBlocked(move)) {
            break;
        }
        x++;
        y++;
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* Queen::_getLegalAttackMoves() const {
    return _getLegalMoves();
}

Position* Queen::_getAllLegalMoves() const {
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

bool Queen::_canTake(const Piece& piece) const {
    return _isMoveValid(piece._getPosition());
}

bool Queen::_canMove(const Position& position) const {
    return _isMoveValid(position);
}

Position* Queen::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* Queen::_getUnprocessedAttackMoves() const {
    return _getLegalAttackMoves();
}

Position* Queen::_processMoves(const Position*& moves) const {
    return moves;
}

bool Queen::_isMoveValid(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;
    }

    // Check if the destination square is either empty or occupied by an opponent's piece
    if (_board->isSquareOccupied(position) && !_board->isSquareOccupiedByOpponent(position, _isBlack)) {
        return false; 
    }

    return true;
}

bool Queen::_isBlocked(const Position& position) const {
    // Check if there are any obstructions in the queens path
    int deltaX = position._horizontial - _position._horizontial;
    int deltaY = position._vertical - _position._vertical;

    int xIncrement = (deltaX > 0) ? 1 : (deltaX < 0) ? -1 : 0;
    int yIncrement = (deltaY > 0) ? 1 : (deltaY < 0) ? -1 : 0;

    int x = _position._horizontial + xIncrement;
    int y = _position._vertical + yIncrement;

    while (x != position._horizontial || y != position._vertical) {
        if (_board->isSquareOccupied(Position(x, y))) {
            return true;
        }
        x += xIncrement;
        y += yIncrement;
    }

    return false;
}
