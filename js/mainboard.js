/*
    !!IMPORTANT INFO!!
    server is temporarily within this directory, as it's the easiest place to put it lol
    to run it, call it ("./server.out") from an ubuntu terminal.
    after the server is online, the frontend should be good to launch (from port 5501, otherwise it won't work lel)
*/

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

    let fen = ChessBoard.objToFen(newPos);
    if (ChessBoard.objToFen(newPos) != ChessBoard.objToFen(oldPos)) {
        handleMove(fen)
            .then(newFen => {
                changeBoard(mainBoard, newFen);
            })
            .catch(error => {
                console.log(error);
            })
    }
    
}

function changeBoard(board, fen) {
    console.log(fen.slice(-2));
    fen = fen.slice(0, -2);
    board.position(fen, true);
}

async function handleMove(fen) {
    fen = fen + " b";
    console.log("sent:", fen);
    const url = `http://127.0.0.1:8080?fen=${encodeURIComponent(fen)}`;
    try {
        const response = await call(url);
        console.log("response:", response);
        return response;
    } catch (error) {
        console.log(error);
        throw error;
    }
}

async function call(url) {
    try {
        const response = await axios.get(url);
        const data = response.data;
        return data.fen;
    } catch (error) {
        if (error.response) {
            console.log(error.response.status);
        } else {
            console.log(error);
            console.log(error.message);
        }
        throw error;
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
    onDragStart: onDragStart,
    onMoveEnd: onMoveEnd
}
// this is supposed to scale the board with the website size but idk
var mainBoard = ChessBoard('board-object', mainConfig);

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