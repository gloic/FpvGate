document.getElementById('listenAll').addEventListener('click', function () {
    fetch('/listen-all')
        .then((response) => response.text())
        .then((data) => console.log(data))
        .catch((error) => console.error('Error:', error));
});

document.getElementById('stopListenAll').addEventListener('click', function () {
    fetch('/stop-listen-all')
        .then((response) => response.text())
        .then((data) => console.log(data))
        .catch((error) => console.error('Error:', error));
});
 
document.getElementById('listen-user').addEventListener('click', function () {
    fetch('/listen-user')
        .then((response) => response.text())
        .then((data) => console.log(data))
        .catch((error) => console.error('Error:', error));
});