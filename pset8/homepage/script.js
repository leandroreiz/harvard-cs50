function background() {
    randonNumber = Math.floor(Math.random() * 4) + 1;
    let background;
    if (randonNumber === 1) {
        background = "url(./img/brazil-bg.jpg)"
    }
    else if (randonNumber === 2) {
        background = "url(./img/lisbon-bg.jpg)"
    }
    else if (randonNumber === 3) {
        background = "url(./img/paris-bg.jpg)"
    }
    else {
        background = "url(./img/prague-bg.jpg)"
    }
    document.querySelector('.home').style.backgroundImage = background;
};

window.onload = background;