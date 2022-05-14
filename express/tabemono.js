//Define the canvas
const canvas = document.querySelector('.gameCanvas');

//change the width and height of the canvas element
canvas.width = 1300;
canvas.height = 650;

//Define the canvas as a 2d canvas
const ctx = canvas.getContext('2d');

//Loop Function
window.main = () =>
{
    window.requestAnimationFrame(main);
}

//Call Loop
main();

window.addEventListener('mousedown', (e) => 
{

});

window.addEventListener('mousemove', (e) =>
{

});

window.addEventListener('mouseup', (e) =>
{

});

