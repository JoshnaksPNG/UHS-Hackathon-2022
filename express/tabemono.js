//Define the canvas
const canvas = document.querySelector('.gameCanvas');

//change the width and height of the canvas element
canvas.width = 1300;
canvas.height = 650;

//Define the canvas as a 2d canvas
const ctx = canvas.getContext('2d');

//Load Images
const img = new Image();
img.src = './bigLion.jpg';

let lionX = 0;
let inSin = 0;
//Loop Function
window.main = () =>
{
    window.requestAnimationFrame(main);

    ctx.fillStyle = 'rgb(255,255,255)';
    ctx.fillRect(0,0,1300,650);
    ctx.drawImage(img, Math.sin(inSin/5)*50, 0);
    
    ++inSin;
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

