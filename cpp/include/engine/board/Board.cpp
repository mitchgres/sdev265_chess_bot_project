/**
 * @file Board.cpp
 * @author Mitchell M. Gresham
 * @brief Representation of a Chess Board.
 * @version 0.1
 * @date 2023-07-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include "Board.h"
#include "../position/Position.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/king/King.h"
#include "../piece/knight/Knight.h"
#include "../piece/pawn/Pawn.h"
#include "../piece/queen/Queen.h"
#include "../piece/rook/Rook.h"

Board::Board(){
    _reset();
}

Board::~Board(){
    delete[] _board;
}

inline Piece* Board::_get() const {
    return _board;
}

void Board::_reset(){
    // Reference Documentation for BOARD PIECE INDEX GUIDE for information on interpretation.
    short index = 0;
    
    // Black Back Rank Added
    _board[index] = Rook(Position(0, 7)); index++;
    _board[index] = Knight(Position(1, 7)); index++;
    _board[index] = Bishop(Position(2, 7)); index++;
    _board[index] = Queen(Position(3, 7)); index++;
    _board[index] = King(Position(4, 7)); index++;
    _board[index] = Bishop(Position(5, 7)); index++;
    _board[index] = Knight(Position(6, 7)); index++;
    _board[index] = Rook(Position(7, 7)); index++;

    // Black Pawn Row Added
    _board[index] = Pawn(Position(0, 6)); index++;
    _board[index] = Pawn(Position(1, 6)); index++;
    _board[index] = Pawn(Position(2, 6)); index++;
    _board[index] = Pawn(Position(3, 6)); index++;
    _board[index] = Pawn(Position(4, 6)); index++;
    _board[index] = Pawn(Position(5, 6)); index++;
    _board[index] = Pawn(Position(6, 6)); index++;
    _board[index] = Pawn(Position(7, 6)); index++;

    // White Pawn Row Added
    _board[index] = Pawn(Position(0, 1)); index++;
    _board[index] = Pawn(Position(1, 1)); index++;
    _board[index] = Pawn(Position(2, 1)); index++;
    _board[index] = Pawn(Position(3, 1)); index++;
    _board[index] = Pawn(Position(4, 1)); index++;
    _board[index] = Pawn(Position(5, 1)); index++;
    _board[index] = Pawn(Position(6, 1)); index++;
    _board[index] = Pawn(Position(7, 1)); index++;

    // White Back Rank Added
    _board[index] = Rook(Position(0, 0)); index++;
    _board[index] = Knight(Position(1, 0)); index++;
    _board[index] = Bishop(Position(2, 0)); index++;
    _board[index] = Queen(Position(3, 0)); index++;
    _board[index] = King(Position(4, 0)); index++;
    _board[index] = Bishop(Position(5, 0)); index++;
    _board[index] = Knight(Position(6, 0)); index++;
    _board[index] = Rook(Position(7, 0));

    // Board has now been created with pieces in the correct starting positions. 
}

void Board::_movePiece(Position source, Position destination) {
    Piece* piece = _getPiece(source);
    if (piece != nullptr) {
        piece->_setPosition(destination);
    }
}

Piece* Board::_getPiece(Position position) const {
    for (int i = 0; i < 32; i++) {
        if (_board[i]._getPosition() == position) {
            return &_board[i];
        }
    }
    return nullptr;
}

bool Board::_isSquareOccupied(Position position) const {
    return _getPiece(position) != nullptr;
}

bool Board::_isSquareOccupiedByFriendly(Position position, bool isBlack) const {
    Piece* piece = _getPiece(position);
    return piece != nullptr && piece->_isBlack() == isBlack;
}

bool Board::_isSquareOccupiedByOpponent(Position position, bool isBlack) const {
    Piece* piece = _getPiece(position);
    return piece != nullptr && piece->_isBlack() != isBlack;
}

void Board::_update(Position old_position, Position new_position) {
    Piece current_piece;
    bool isPieceThere;

    // Find the piece with that position.
    for (int i = 0; i < 32; i++) {
        if (old_position == _board[i]._getPosition()) {
            current_piece = _board[i];
        }
    }

    // If there was another piece there update its position to a NULL value since taken.
    for (int i = 0; i < 32; i++) {
        if (new_position == _board[i]._getPosition()) {
            // The piece is taken.
            _board[i]._setPosition(Position(-1, -1));
        }
    }

    // Update its position
    current_piece._setPosition(new_position);
}




/// @brief  Prints to the standard output a visual representation of the chess board.
void Board::_printBoard() const {
    // The function will print out a two-dimensional array of characters, declared here.
    char char_representation_board[8][8];

    // Initialize the char represention of the board so that by default the space is empty. 
    for (int i = 0; i < 8; i++){
        for (int e = 0; e < 8; e++){
            char_representation_board[i][e] = '#';
        }
        
    }
    
    // Change the single-dimensional array to two dimensional for output. 
    for(int i = 0; i < 32; i++){
        // Get the position of the piece in the array. 
        int x = _board[i]._getPosition()._horizontial;
        int y = _board[i]._getPosition()._vertical;
        char char_representation_piece; 

        // Get the char that will represent the piece. 
        switch(_board[i]._getID()){
            case Piece::PIECE::BISHOP:
                char_representation_piece = 'B';
                break;
            case Piece::PIECE::KING:
                char_representation_piece = 'K';
                break;
            case Piece::PIECE::KNIGHT:
                char_representation_piece = 'N';
                break;
            case Piece::PIECE::PAWN:
                char_representation_piece = 'P';
                break;
            case Piece::PIECE::QUEEN:
                char_representation_piece = 'Q';
                break;
            case Piece::PIECE::ROOK:
                char_representation_piece = 'R';
                break;
        }

        // If the piece isn't taken then display it. 
        if (x > 0 && y > 0){
            char_representation_board[x][y] = char_representation_piece;
        }
    }
}

/// @brief Prints to the standard output the state of all pieces in the game. 
void Board::_printData() const {
    for(int i = 0; i < 32; i++){
        std::cout <<  "ID: " << _board[i]._getID() << " isBlack: " << _board[i]._isBlack() << " Position: X-" << _board[i]._getPosition()._horizontial << " Y-" << _board[i]._getPosition()._horizontial << std::endl;
    }
}

