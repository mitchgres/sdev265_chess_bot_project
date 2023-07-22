#include <list>

#include "Queen.h"

Piece::PIECE Queen::_get_ID() const { return Piece::PIECE::QUEEN; }

void Queen::update_movements_and_attacks(Board* board)
{
    std::list<Position> legal_movements;

    std::list<Position> legal_horizontial_movements = get_legal_horizontial_movement(board);
    std::list<Position> legal_vertical_movements = get_legal_vertical_movement(board);
    std::list<Position> legal_diagonal_movements = get_legal_diagonal_movement(board);

    legal_movements = legal_horizontial_movements;

    for (Position position: legal_vertical_movements)
    {
        legal_movements.push_back(position);
    }

    for (Position position: legal_diagonal_movements)
    {
        legal_movements.push_back(position);
    }

    // GENERATION FOR MOVEMENTS & ATTACKS
    for (Position position: legal_movements)
    {
        if (is_movement_valid(position, board)) all_possible_movements.push_back(position); // Note: That if the move is a movement. It should never register as an attack becuase the position would have nullptr for piece. 
        else if (is_attack_valid(position, board)) all_possible_attacks.push_back(position);
    }
}

Queen::Queen(const Position position, bool is_black): Piece(position, is_black)
{

}