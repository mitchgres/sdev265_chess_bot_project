const logDiv = document.querySelector('#log');

window.onload = function() {
    document.querySelector('#messageInput').addEventListener('keypress', function(e) {
        let key = e.which || e.keyCode;
        if (key === 13 && !e.shiftKey) { // 'Enter' key without holding 'shift'
            let message = this.value;
            if (message) {
                let newMessageDiv = document.createElement('div');
                newMessageDiv.innerHTML = message.replace(/\n/g, "<br/>"); // replace newline characters with <br/>
                newMessageDiv.classList.add('chat');
                logDiv.appendChild(newMessageDiv);
                this.value = '';
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