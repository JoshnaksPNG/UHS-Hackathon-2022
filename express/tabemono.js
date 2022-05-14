
//Define the canvas
const canvas = document.querySelector('.gameCanvas');

//change the width and height of the canvas element
canvas.width = 1300;
canvas.height = 650;

//Define the canvas as a 2d canvas
const ctx = canvas.getContext('2d');

//Load Images
const bground = new Image();
bground.src = './gameAssets/backgroundForNow.jpg';

const lbutt = new Image();
lbutt.src = "./gameAssets/LeftBracket.png";

const rbutt = new Image();
rbutt.src = "./gameAssets/RightBracket.png";

let currentAnID = 0;

//Classes
class Button 
{
    constructor(x, y, w, h)
    {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
    }

    checkClick(inX, inY)
    {
        if(inX <= this.x + this.w && inX >= this.x && inY <= this.y + this.h && inY >= this.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

//Game elements
LeftButton = new Button(300, 250, 110, 164);
RightButton = new Button(800, 250, 110, 164);

//Loop Function
window.main = () =>
{
    window.requestAnimationFrame(main);

    fetch("test.json").then(response => response.json()).then(data => 
    {
        ctx.drawImage(bground, 0, 0);
        ctx.drawImage(rbutt, 800, 250);
        ctx.drawImage(lbutt, 300, 250);


    });
    
}

//Call Loop
main();

window.addEventListener('mousedown', (e) => 
{
    if(LeftButton.checkClick(e.offsetX, e.offsetY))
    {
        creatureLeft(currentAnID);
    } else if (RightButton.checkClick(e.offsetX, e.offsetY))
    {
        creatureRight(currentAnID);
    }
});

window.addEventListener('mousemove', (e) =>
{

});

window.addEventListener('mouseup', (e) =>
{

});

window.addEventListener("beforeunload", function (e) 
{
    var confirmationMessage = "\o/";
  
    exit();
    (e || window.event).returnValue = confirmationMessage; //Gecko + IE
    return confirmationMessage;                            //Webkit, Safari, Chrome
});



//Hand Down Data
function creatureLeft (creatureID)
{
    return fetch('/request', 
    {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(
        {
            currentAction: "moveleft",
            currentAnimal: creatureID
        })
    });
}

function creatureRight (creatureID)
{
    return fetch('/request', 
    {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(
        {
            currentAction: "moveright",
            currentAnimal: creatureID
        })
    });
}

function killCreature (creatureID)
{
    return fetch('/request', 
    {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(
        {
            currentAction: "kill",
            currentAnimal: creatureID
        })
    });
}

function newCreature ()
{
    return fetch('/request', 
    {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(
        {
            currentAction: "new",
            currentAnimal: 0
        })
    });
}

function exit ()
{
    return fetch('/request', 
    {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(
        {
            currentAction: "exit",
            currentAnimal: 0
        })
    });
}