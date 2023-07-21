let timer1 = document.getElementById("timer1");
let timer2 = document.getElementById("timer2");

let fast = 300; // 5 minutes
let slow = 900; // 15 minutes

let player1Time = fast;
let player2Time = fast;

timer1.textContent = formatTime(player1Time);
timer2.textContent = formatTime(player2Time);

let interval;

function resetTimer(time) {
    stopTimer();
    player1Time = time;
    player2Time = time;
    timer1.textContent = formatTime(player1Time);
    timer2.textContent = formatTime(player2Time);
    startTimer();
}

function startTimer() {
    interval = setInterval(updateTimer, 1000);
}

function stopTimer() {
    clearInterval(interval);
}

function updateTimer() {
    if (player1Time > 0 && player2Time > 0)
    {
        player1Time--;
        player2Time--;
        timer1.textContent = formatTime(player1Time);
        timer2.textContent = formatTime(player2Time);
    }
}

function formatTime(time) {
    let minutes = Math.floor(time / 60);
    let seconds = time % 60;

    return `${padZero(minutes)}:${padZero(seconds)}`;
}

function padZero(num) {
    return num.toString().padStart(2, "0");
}

startTimer();

document.getElementById('setButton').addEventListener('click', function() {
    resetTimer(fast);
});
document.getElementById('clearButton').addEventListener('click', stopTimer);