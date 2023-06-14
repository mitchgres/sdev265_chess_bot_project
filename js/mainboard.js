var mainBoardHeight = document.querySelector('.chess-window').clientHeight;

// change this later
var mainBoard = ChessBoard('mainboard',
{
    draggable: true,
    dropOffBoard: 'trash',
    sparePieces: true,
    height: mainBoardHeight + 'px'
});