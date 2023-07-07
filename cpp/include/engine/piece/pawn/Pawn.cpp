#include "Pawn.h"
#include "../Piece.h"

inline Piece::PIECE Pawn::_getID() const {
    return Piece::PIECE::PAWN;
}

Position* Pawn::_getLegalMoves() const {

}
        
Position* Pawn::_getLegalAttackMoves() const {

}
        
Position* Pawn::_getAllLegalMoves() const {

}
        
bool Pawn::_isCapturePossible(const Piece&) const {

}
        
bool Pawn::_isMovePossible(const Position&) const {

}

Position* Pawn::_getUnprocessedMoves() const {
    
}
        
Position* Pawn::_getUnprocessedAttackMoves() const {

}
        
Position* Pawn::_processMoves(const Position*&) const {

}