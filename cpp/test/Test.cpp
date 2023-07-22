#include <exception>
#include <iostream>

#include "../include/engine/board/Board.h"
#include "../include/engine/Engine.h"
#include "../include/server/Server.h"

int test_board();
int test_bishop();
int test_engine();
int test_king();
int test_knight();
int test_pawn();
int test_queen();
int test_rook();

// PROGRAM WILL TEST ENGINE & DATA CLASSES FOR ENGINE
int main()
{
    if (test_board() == -1) std::cout << "[TEST FAILED]: BOARD" << std::endl; //DONE
    if (test_bishop() == -1) std::cout << "[TEST FAILED]: BISHOP" << std::endl; // DONE
    if (test_king() == -1) std::cout << "[TEST FAILED]: KING" << std::endl; // DONE
    if (test_knight() == -1) std::cout << "[TEST FAILED]: KNIGHT" << std::endl; // DONE
    if (test_pawn() == -1) std::cout << "[TEST FAILED]: PAWN" << std::endl; // DONE
    if (test_queen() == -1) std::cout << "[TEST FAILED]: QUEEN" << std::endl; // DONE
    if (test_rook() == -1) std::cout << "[TEST FAILED]: ROOK" << std::endl; // DONE 
    if (test_engine() == -1) std::cout << "[TEST FAILED]: ENGINE" << std::endl;
}

int test_board()
{
    std::cout << "---------------- [TEST]: BOARD STARTING... ----------------" << std::endl;
    // TEST ONE: PRINT METHODS
    std::cout << "[TEST ONE]: BEGIN";
    std::cout << "[TEST ONE]: DO PRINT METHODS WORK CORRECTLY?" << std::endl;
    do 
    {
        Board board;

        std::cout << "[TEST ONE]: PRINT BOARD" << std::endl;
        board._print_board();

        std::cout << "[TEST ONE]: PRINT DATA" << std::endl;
        board._print_data();    
    } while (false);

    std::cout << "[TEST ONE]: YOU SHOULD BE SEEING A DEFAULT BOARD WITH (BLACK ON LEFT) & (WHITE ON RIGHT)" << std::endl;
    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: FEN CONSTRUCTION
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: DOES FEN CONSTRUCTION WORK CORRECTLY?" << std::endl;
    
    do 
    {
        Board board("r2qkbnr/pppb1ppp/4p3/3p1P2/1n1PP1P1/P1N2N2/1PP4P/R1BQKB1R");
        board._print_board();
    } while (false);

    std::cout << "[TEST TWO]: YOU SHOULD BE SEEING AN EDITED BOARD" << std::endl;
    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

    // TEST THREE: DOES GETTING PIECE WORK
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: DOES GETTING PIECE WORK CORRECTLY?" << std::endl;

    do
    {
        Board board;

        // if-statement to determine if the ID of the piece that is at the location is equal to that of the white rook at (0, 0).
        if (board.get_piece_at(Position(0, 0))->_get_ID() != Piece::PIECE::ROOK)
        {
            std::cout << "[TEST THREE]: FAILED | EXPECTED: WHITE ROOK | ACTUAL: " << board.get_piece_at(Position(0, 0))->_get_ID() << std::endl;
            break;
        }
    } while (false);

    std::cout << "---------------- [TEST THREE]: COMPLETED ----------------" << std::endl;

    // TEST FOUR: DOES GETTING ALL OPPOSING PIECES WORK
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: DOES GETTING ALL OPPOSING PIECES WORK CORRECTLY?" << std::endl;
    
    do
    {
        Board board;
        std::cout << "[TEST FOUR]: GETTING ALL OPPOSING PIECES" << std::endl;
        for (Piece* piece: board._get_all_opposing_pieces(true))
        {
            if (piece->_is_black() == true)
            {
            std::cout << "[TEST FOUR]: FAILED | EXPECTED: WHITE PIECE | ACTUAL: BLACK PIECE" << std::endl;
            break;
            }
        }
    } while (false);

    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;

    // TEST FOUR: DOES GETTING ALL PIECES WORK
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: DOES GETTING ALL PIECES WORK CORRECTLY?" << std::endl;

    // Check if the number of elements in the list from the _get_all_pieces method is equal to the number of elements in the _board. 
    do
    {
        Board board;
        if (board._get_all_pieces().size() != 32)
        {
            std::cout << "[TEST FOUR]: FAILED | EXPECTED: " << 32 << " | ACTUAL: " << board._get_all_pieces().size() << std::endl;
            break;
        }
    } while (false);

    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;
    
    // TEST FIVE: DOES UPDATE BOARD WORK IF NO PIECE IS WHERE IT NEEDS TO MOVE
    std::cout << "[TEST FIVE]: BEGIN" << std::endl;
    std::cout << "[TEST FIVE]: DOES UPDATE BOARD WORK CORRECTLY IF NO PIECE IS WHERE IT NEEDS TO MOVE?" << std::endl;

    do
    {
        Board board;
        Position piece_starting_position(0, 0); // This is where out piece is originally.
        Position target_position(0, 2); // This is where we want to move it to. There shouldn't be a piece here. 

        board._update(piece_starting_position, target_position); 

        if (board.get_piece_at(target_position) == nullptr)
        {
            std::cout << "[TEST FIVE]: FAILED | EXPECTED: PIECE | ACTUAL: NO PIECE" << std::endl;
            break;
        }

    } while (false);
    
    std::cout << "---------------- [TEST FIVE]: COMPLETED ----------------" << std::endl;

    // TEST SEVEN: DOES UPDATE BOARD WORK IF PIECE IS WHERE IT NEEDS TO MOVE
    std::cout << "[TEST SEVEN]: BEGIN" << std::endl;
    std::cout << "[TEST SEVEN]: DOES UPDATE BOARD WORK CORRECTLY IF PIECE IS WHERE IT NEEDS TO MOVE?" << std::endl;

    do
    {
        Board board;
        Position piece_starting_position(0, 0); // This is where out piece is originally.
        Position target_position(0, 1); // This is where we want to move it to. There should be a piece here.

        // Let's get the piece in the target position before we capture it so that we can check if the position of it has been set to -1, -1.
        Piece* piece_in_target_position = board.get_piece_at(target_position);

        // Next we'll get a pointer to the piece that we want to move and check that it's position has been updated too. 
        Piece* piece_to_move = board.get_piece_at(piece_starting_position);

        board._update(piece_starting_position, target_position);

        if (!(piece_to_move->_get_position() == target_position))
        {
            std::cout << "[TEST SEVEN]: FAILED | EXPECTED: " << target_position._horizontial << ", " << target_position._vertical << " | ACTUAL: " << piece_to_move->_get_position()._horizontial << ", " << piece_to_move->_get_position()._vertical << std::endl;
            break;
        }

        if (!(piece_in_target_position->_get_position() == Position(-1, -1)))
        {
            std::cout << "[TEST SEVEN]: FAILED | EXPECTED: " << -1 << ", " << -1 << " | ACTUAL: " << piece_in_target_position->_get_position()._horizontial << ", " << piece_in_target_position->_get_position()._vertical << std::endl;
            break;
        }
    
    } while (false);
    
    std::cout << "---------------- [TEST SEVEN]: COMPLETED ----------------" << std::endl;
    
    // TEST EIGHT: DOES AS FEN WORK CORRECTLY?
    std::cout << "[TEST EIGHT]: BEGIN" << std::endl;
    std::cout << "[TEST EIGHT]: DOES AS FEN WORK CORRECTLY?" << std::endl;

    do 
    {
        // Make an if-statment that checks if the FEN is correct. If not then print out the FEN and the expected FEN, and say that test was failed.
        Board board;
        std::string expected_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        std::string actual_fen = board._as_fen();
        if (expected_fen != actual_fen)
        {
            std::cout << "[TEST EIGHT]: FAILED | EXPECTED: " << expected_fen << " | ACTUAL: " << actual_fen << std::endl;
            break;
        }

    } while(false);

    std::cout << "---------------- [TEST EIGHT]: COMPLETED ----------------" << std::endl;

    return 0;
}

// With this method we want to test all the methods of the Bishop class and make sure that they work correctly.
int test_bishop()
{
    std::cout << "---------------- [TEST]: BISHOP STARTING... ----------------" << std::endl;
    // TEST ONE: ARE GENERATED ATTACKS CORRECT?
    // In the position that's set up on the board there should be a white bishop at (4, 3) and a black pawn at (1, 6) we'll see if the bishop can capture the pawn and if it can 
    // move to the bottom left, bottom right, and top right. Also output the movements that it generates so that we'll know if the positions are incorrect.
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE GENERATED ATTACKS CORRECT?" << std::endl;

    do
    {
        Board board("8/1p6/8/8/4B3/8/8/k3K3");
        // Ouput the board just to make sure the right setup is there. 

        // See if the the position of the black pawn is in the list of generated attack movements for the bishop.
        for (Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            if (!(position == Position(1, 6)))
            {
                std::cout << "[TEST ONE]: FAILED | EXPECTED: " << 1 << ", " << 6 << " | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Now just output the whole list just in case there's something that we missed.
        std::cout << "[TEST ONE]: GENERATED ATTACKS" << std::endl;

        for(Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: ARE GENERATED MOVEMENTS CORRECT?
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: ARE GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/2p5/4p3/8/2Q2p2/1p6/7K");

        // See if the movements positions (5, 4), (6, 5), (7, 6), (5, 2), (6, 1), (7, 0), (3, 4), (2, 5), (3, 2), (2, 1), (1, 0) are in the list of generated movements for the bishop.
        for (Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            if (!(position == Position(5, 4) || position == Position(6, 5) || position == Position(7, 6) || position == Position(5, 2) || position == Position(6, 1) || position == Position(7, 0) || position == Position(3, 4) || position == Position(2, 5) || position == Position(3, 2) || position == Position(2, 1) || position == Position(1, 0)))
            {
                std::cout << "[TEST TWO]: WARNING | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                // Just because the case is true doesn't mean that they bishop couldn't move there since the list isn't comprehehensive. In this just output the position for the user to check manually. 
            }
        }

        // Now just output the whole list just in case there's something that we missed.
        std::cout << "[TEST TWO]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);
    
    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

    // TEST THREE: DOES UPDATE MOVEMENTS AND ATTACKS WORK CORRECTLY?
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: DOES UPDATE MOVEMENTS AND ATTACKS WORK CORRECTLY?" << std::endl;

    // The test will have the white bishop at (4, 3) with a pawn located at (3, 4) the 



    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // The test will have a white bishop located at a position (4,3). We'll then see if the auto-generated movements are correct for that position, and output the list of movemnts to the user..
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("4k3/8/8/8/4B3/8/8/4K3");
        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll output the movements that are generated for the bishop.
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;
    
    // TEST TWO: ARE THE AUTO-GENERATED MOVEMENTS CORRECT WHEN THERE A PIECE OF THE OPPOSITE COLOR IN THE WAY?
    // The code is the same as in test one but the side have been flipped so that the bishop is black, and in the same position. 
    do
    {
        Board board("4K3/8/8/8/4b3/8/8/4k3");
        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST TWO]: IS BOARD CORRECT?" << std::endl;

        // Now we'll output the movements that are generated for the bishop.
        std::cout << "[TEST TWO]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;
    
    // TEST THREE: ARE MOVEMENTS CORRECT WHEN THERE IS A FRIENDLY PIECE IN THE WAY?
    // We'll have the white bishop in the same position but this time there is a white pawn on (2, 5) that is in out path.
    
    std::cout << "[TEST THREE]: BEGIN" << std::endl; 
    std::cout << "[TEST THREE]: ARE MOVEMENTS CORRECT WHEN THERE IS A FRIENDLY PIECE IN THE WAY?" << std::endl;

    do
    {
        Board board("4k3/8/2P5/8/4B3/8/8/4K3");
        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST THREE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll output the movements that are generated for the bishop.
        std::cout << "[TEST THREE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

        // We should also while here make sure that white pawn isn't in out attack options. 
        std::cout << "[TEST THREE]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    // TEST FOUR: ARE THE AUTO-GENERATED ATTACKS CORRECT WHEN THERE IS A PIECE OF THE SAME COLOR IN THE WAY?
    // The test is a white bishop on (4, 3) and a black pawn on (2, 5). We'll see if the bishop can attack the pawn.
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: ARE THE AUTO-GENERATED ATTACKS CORRECT WHEN THERE IS A PIECE OF THE SAME COLOR IN THE WAY?" << std::endl;

    do
    {
        Board board("4k3/8/2p5/8/4B3/8/8/4K3");
        // Output the board just to make sure the right setup is there.

        board._print_board();

        std::cout << "[TEST FOUR]: IS BOARD CORRECT?" << std::endl;

        // Now we'll output the movements that are generated for the bishop.
        std::cout << "[TEST FOUR]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;
    
    // TEST FOUR: ARE THE AUTO-GENERATED ATTACKS CORRECT?
    // The program will have a white bishop on (4, 3) and a black pawn on (2, 5), and a black queen on (3, 2) if these are both in the list of generated attacks then the test is passed.
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: ARE THE AUTO-GENERATED ATTACKS CORRECT?" << std::endl;

    do
    {
        Board board("4k3/8/2p5/8/4B3/3q4/8/4K3");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST FOUR]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only two attack position in the list are (3, 2) and (2, 5).
        for(Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            if (!(position == Position(3, 2) || position == Position(2, 5)))
            {
                std::cout << "[TEST FOUR]: FAILED | EXPECTED: (3, 2), (2, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }
    } while (false);

    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;
    
    // TEST FIVE: ARE THE AUTO-GENERATED ATTACKS CORRECT WHEN THERE IS A PIECE OF SAME COLOR IN THE WAY?
    // The program is the same as above but there is a white pawn on (5, 4) that in the way of the bishop moving up-right. 
    std::cout << "[TEST FIVE]: BEGIN" << std::endl;
    std::cout << "[TEST FIVE]: ARE THE AUTO-GENERATED ATTACKS CORRECT WHEN THERE IS A PIECE OF SAME COLOR IN THE WAY?" << std::endl;

    do
    {
        Board board("4k3/8/2p5/5P2/4B3/3q4/8/4K3");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST FIVE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just output all the attack positions that are generated for the bishop and the movement positions and leave it up to tester to see for bugs.
        std::cout << "[TEST FIVE]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

        std::cout << "[TEST FIVE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);
    
    std::cout << "---------------- [TEST FIVE]: COMPLETED ----------------" << std::endl;

    // TEST SEVEN: SIMULATION. ARE THE AUTO-GENERATED MOVEMENTS & ATTACKS CORRECT AFTER TAKING A PIECE? DOES THAT TAKEN PIECE UPADTE CORRECTLY?
    // The program will have a white bishop on (1, 2) and a black queen on (3, 4), and then a black pawn on (2, 5) the bishop will take the queen and then we'll see. It's attack should only be (2, 5).
    std::cout << "[TEST SEVEN]: BEGIN" << std::endl;
    std::cout << "[TEST SEVEN]: SIMULATION. ARE THE AUTO-GENERATED MOVEMENTS & ATTACKS CORRECT AFTER TAKING A PIECE? DOES THAT TAKEN PIECE UPADTE CORRECTLY?" << std::endl;

    do
    {
        Board board("5k2/8/2p5/3q1P2/8/1B6/8/4K3");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST SEVEN]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (3, 4)
        for(Position position: board.get_piece_at(Position(1, 2))->_get_attacks(&board))
        {
            if (!(position == Position(3, 4)))
            {
                std::cout << "[TEST SEVEN]: FAILED | EXPECTED: (3, 4) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Now we'll move the bishop to (3, 4) and see if the attack list is updated correctly. 
        Position old_position(1, 2);
        Position new_position(3, 4);

        board._update(old_position, new_position);

        board._print_board();

        std::cout << "[TEST SEVEN]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (2, 5).
        for(Position position: board.get_piece_at(Position(3, 4))->_get_attacks(&board))
        {
            if (!(position == Position(2, 5)))
            {
                std::cout << "[TEST SEVEN]: FAILED | EXPECTED: (2, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

    } while (false);

    std::cout << "---------------- [TEST SEVEN]: COMPLETED ----------------" << std::endl;

}

int test_king()
{
    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // This will be a white king on (4, 1). We'll check if the movements of the king are equal to (3, 0), (3, 1), (3, 2), (4, 0), (4, 2), (5, 0), (5, 1), (5, 2).
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/8/8/8/8/4K3/8");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible movements of the king. 
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: CAN THE KING TAKE A PAWN THAT'S IN FRONT OF IT?
    // This will put have the white king on (4, 1) and a black pawn on (4, 2). We'll see if the king can take the pawn.
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: CAN THE KING TAKE A PAWN THAT'S IN FRONT OF IT?" << std::endl;

    do 
    {
        Board board("7k/8/8/8/8/4p3/4K3/8");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST TWO]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (4, 2)
        for(Position position: board.get_piece_at(Position(4, 1))->_get_attacks(&board))
        {
            if (!(position == Position(4, 2)))
            {
                std::cout << "[TEST TWO]: FAILED | EXPECTED: (4, 2) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }
    } while(false);

    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

    // TEST THREE: CAN THE KING TAKE A PAWN THAT'S DIAGONALLY IN FRONT OF IT?
    // This will put have the white king on (4, 1) and a black pawn on (5, 2). We'll see if the king can take the pawn.
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: CAN THE KING TAKE A PAWN THAT'S DIAGONALLY IN FRONT OF IT?" << std::endl;

    do
    {
        Board board("7k/8/8/8/8/5p2/4K3/8");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST THREE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (5, 2)
        for(Position position: board.get_piece_at(Position(4, 1))->_get_attacks(&board))
        {
            if (!(position == Position(5, 2)))
            {
                std::cout << "[TEST THREE]: FAILED | EXPECTED: (5, 2) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

    } while (false);

    std::cout << "---------------- [TEST THREE]: COMPLETED ----------------" << std::endl;
    
    // TEST FOUR: DOES THE KING PUT ITSELF IN CHECK? 
    // This will have a white king on (4, 1) and a black queen on (4, 2). We'll see if the king can move to (4, 2) since it would put itself in check.
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: DOES THE KING PUT ITSELF IN CHECK?" << std::endl;

    do
    {
        Board board("7k/8/8/8/8/4q3/4K3/8");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST FOUR]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (4, 2)
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            if (!(position == Position(4, 2)))
            {
                std::cout << "[TEST FOUR]: FAILED | EXPECTED: (4, 2) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Then just output all the movement positions for the king. Since as opposed to capture the king could move away from queen.
        std::cout << "[TEST FOUR]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    // TEST FIVE: DOES THE KING PUT ITSELF IN CHECK WHEN CAPTURING A PIECE?
    // This will have a white king (4, 1), a black queen (4, 3), and a black pawn (4, 2). We'll see if the king can capture the pawn since it would put itself in check.
    std::cout << "[TEST FIVE]: BEGIN" << std::endl;
    std::cout << "[TEST FIVE]: DOES THE KING PUT ITSELF IN CHECK WHEN CAPTURING A PIECE?" << std::endl;

    do
    {
        Board board("7k/8/8/8/4q3/4p3/4K3/8");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST FIVE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll check to see if the only attack position is (4, 2)
        for(Position position: board.get_piece_at(Position(4, 1))->_get_attacks(&board))
        {
            if (!(position == Position(4, 2)))
            {
                std::cout << "[TEST FIVE]: FAILED | EXPECTED: CANNOT CAPTURE (4, 2) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Then just output all the movement positions for the king. Since as opposed to capture the king could move away from queen.
        std::cout << "[TEST FIVE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

        // Then also output the attacks just to make sure. 
        std::cout << "[TEST FIVE]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 1))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);

    return 0;
}

int test_knight()
{
    std::cout << "---------------- [TEST]: KNIGHT STARTING... ----------------" << std::endl;
    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // This will start with a white knight on (0, 1) and we'll see if potential movement position are only (2, 0), (2, 2), (1, 3).
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/8/8/8/8/N7/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // We'll use an if-statement to determine whether the only movement positions are (2, 0), (2, 2), (1, 3).
        for(Position position: board.get_piece_at(Position(0, 1))->_get_movements(&board))
        {
            if (!(position == Position(2, 0) || position == Position(2, 2) || position == Position(1, 3)))
            {
                std::cout << "[TEST ONE]: FAILED | EXPECTED: (2, 0), (2, 2), (1, 3) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                return -1; // Kill the process since we failed the test. If we want to continue the test then we can just remove this line to see the rest of the output.
            }
        }

        // Now we'll just print out all the possible movements of the knight.
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(0, 1))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: ARE THE AUTO-GENERATED ATTACKS CORRECT?
    // This will start with a black knight on (3, 3) and a white pawn on (4, 5). We'll see if the only attack position is (4, 5).
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: ARE THE AUTO-GENERATED ATTACKS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/4P3/8/3n4/8/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST TWO]: IS BOARD CORRECT?" << std::endl;

        // We'll use an if-statement to determine whether the only attack position is (4, 5).

        for(Position position: board.get_piece_at(Position(3, 3))->_get_attacks(&board))
        {
            if (!(position == Position(4, 5)))
            {
                std::cout << "[TEST TWO]: FAILED | EXPECTED: (4, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Now we'll just output all the attacks to make sure ther aren't any extra. 
        std::cout << "[TEST TWO]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(3, 3))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }

    } while (false);
    
    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

}

int test_pawn()
{
    std::cout << "---------------- [TEST]: PAWN STARTING... ----------------" << std::endl;

    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // Has two white pawns. One at (3, 3) and the other at (4, 4). There is a black pawn at (3, 5) we'll see if the only movement position for the first white pawn is (3, 4).
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/3p4/4P3/3P4/8/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // We'll use an if-statement to determine whether the only movement position is (3, 4).

        for(Position position: board.get_piece_at(Position(3, 3))->_get_movements(&board))
        {
            if (!(position == Position(3, 4)))
            {
                std::cout << "[TEST ONE]: FAILED | EXPECTED: (3, 4) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Now we'll just output all the movements to make sure ther aren't any extra.
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(3, 3))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: CAN THE PAWN TAKE UP AND LEFT?
    // The setup is the same as the last test but we'll see if the pawn at (4, 4) can take the pawn at (3, 5).
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: CAN THE PAWN TAKE UP AND LEFT?" << std::endl;

    // We don't need to print the board since we know it'll be right from the last one. 

    do
    {
        Board board("6k1/8/3p4/4P3/3P4/8/8/7K");

        // Now we check if the only attack position for the white pawn at (4, 4) is (3, 5).
        for(Position position: board.get_piece_at(Position(4, 4))->_get_attacks(&board))
        {
            if (!(position == Position(3, 5)))
            {
                std::cout << "[TEST TWO]: FAILED | EXPECTED: (3, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Now output the rest of the attacks position just to make sure there aren't any extra. 

    } while (false);

    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;
    
    // TEST THREE: CAN THE PAWN TAKE UP AND RIGHT?
    // The setup is the same as the last test but we'll see if the pawn at (4, 4) can take the pawn at (5, 5).
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: CAN THE PAWN TAKE UP AND RIGHT?" << std::endl;

    do
    {
        Board board("6k1/8/5p2/4P3/3P4/8/8/7K");

        // Print the board to make sure that it's correct. 
        board._print_board();

        std::cout << "[TEST THREE]: IS BOARD CORRECT?" << std::endl;

        // Now we check if the only attack position for the white pawn at (4, 4) is (5, 5).
        for(Position position: board.get_piece_at(Position(4, 4))->_get_attacks(&board))
        {
            if (!(position == Position(5, 5)))
            {
                std::cout << "[TEST THREE]: FAILED | EXPECTED: (5, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }
    } while (false);
    
    std::cout << "---------------- [TEST THREE]: COMPLETED ----------------" << std::endl;

    // TEST FOUR: CAN THE PAWN DOUBLE JUMP:
    // The white pawn will be at position (4, 1) and we'll see if it's possible to move the pawn to (4, 3) in one move.
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: CAN THE PAWN DOUBLE JUMP?" << std::endl;

    do
    {
        Board board("6k1/8/8/8/8/8/4P3/7K");

        // Print the board to make sure that it's correct.
        board._print_board();

        std::cout << "[TEST FOUR]: IS BOARD CORRECT?" << std::endl;

        // Now we check if the only movement position for the white pawn at (4, 1) is (4, 3), and (4, 2).
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            if (!(position == Position(4, 3) || position == Position(4, 2)))
            {
                std::cout << "[TEST FOUR]: FAILED | EXPECTED: (4, 3), (4, 2) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Print all movements just to make sure it's all right. 
        std::cout << "[TEST FOUR]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(4, 1))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;

    // TEST FIVE: CAN THE PAWN UNDERSTAND EN PASSANT?
    // We'll have to do a simulation here. There will be a white pawn on (1, 4) and a black pawn on (2, 6). The black pawn will then be updated to move to it's double jump position
    // at (2, 4). Then we'll see if the white pawn can take the black pawn at (2, 4) using en passant.
    std::cout << "[TEST FIVE]: BEGIN" << std::endl;
    std::cout << "[TEST FIVE]: CAN THE PAWN UNDERSTAND EN PASSANT?" << std::endl;

    do
    {
        Board board("6k1/2p5/8/1P6/8/8/8/7K");

        // Print the board to make sure that it's correct.
        board._print_board();

        std::cout << "[TEST FIVE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll update the black pawn to move to it's double jump position.

        Position old_position(2, 6);

        Position new_position(2, 4);

        board._update(old_position, new_position);

        // Now we'll check if the only attack position for the white pawn at (1, 4) is (2, 5).

        for(Position position: board.get_piece_at(Position(1, 4))->_get_attacks(&board))
        {
            if (!(position == Position(2, 5)))
            {
                std::cout << "[TEST FIVE]: FAILED | EXPECTED: (2, 5) | ACTUAL: " << position._horizontial << ", " << position._vertical << std::endl;
                break;
            }
        }

        // Output the board again at the end to make sure that it all worked. 
        board._print_board();

    } while (false);

    std::cout << "---------------- [TEST FIVE]: COMPLETED ----------------" << std::endl;
    
}

int test_queen()
{
    std::cout << "---------------- [TEST]: QUEEN STARTING... ----------------" << std::endl;
    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // The white queen is on (2, 2) and we'll simply output all the movements that are generated for the queen and leave it to the user to see if they're correct. 
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/1P6/4P3/8/2Q5/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible movements of the queen.
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(2, 2))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);

    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: ARE THE AUTO-GENERATED ATTACKS CORRECT (DIAGONAL)?
    // The white queen is still on (2, 2) and there are multiple black pawns that can be taken by the queen on positions (5, 2), (4, 4), (2, 5), and (1, 1).
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: ARE THE AUTO-GENERATED ATTACKS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/2p5/4p3/8/2Q2p2/1p6/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST TWO]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible movements of the queen.
        std::cout << "[TEST TWO]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(2, 2))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);

    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

    // TEST THREE: MAKE SURE THE QUEEN ISN'T SEEING THROUGH PIECES.
    // We'll have the queen on (2, 2). Simply output the attacks of the queen and we'll leave it for the user to determine whether it's correct or not. 
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: MAKE SURE THE QUEEN ISN'T SEEING THROUGH PIECES." << std::endl;

    do
    {
        Board board("2p3k1/8/2P5/8/8/2Q2p1p/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST THREE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible attacks of the queen.
        std::cout << "[TEST THREE]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(2, 2))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);
    
    std::cout << "---------------- [TEST THREE]: COMPLETED ----------------" << std::endl;
}

int test_rook()
{
    // TEST ONE: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?
    // We'll have a white rook at (2, 2) with one white pawn at its way on (5, 2). We'll output all the movements and see if they're correct.
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: ARE THE AUTO-GENERATED MOVEMENTS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/8/8/8/2R2P2/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST ONE]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible movements of the rook.
        std::cout << "[TEST ONE]: GENERATED MOVEMENTS" << std::endl;
        for(Position position: board.get_piece_at(Position(2, 2))->_get_movements(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);

    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;
    
    // TEST TWO: ARE THE AUTO-GENERATED ATTACKS CORRECT?
    // We'll have a white rook at (2, 2) with two black pawns with one on (5, 2) and another on (2, 5) and we'll see if those are in the attack positions. 
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: ARE THE AUTO-GENERATED ATTACKS CORRECT?" << std::endl;

    do
    {
        Board board("6k1/8/2p5/8/8/2R2p2/8/7K");

        // Output the board just to make sure the right setup is there.
        board._print_board();

        std::cout << "[TEST TWO]: IS BOARD CORRECT?" << std::endl;

        // Now we'll just print out all the possible movements of the rook.
        std::cout << "[TEST TWO]: GENERATED ATTACKS" << std::endl;
        for(Position position: board.get_piece_at(Position(2, 2))->_get_attacks(&board))
        {
            std::cout << position._horizontial << ", " << position._vertical << std::endl;
        }
    } while (false);

    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;
}

int test_engine()
{
    // TEST ONE: CAN THE ENGINE MAKE RANDOM LEGAL MOVE FROM STARTING POSITION?
    std::cout << "[TEST ONE]: BEGIN" << std::endl;
    std::cout << "[TEST ONE]: CAN THE ENGINE MAKE A LEGAL MOVE FROM STARTING POSITION?" << std::endl;

    do
    {
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b");
        Engine::get_random_move(&board);
    } while (false);
    
    std::cout << "---------------- [TEST ONE]: COMPLETED ----------------" << std::endl;

    // TEST TWO: CAN THE ENGINE MAKE A RANDOM LEGAL MOVE IN MID-GAME?
    std::cout << "[TEST TWO]: BEGIN" << std::endl;
    std::cout << "[TEST TWO]: CAN THE ENGINE MAKE A RANDOM LEGAL MOVE IN MID-GAME?" << std::endl;

    do
    {
        Board board("r3k3/1pp1b1pp/p2q1p1n/1B4B1/1n2p1b1/N1Pp2P1/PP2Q2P/R4RK1 b");
        Engine::get_random_move(&board);
    } while (false);
    
    std::cout << "---------------- [TEST TWO]: COMPLETED ----------------" << std::endl;

    // TEST THREE: SAME AS TEST TWO BUT DIFFERNT CONDITIONS
    std::cout << "[TEST THREE]: BEGIN" << std::endl;
    std::cout << "[TEST THREE]: CAN THE ENGINE MAKE A RANDOM LEGAL MOVE IN MID-GAME?" << std::endl;

    do 
    {
        Board board("r5k1/2p1b3/2rP1p1n/pB1P2B1/1n1Nppb1/N1p3P1/P3Q2P/R5K1 w");
        Engine::get_random_move(&board);
    } while (false);

    std::cout << "---------------- [TEST THREE]: COMPLETED ----------------" << std::endl;

    // TEST FOUR: CAN THE ENGINE MAKE A RANDOM LEGAL MOVE IN END-GAME?
    std::cout << "[TEST FOUR]: BEGIN" << std::endl;
    std::cout << "[TEST FOUR]: CAN THE ENGINE MAKE A RANDOM LEGAL MOVE IN END-GAME?" << std::endl;

    do
    {
        Board board("6r1/3k4/8/p2p2P1/4P3/8/5K1p/1R6 w");
        Engine::get_random_move(&board);
    } while (false);
    
    std::cout << "---------------- [TEST FOUR]: COMPLETED ----------------" << std::endl;

    // TEST FIVE: BOT SIMULATION WITH ITSELF. 
    std::cout << "[TEST FIVE]: BEGIN" << std::endl;
    std::cout << "[TEST FIVE]: BOT SIMULATION WITH ITSELF." << std::endl;

    do
    {
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");

        // We'll just have the bot play itself for 10 moves. 
        for(int i = 0; i < 10; i++)
        {
            std::cout << "MOVE NUMBER: " << i << std::endl;
            board = *Engine::get_random_move(&board);
        }
    } while (false);
}
