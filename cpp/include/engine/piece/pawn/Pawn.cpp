#include "Pawn.h"
#include "../Piece.h"

Piece::PIECE Pawn::_getID() const {
    return Piece::PIECE::PAWN;
}

Position* Pawn::_getLegalMoves() const {
    std::vector<Position> legalMoves;

    // Determine the direction of movement based on the pawns color
    int direction = (_isBlack) ? 1 : -1;

    // Check the square in front of the pawn
    Position forwardMove(_position._horizontial, _position._vertical + direction);
    if (_isMovePossible(forwardMove) && !_board->isSquareOccupied(forwardMove)) {
        legalMoves.push_back(forwardMove);

        // Check if it's the pawns first move and add the double forward move if possible
        if ((_isBlack && _position._vertical == 1) || (!_isBlack && _position._vertical == 6)) {
            Position doubleForwardMove(_position._horizontial, _position._vertical + (2 * direction));
            if (!_board->isSquareOccupied(doubleForwardMove)) {
                legalMoves.push_back(doubleForwardMove);
            }
        }
    }

    // Check diagonal captures
    Position captureMove1(_position._horizontial - 1, _position._vertical + direction);
    Position captureMove2(_position._horizontial + 1, _position._vertical + direction);
    if (_isCapturePossible(captureMove1)) {
        legalMoves.push_back(captureMove1);
    }
    if (_isCapturePossible(captureMove2)) {
        legalMoves.push_back(captureMove2);
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalMoves.size()];
    std::copy(legalMoves.begin(), legalMoves.end(), movesArray);
    return movesArray;
}

Position* Pawn::_getLegalAttackMoves() const {
    std::vector<Position> legalAttackMoves;

    // Determine the direction of movement based on the pawns color
    int direction = (_isBlack) ? 1 : -1;

    // Check diagonal captures
    Position captureMove1(_position._horizontial - 1, _position._vertical + direction);
    Position captureMove2(_position._horizontial + 1, _position._vertical + direction);
    if (_isCapturePossible(captureMove1)) {
        legalAttackMoves.push_back(captureMove1);
    }
    if (_isCapturePossible(captureMove2)) {
        legalAttackMoves.push_back(captureMove2);
    }

    // Convert the vector to a dynamic array and return
    Position* movesArray = new Position[legalAttackMoves.size()];
    std::copy(legalAttackMoves.begin(), legalAttackMoves.end(), movesArray);
    return movesArray;
}

Position* Pawn::_getAllLegalMoves() const {
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

bool Pawn::_isCapturePossible(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;  // Move is outside the board
    }

    // Check if the destination square is occupied by an opponent's piece
    if (_board->isSquareOccupiedByOpponent(position, _isBlack)) {
        return true;
    }

    return false;
}

bool Pawn::_isMovePossible(const Position& position) const {
    // Check if the move is within the bounds of the board
    if (position._horizontial < 0 || position._horizontial >= 8 ||
        position._vertical < 0 || position._vertical >= 8) {
        return false;  // Move is outside the board
    }

    // Check if the destination square is occupied by any piece
    if (_board->isSquareOccupied(position)) {
        return false;
    }

    return true;
}

Position* Pawn::_getUnprocessedMoves() const {
    return _getLegalMoves();
}

Position* Pawn::_getUnprocessedAttackMoves() const {
    return _getLegalAttackMoves();
}

Position* Pawn::_processMoves(const Position*& moves) const {
    return moves;
}
