#include "../Piece.h"

class Pawn: public Piece {
    public:
        inline PIECE _getID() const;
        Position* _getLegalMoves() const;
        Position* _getLegalAttackMoves() const;
        Position* _getAllLegalMoves() const;
        
    private:
        bool _isCapturePossible(const Piece&) const;
        bool _isMovePossible(const Position&) const;
        Position* _getUnprocessedMoves() const;
        Position* _getUnprocessedAttackMoves() const;
        Position* _processMoves(const Position*&) const;
};