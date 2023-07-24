// sound cache
var soundClack = getSoundGitHub('clack.ogg');
var soundClick = getSoundGitHub('quietclick.ogg');

function getSoundGitHub(fileName) {
    var audio = new Audio('https://github.com/mitchgres/sdev265_chess_bot_project/blob/main/assets/sound/' + fileName + '?raw=true');
    return audio;
}

const playerName = "Player";

const logDiv = document.querySelector('#log');



window.onload = function() {
    document.querySelector('#messageInput').addEventListener('keypress', function(e) {
        soundClick.cloneNode().play();
        let key = e.which || e.keyCode;
        if (key === 13 && !e.shiftKey) { // 'Enter' key without holding 'shift'
            let message = this.value;
            if (message) {
                // create new divs for chatbox, playername and message
                let newChatBoxDiv = document.createElement('div');
                let newMessageDiv = document.createElement('div');
                let newNameDiv = document.createElement('div');

                // set text content and css class for each new div
                newChatBoxDiv.classList.add('chatBox');
                newNameDiv.textContent = playerName + ":";
                newNameDiv.classList.add('playerName');
                newMessageDiv.innerHTML = message.replace(/\n/g, "<br/>"); // replace newline characters with <br/>
                newMessageDiv.classList.add('chat');

                // add playername and message text to chatbox, add chatbox to log
                logDiv.appendChild(newChatBoxDiv);
                newChatBoxDiv.appendChild(newNameDiv);
                newChatBoxDiv.appendChild(newMessageDiv);

                this.value = '';
                
                soundClack.play();
            }
        }
    });
}

// create mutationobserver instance to handle addition of new divs
let observer = new MutationObserver(function() {
    logDiv.scrollTop = logDiv.scrollHeight;
})

// configuration of the observer: childList to true (as new divs will be added as child)
let config = { childList: true };

// pass in the target node (logDiv) along with the observer options
observer.observe(logDiv, config);