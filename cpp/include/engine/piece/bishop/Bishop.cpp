#include <list>
#include <iostream>

#include "Bishop.h"

Piece::PIECE Bishop::_get_ID() const { return PIECE::BISHOP; }

void Bishop::update_movements_and_attacks(Board* board) 
{
    std::list<Position> legal_movements = get_legal_diagonal_movement(board);

    // GENERATION FOR MOVEMENTS & ATTACKS
    for (Position position: legal_movements)
    {
        if (is_movement_valid(position, board)) all_possible_movements.push_back(position); // Note: That if the move is a movement. It should never register as an attack becuase the position would have nullptr for piece. 
        else if (is_attack_valid(position, board)) all_possible_attacks.push_back(position);
    }
}

Bishop::Bishop(const Position position, bool is_black): Piece(position, is_black)
{

}