var element = document.querySelector('.game');
var positionInfo = 475;
var xPosition = positionInfo / 2.5;

var gameElement = document.querySelector('.game');
var boardElement = document.querySelector('.board');

function positionBoard() {
    var parentWidth = gameElement.offsetWidth;
    boardElement.style.transform = 'translateX(' + ((parentWidth / 3) - xPosition) + 'px)';
    console.log(xPosition);
}

positionBoard();
window.addEventListener('resize', positionBoard);