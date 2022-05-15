
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

let sendID = 1;

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

const head = new Image();
const body = new Image();
head.src = "./animalAssets/heads/ape.png";
body.src = "./animalAssets/bodies/cat.png";

//Loop Function
window.main = () =>
{
    window.requestAnimationFrame(main);

    fetch("test.json").then(response => response.json()).then(data => 
    {
        //Work With Current Data
        head.src = "./animalAssets/heads/" + yoinkHead(data.currentanimal.head);
        body.src = "./animalAssets/bodies/" + yoinkBody(data.currentanimal.chest);
        currentAnID = data.currentanimal.id;

        ctx.drawImage(bground, 0, 0);
        ctx.drawImage(rbutt, 800, 250);
        ctx.drawImage(lbutt, 300, 250);
        ctx.drawImage(body, 400, 200);
        ctx.drawImage(head, 400, 100);

        ctx.font = '12px serif';
        ctx.fillText(data.attributes, 10, 50);
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
            currentAnimal: creatureID,
            stamp: sendID
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
            currentAnimal: creatureID,
            stamp:sendID
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
            currentAnimal: creatureID,
            stamp: sendID
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
            currentAnimal: 0,
            stamp: sendID
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
            currentAnimal: 0,
            stamp:sendID
        })
    });
}


//Data Processing
function yoinkHead(head)
{
    switch(head)
    {
        case "bear":
            return "bear.png";
            break;
        case "zebra":
            return "zebra.png";
            break;
        case "tiger":
            return "tiger.png";
            break;
        case "hippo":
            return "hippo.png";
            break;
        case "lion":
            return "lion.png";
            break;
        case "rhino":
            return "rhino.png";
            break;
        case "boar":
            return "boar.png";
            break;
        case "ape":
            return "ape.png";
            break;
        case "giraffe":
            return "girrafe.png";
            break;
        case "fox":
            return "fox.png";
            break;
        case "elephant":
            return "elephant.png";
            break;
        case "deer":
            return "deer.png";
            break;
        case "gator":
            return "gator.png";
            break;
        case "yak":
            return "yak.png";
            break;
        case "panda":
            return "panda.png";
            break;
    }
}

function yoinkBody(chest)
{
    switch(chest)
    {
        case "bear":
            return "dog.png";
            break;
        case "zebra":
            return "mouse.png";
            break;
        case "tiger":
            return "cat.png";
            break;
        case "hippo":
            return "pig.png";
            break;
        case "lion":
            return "cat.png";
            break;
        case "rhino":
            return "pig.png";
            break;
        case "boar":
            return "pig.png";
            break;
        case "ape":
            return "rabbit.png";
            break;
        case "giraffe":
            return "bear.png";
            break;
        case "fox":
            return "dog.png";
            break;
        case "elephant":
            return "pig.png";
            break;
        case "deer":
            return "penguin.png";
            break;
        case "gator":
            return "rabbit.png";
            break;
        case "yak":
            return "snake.png";
            break;
        case "panda":
            return "mouse.png";
            break;
    }
}