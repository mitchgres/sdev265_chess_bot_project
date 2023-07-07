#include "../Piece.h"

class King: public Piece {
    public:
        Position* _getNextPossiblePositions() const;
        inline PIECE _getID() const;
    private:
};