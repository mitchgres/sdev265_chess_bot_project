board = include/engine/board/Board.cpp
engine = include/engine/Engine.cpp
piece = include/engine/piece/Piece.cpp
bishop = include/engine/piece/bishop/Bishop.cpp
king = include/engine/piece/king/King.cpp
knight = include/engine/piece/knight/Knight.cpp
pawn = include/engine/piece/pawn/Pawn.cpp
queen = include/engine/piece/queen/Queen.cpp
rook = include/engine/piece/rook/Rook.cpp
position = include/engine/position/Position.cpp
server = include/server/Server.cpp

test-exe = test/Test.cpp
main-exe = source/main.cpp

board-object = Board.o
engine-object = Engine.o
piece-object = Piece.o
bishop-object = Bishop.o
king-object = King.o
knight-object = Knight.o
pawn-object = Pawn.o
queen-object = Queen.o
rook-object = Rook.o
position-object = Position.o
server-object = Server.o

link-board: $(board)
	g++ -c -g $(board) $(piece) $(position) $(pawn) $(rook) $(knight) $(bishop) $(queen) $(king)

link-engine: $(engine)
	g++ -c -g $(engine) 

link-piece: $(piece)
	g++ -c -g $(piece) $(position) $(board)

link-bishop: $(bishop)
	g++ -c -g $(bishop) $(piece)

link-king: $(king)
	g++ -c -g $(king) $(piece)

link-knight: $(knight)
	g++ -c -g $(knight) $(piece)

link-pawn: $(pawn)
	g++ -c -g $(pawn) $(piece)

link-queen: $(queen)
	g++ -c -g $(queen) $(piece)

link-rook: $(rook)
	g++ -c -g $(rook) $(piece)

link-position: $(position)
	g++ -c -g $(position)

link-all-engine: 
	make link-board
	make link-engine
	make link-piece
	make link-bishop
	make link-king
	make link-knight
	make link-pawn
	make link-queen
	make link-rook
	make link-position

test-engine: $(test-exe) $(board-object) $(engine-object) $(piece-object) $(bishop-object) $(king-object) $(knight-object) $(pawn-object) $(queen-object) $(rook-object) $(position-object)
	g++ $(test-exe) $(board-object) $(engine-object) $(piece-object) $(bishop-object) $(king-object) $(knight-object) $(pawn-object) $(queen-object) $(rook-object) $(position-object)

clean:
	rm -f a.out $(server-object) $(board-object) $(engine-object) $(piece-object) $(bishop-object) $(king-object) $(knight-object) $(pawn-object) $(queen-object) $(rook-object) $(position-object) test-engine

# Only used to run test to make sure everything is working.

test-and-run-engine:
	make clean
	make link-all-engine
	make test-engine
	./a.out

# Used if you want to access the engine through sockets. 

link-server: $(server)
	g++ -c -g $(server)

start-server: $(server)
	g++ $(server) $(board-object) $(engine-object) $(piece-object) $(bishop-object) $(king-object) $(knight-object) $(pawn-object) $(queen-object) $(rook-object) $(position-object)

run-server: 
	./a.out