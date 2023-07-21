// sound cache
var soundPickup = getSoundGitHub('pickup.ogg');
var soundPlace = getSoundGitHub('place.ogg');

// sound playback function
function getSoundGitHub(fileName) {
    var audio = new Audio('https://github.com/mitchgres/sdev265_chess_bot_project/blob/main/assets/sound/' + fileName + '?raw=true');
    return audio;
}

// this is called when a piece is picked up
function onDragStart(source, piece, position, orientation)
{
    soundPickup.play();
}

// this is called when a piece is dropped
function onDrop(source, target, piece, newPos, oldPos, orientation)
{
    if (target != 'offboard') 
    {
        // this is called when a piece is dropped only on the board
        soundPlace.play();
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
    onDrop: onDrop,
    onDragStart: onDragStart
}

// this is supposed to scale the board with the website size but idk
var mainBoard = ChessBoard('board-object', mainConfig);

// more fucking scaling shit idk how this works
/* function resizeBoard()
{
    var boardContainer = document.querySelector('.board');
    var boardHeight = boardContainer.clientHeight;
    var boardWidth = boardContainer.clientWidth - 80;

    // set the new width and height on the board itself
    var boardElement = document.getElementById('board-object');
    boardElement.style.height = boardHeight + 'px';
    boardElement.style.width = boardWidth + 'px';
    console.log("div: " + boardHeight);
    console.log("board: " + boardElement.style.height);
    
    mainBoard.resize();
}

var debug_shouldResize = true;

if (debug_shouldResize)
{
    window.addEventListener('resize', resizeBoard);
    window.addEventListener('load', resizeBoard);
}

resizeBoard();

const boardContainer = document.querySelector('.board');
const resizeObserver = new ResizeObserver(entries => {
  for (let entry of entries) {
    const {width, height} = entry.contentRect;
    var boardElement = document.getElementById('board-object');
    boardElement.style.height = height + 'px';
    boardElement.style.width = width + 'px';
    mainBoard.resize();
  }
});
resizeObserver.observe(boardContainer); */

/* window.addEventListener('resize', function() {
    var gameWidth = document.querySelector('.game').clientWidth;
    console.log(gameWidth + "px");
}) */

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

// api
function get() {
    axios.get('https://api.example.com/home')
        .then(response => {
            // handle response data
            console.log(response.data);
        })
        .catch(error => {
            // handle error
            console.error(error);
        })
}