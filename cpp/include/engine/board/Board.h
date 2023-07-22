#ifndef __BOARD_H__
#define __BOARD_H__

#include <list>
#include <string>
#include <iostream>

#include "../piece/Piece.h"

class Piece;

class Board
{
public:
    Board();
    ~Board();
    Board(const std::string &); // FEN Notation is the input that's the string.
    std::string _as_fen();
    std::list<Piece *> _get_all_pieces();
    std::list<Piece *> _get_all_opposing_pieces(bool is_current_black);
    Piece *get_piece_at(Position);
    void _update(Position& , Position &);
    void _print_board() const;
    void _print_data() const;
    // Are only use for checking for checks on the king. 
    Board _get_copy();

    // TODO: Imlplement these functions.
    bool _is_black_turn() const;
    bool _is_stalemate(bool _is_black);
    bool _is_checkmate(bool _is_black);
    bool _is_king_in_check(bool _is_black);

private:
    std::list<Piece*> _board;
    // DETERMINED BY FEN
    bool is_black_turn; 
};
#endif // __BOARD_H__

// TODO: CASTLING LOGIC NOT ADDED YET.