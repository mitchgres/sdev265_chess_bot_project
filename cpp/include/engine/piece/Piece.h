#ifndef __PIECE_H__
#define __PIECE_H__

#include <list>
#include <iostream>

#include "../position/Position.h"
#include "../board/Board.h"

class Board;

class Piece
{
public:
    /// @brief When faced with a situation where and action can only be preformed on another piece by a ceratin piece. For instance, En Passnat a function that gives 
    ///        the identidy of the piece is needed. 
    enum PIECE
    {
        BISHOP,
        KING,
        KNIGHT,
        PAWN,
        QUEEN,
        ROOK
    };

    // ==== PUBLIC MEMBER FUNCTIONS ====
    Piece(const Position starting_position, bool is_black);
    Position _get_position() const;
    virtual void _set_position(Position new_postion);
    std::list<Position> _get_movements(Board* board);
    std::list<Position> _get_attacks(Board* board);
    bool _is_black() const;

    // ==== PUBLIC MEMBER FUNCTIONS THAT MUST BE OVERRIDEN ==== 
    virtual PIECE _get_ID() const = 0;

protected:
    //==== MEMBER VARIABLES ====
    Position position;
    std::list<Position> all_possible_movements;
    std::list<Position> all_possible_attacks; 
    bool is_black;
    
    //==== PRIVATE MEMBER FUNCTIONS ====

    /// Is the given position within the 8x8 constraints of the board?
    bool _is_square_blocked(const Position* target_position, Board* board);
    static bool _is_in_bounds(const Position * position);
    static bool _is_in_bounds(int horizontial, int vertical);
 
    // These are methods that are used by specific pieces when they want to find which piece is blocking them from travering the board. 
    // They find the furthest that they can go on one column then return the piece blocking so it can be determined if they can take it. 
    std::list<Position> get_legal_vertical_movement(Board* board);
    std::list<Position> get_legal_horizontial_movement(Board* board);
    std::list<Position> get_legal_diagonal_movement(Board* board);

    bool is_attack_valid(Position target_square, Board *board) const;
    bool is_movement_valid(Position new_position, Board* board) const;

    virtual void update_movements_and_attacks(Board* board) = 0;
};
#endif // __PIECE_H__