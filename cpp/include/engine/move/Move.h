#include "../piece/Piece.h"
#include "../position/Position.h"

/// @brief Representation of the movement that a piece will make on the board. Previous & New Location, and the moved piece.
class Move 
{
    public: 
        Move(Piece*, const Position&, const Position&);
        inline Piece* _get_piece_ptr() const;
        inline Position _get_old_position() const;
        inline Position _get_new_position() const;
    private:   
        Piece* _piece; // Pointer is needed because it's abstract superclass.
        Position _old_position;
        Position _new_position;
};