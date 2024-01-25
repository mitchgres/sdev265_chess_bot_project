#include<cstdlib>
#include <ctime>
#include <cstring>

#include "Engine.h"

struct Movement
{
    Position _from;
    Position _to;
};

std::list<Movement> generate_all_possible_moves(Board* board)
{
    bool is_black_turn = board->_is_black_turn();
    std::list<Piece*> get_all_friendly_pieces = board->_get_all_opposing_pieces(!is_black_turn); // This will instead of getting the opposing get all friendly. 

    // We'll ignore the piece if it's null value to reduce computation time. 
    get_all_friendly_pieces.remove_if([](Piece* piece) { return piece->_get_position() == Position(-1, -1); });

    // We'll now iterate through all the pieces and get all the possible moves that could be made.
    std::list<Movement> all_possible_moves;

    for (Piece* piece: get_all_friendly_pieces)
    {
        for (Position position: piece->_get_movements(board))
        {
            Movement move;
            move._from = piece->_get_position();
            move._to = position;
            all_possible_moves.push_back(move);
        }
    }

    // We'll do the same thing but for attacks instead of movements.
    for (Piece* piece: get_all_friendly_pieces)
    {
        for (Position position: piece->_get_attacks(board))
        {
            Movement move;
            move._from = piece->_get_position();
            move._to = position;
            all_possible_moves.push_back(move);
        }
    }

    return all_possible_moves;
}

double Engine::evaluate(Board* board)
{
    // Right now the evaluate function will just return the numerical value of all the piece for your side of the board
    // and then subtract the numerical value of all the pieces for the opposing side of the board.
    const int PAWN_VALUE = 1;
    const int KNIGHT_VALUE = 3;
    const int BISHOP_VALUE = 3;
    const int ROOK_VALUE = 5;
    const int QUEEN_VALUE = 9;
    const int KING_VALUE = 100; // The game will end before this will get executed.

    std::list<Piece*> all_pieces = board->_get_all_pieces();
    double value = 0;
    for (Piece* piece: all_pieces)
    {
        if (piece->_get_position() == Position(-1, -1))
        {
            all_pieces.remove(piece);
        }
        switch (piece->_get_ID())
        {
            // Note that we're assuming that the bot is only ever going to be black since white it our default.
            case Piece::PIECE::PAWN:
                (piece->_is_black() ? value -= PAWN_VALUE : value += PAWN_VALUE);
                break;
            case Piece::PIECE::KNIGHT:
                (piece->_is_black() ? value -= KNIGHT_VALUE : value += KNIGHT_VALUE);
                break;
            case Piece::PIECE::BISHOP:
                (piece->_is_black() ? value -= BISHOP_VALUE : value += BISHOP_VALUE);
                break;
            case Piece::PIECE::ROOK:
                (piece->_is_black() ? value -= ROOK_VALUE : value += ROOK_VALUE);
                break;
            case Piece::PIECE::QUEEN:
                (piece->_is_black() ? value -= QUEEN_VALUE : value += QUEEN_VALUE);
                break;
            case Piece::PIECE::KING:
                (piece->_is_black() ? value -= KING_VALUE : value += KING_VALUE);
                break;
        }
    }

    return value;
}

// The RANDOM ENGINE will first determine all the possible movements that could be made. It'll then choose a random movement from that list. That movement will be put updated
// on a board and the FEN will be outputted as a updated board

// RANDOM
Board* Engine::get_random_move(Board* board)
{
    std::list<Movement> all_possible_moves = generate_all_possible_moves(board);
    // We'll now choose a random move from the list of all possible moves.
    srand((int)time(0)); // Truly random number. 
    int random_number = rand() % all_possible_moves.size();

    // Update the board with the random move.
    std::list<Movement>::iterator it = all_possible_moves.begin();
    std::advance(it, random_number);
    board->_update(it->_from, it->_to);

    board->_print_board();

    return board;
}

Board* Engine::get_simple_move(Board* board)
{
    // We'll at first set the best_move to a random move then we'll iterate through all the possible moves and see if we can find a better move.
    // to see if we can find a better move. If not we'll just return that one.
    std::list<Movement> all_possible_moves = generate_all_possible_moves(board);

    Movement best_move = all_possible_moves.front();
    for (Movement move: all_possible_moves)
    {
        // We'll look one move ahead and see what the best outcome is for that one move. If they're all equal like they are
        // in the beginning of the game we'll tell it to move a random piece.
        Board board_copy = board->_get_copy();
        std::cout << "Board Copy Before Update: " << std::endl;
        board_copy._print_board();
        board_copy._update(move._from, move._to);
        std::cout << "Board Copy After Update: " << std::endl;
        board_copy._print_board();
        //Print the evaluation of the board copy
        std::cout << "Evaluation of the board copy: " << Engine::evaluate(&board_copy) << std::endl;
        std::cout << "Evaluation of the board: " << Engine::evaluate(board) << std::endl;


        if (Engine::evaluate(&board_copy) > Engine::evaluate(board))
        {
            std::cout << "Better Move Found" << std::endl;
            best_move = move;
        }
    }

    // Update the board with the best move.
    board->_update(best_move._from, best_move._to);
    board->_print_board();
    return board;
}