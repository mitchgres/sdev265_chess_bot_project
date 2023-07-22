#include <list>

#include "Rook.h"
#include "../../board/Board.h"

Piece::PIECE Rook::_get_ID() const { return Piece::PIECE::ROOK; }

void Rook::update_movements_and_attacks(Board* board)
{
    // The two lists represent the movement of the piece overall. Merge together so we can get the full list of all movement. 
    std::list<Position> legal_movements;

    std::list<Position> legal_horizontial_movements = get_legal_horizontial_movement(board);
    std::list<Position> legal_vertical_movements = get_legal_vertical_movement(board);

    legal_movements = legal_horizontial_movements;
    for (Position position: legal_vertical_movements) legal_movements.push_back(position);

    // GENERATION FOR MOVEMENTS & ATTACKS
    for (Position position: legal_movements)
    {
        if (is_movement_valid(position, board)) all_possible_movements.push_back(position);
        else if (is_attack_valid(position, board)) all_possible_attacks.push_back(position);
    }
}

Rook::Rook(const Position position, bool is_black): Piece(position, is_black)
{
    
}