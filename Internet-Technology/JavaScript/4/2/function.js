let backgroundGraphic = document.getElementById("bg");
let computedStyle = window.getComputedStyle(backgroundGraphic);
let currentStyle = 0;

let pointContainer = document.createElement("div");
pointContainer.id = "point_container";

let svgContainer = document.getElementById("svg_container");

let canvasContainer = document.createElement("canvas");
canvasContainer.id = "canvas_container";

let drawStyles = new Array();
drawStyles.push(pointContainer);
drawStyles.push(svgContainer);
drawStyles.push(canvasContainer);

let aOld=0;
let bOld=0;

backgroundGraphic.append(drawStyles[currentStyle]);

document.getElementsByName("drawstyle").forEach((r, value=0) => 
{
    r.value=value.toString();
    value++;
});


function chooseDrawStyle(radio)
{
    currentStyle = parseInt(radio.value);

    clear(backgroundGraphic);

    backgroundGraphic.append(drawStyles[currentStyle]);
}

function line(x1,y1,x2,y2, size)
{
    x1 = Math.floor(x1);
    x2 = Math.floor(x2);
    y1 = Math.floor(y1);
    y2 = Math.floor(y2);
    let deltaSize = size/2;
    let ready_line = "";
    let one_point = '<img src="Tochka.bmp" width=' + size + ' height=' + size + ' style="position:absolute;';
    
    let x = x1;
    let y = y1;
    while (x <= x2 || y < y2) {
        ready_line += one_point + 'top:' + (y -deltaSize) + 'px; left:' + (x -deltaSize) + 'px">';

        if (x <= x2)
            x++;
        if (y < y2)
            y++;
    }
    
    pointContainer.innerHTML += ready_line;
}
function ellipseWithPoint(a,b,x1,y1,size)
{
    let x;
    let y;
    let deltaSize = size/2;
    
    let ready_line = "";
    let one_point = '<img src="Tochka.bmp" width=' + size + ' height=' + size + ' style="position:absolute;';
    for(let t=0;t<=Math.PI*2; t+=0.01)
    {
        x = a * Math.cos(t); 
        y = b * Math.sin(t);

        ready_line += one_point + 'top:' + (y1 + y - deltaSize) + 'px; left:' + (x1 + x - deltaSize) + 'px">';
    }
    pointContainer.innerHTML += ready_line;
}
function pointDraw(a,b, centerX,centerY,width,height)
{

    line(centerX,0,centerX,height,2); 
    line(0,centerY,width,centerY,2);

    ellipseWithPoint(a,b, centerX,centerY, 2);
}

function svgDraw(a,b,centerX,centerY,width,height)
{
    let code = '<line x1="0" y1="' + centerY + '" x2="' + width + '" y2="' + centerY + '" style="stroke:#000; stroke-width: 2">' + '</line>';
    code += '<line x1="' + centerX +  '" y1="' + 0 + '" x2="' + centerX + '" y2="' + height + '" style="stroke:#000; stroke-width: 2">' + '</line>';
    code += '<ellipse cx="' + centerX + '" cy="' + centerY + '" rx="' + a + '" ry="' + b + '" style="fill: none; stroke:#000; stroke-width: 2" />';
    svgContainer.innerHTML = code;
}
function canvasDraw(a,b,centerX,centerY,width,height)
{
    let context = canvasContainer.getContext('2d');
    
    canvasContainer.width = width;
    canvasContainer.height = height;

    context.lineWidth = 2;
    context.beginPath();
    context.moveTo(0,centerY);
    context.lineTo(width,centerY);
    context.moveTo(centerX,0);
    context.lineTo(centerX,height);
    context.stroke();
    
    context.beginPath();
    context.ellipse(centerX, centerY, a, b, 0, 0, Math.PI * 2);
    context.stroke();
}

function clear(element)
{
    while (element.firstChild) {
        element.removeChild(element.firstChild);
    }
}

function draw()
{
    let a = document.getElementById("a").value;
    let b = document.getElementById("b").value;

    if(!a.length || !b.length) 
    {
        alert("a и b должны быть введены");
        return;
    }

    if(a!=bOld || b!=bOld)
    {
       
    
        a = parseInt(a);
        b = parseInt(b);
        if(isNaN(a) || isNaN(b)) 
        {
            alert("a и должны быть цифрами");
            return;
        }
        

        computedStyle = window.getComputedStyle(backgroundGraphic);

        let height = parseInt(computedStyle.height.slice(0,computedStyle.height.length-2));
        let width = parseInt(computedStyle.width.slice(0,computedStyle.width.length-2));
        let centerY = height/2;
        let centerX = width/2;

        if(a>width || b > height) 
        {
            alert("Слишком большие параметры");
            return;
        }
        // Save current a and b.
        aOld = a;
        bOld = b;

        
        clear(backgroundGraphic);
        clear(pointContainer);
        clear(svgContainer);

  
        pointDraw(aOld,bOld,centerX,centerY,width,height);
        svgDraw(aOld,bOld,centerX,centerY,width,height);
        canvasDraw(aOld,bOld,centerX,centerY,width,height);

        backgroundGraphic.append(drawStyles[currentStyle]);
    }
}

