#include <climits>
#include <algorithm>
#include "Engine.h"

Engine::Engine(int searchDepth) : _searchDepth(searchDepth) {}

int Engine::_minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || board.isGameOver()) {
        return board.evaluate();
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        std::vector<Move> moves = board.generateMoves();

        for (const auto& move : moves) {
            board.makeMove(move);
            int eval = _minimax(board, depth - 1, alpha, beta, false);
            board.undoMove();

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cutoff
            }
        }

        return maxEval;
    } else {
        int minEval = INT_MAX;
        std::vector<Move> moves = board.generateMoves();

        for (const auto& move : moves) {
            board.makeMove(move);
            int eval = _minimax(board, depth - 1, alpha, beta, true);
            board.undoMove();

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cutoff
            }
        }

        return minEval;
    }
}

Move Engine::_findBestMove(Board& board, int depth) {
    int maxEval = INT_MIN;
    Move bestMove;

    std::vector<Move> moves = board.generateMoves();

    for (const auto& move : moves) {
        board.makeMove(move);
        int eval = _minimax(board, depth - 1, INT_MIN, INT_MAX, false);
        board.undoMove();

        if (eval > maxEval) {
            maxEval = eval;
            bestMove = move;
        }
    }

    return bestMove;
}

void Engine::makeAIMove(Board& board) {
    Move bestMove = _findBestMove(board, _searchDepth);
    board.makeMove(bestMove);
}
