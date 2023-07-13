#include "piece/Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

// Piece class implementation

Piece::Piece(Position position) : _position(position), _isBlack(false) {}

void Piece::_setPosition(const Position& newPosition) {
    _position = newPosition;
}

Position Piece::_getPosition() const {
    return _position;
}

bool Piece::_isBlack() const {
    return _isBlack;
}

// King
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

// Queen
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

// Bishop
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

// Knight
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

// Rook
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

// Pawn
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
