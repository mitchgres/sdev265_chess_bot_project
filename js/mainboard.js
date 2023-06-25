// sound playback function
function playSound(fileName)
{
    var audio = new Audio('../assets/sound/' + fileName);
    audio.play();
}

// this is called when a piece is picked up
function onDragStart(source, piece, position, orientation)
{
    var audio = new Audio('../assets/sound/pickup.ogg');
    audio.play();
}

// this is called when a piece is dropped
function onDrop(source, target, piece, newPos, oldPos, orientation)
{
    var audio;
    if (target != 'offboard') 
    {
        // this is called when a piece is dropped only on the board
        playSound('place.ogg');
    }
}



// these are the settings used by the mainBoard.
// settings are defined at https://chessboardjs.com/examples.html#2000
var mainConfig = 
{
    draggable: true,
    dropOffBoard: 'snapback',
    sparePieces: false,
    showNotation: false,
    height: mainBoardHeight + 'px',
    onDrop: onDrop,
    onDragStart: onDragStart
}

// this is supposed to scale the board with the website size but idk
var mainBoardHeight = document.querySelector('.chess-window').clientHeight;

var mainBoard = ChessBoard('mainboard', mainConfig);

// buttons
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