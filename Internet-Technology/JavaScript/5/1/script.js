let rect = document.getElementById("rect");


let centerX;
let centerY;
let radius;
let min;

let time = 24;
let deltaRadius = 2;

let t = 0;
let deltaT = 0.1;
{
    let style = window.getComputedStyle(document.body);
    let width = parseInt(style.width.substr(0,style.width.length-2));
    let height = parseInt(style.height.substr(0,style.height.length-2));

    centerX = width/2;
    centerY = height/2;

    min = Math.min(width,height);
    radius = min/12;
}


setInterval(move,time);

function move()
{
    if(radius > min || radius < min/12) deltaRadius*=-1;
    if(t > 2*Math.PI) t = t - 2*Math.PI;

    let x = radius * Math.cos(t);
    let y = radius * Math.sin(t);

    rect.style.left = centerX + x + "px";
    rect.style.top = centerY + y + "px";

    radius += deltaRadius;
    t+=deltaT;    
}

move();