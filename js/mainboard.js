var mainConfig = 
{
    draggable: true,
    dropOffBoard: 'snapback',
    sparePieces: false,
    showNotation: false,
    height: mainBoardHeight + 'px'
}

var mainBoardHeight = document.querySelector('.chess-window').clientHeight;

// change this later
var mainBoard = ChessBoard('mainboard', mainConfig);

function setBoardButton()
{
    mainBoard.start();
}

function clearBoardButton()
{
    mainBoard.clear();
}

document.getElementById('setButton').addEventListener('click', setBoardButton);
document.getElementById('clearButton').addEventListener('click', clearBoardButton);