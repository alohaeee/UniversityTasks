var canvas: HTMLCanvasElement = document.getElementById("canvas") as HTMLCanvasElement;
var context : CanvasRenderingContext2D = canvas.getContext("2d");

class Rectangle
{
    private _rect : {x:number,y:number,w:number,h:number};
    public onFocus: boolean;
    constructor(w:number,h:number)
    {
        this._rect = {
            x: 0,
            y: 0,
            w: w,
            h: h
        }
        this._rect.x = (canvas.width-this._rect.w)/2;
        this._rect.y = (canvas.height-this._rect.h)/2;
    }

    draw()
    {
        context.fillRect(this._rect.x,this._rect.y,this._rect.w,this._rect.h);
        context.strokeRect(this._rect.x,this._rect.y,this._rect.w,this._rect.h);
    }
    setPosition(position : {x:number,y:number}) : void
    {
        let newX = position.x-this._rect.w/2
        let newY = position.y-this._rect.h/2
        if(newX + this._rect.w> canvas.width)
        {
            newX=canvas.width - this._rect.w;
        }
        if(newY + this._rect.h > canvas.height)
        {
            newY=canvas.height - this._rect.h;
        }
        if(newX < 0) 
        {
            newX=0;
        }
        if(newY < 0)
        {
            newY=0;
        } 
        this._rect.x = newX;
        this._rect.y = newY;
    }
    isWithin(position : {x:number,y:number}) : boolean
    {
        if(this._rect.x + this._rect.w < position.x || this._rect.x > position.x) return false;
        if(this._rect.y + this._rect.h < position.y || this._rect.y > position.y) return false;
        return true;
    }
}
var rect = new Rectangle(50,50);

window.addEventListener("load",initialization);

canvas.addEventListener("click", mouseClick);
function getMousePos(event : MouseEvent) 
{
    let rect = canvas.getBoundingClientRect();
    return {
      x: event.clientX - rect.left,
      y: event.clientY - rect.top
    };
}

function mouseClick()
{
    let event: MouseEvent = window.event as MouseEvent;
    let position = getMousePos(event);

    if(rect.isWithin(position))
    {
        if(rect.onFocus)
        {
            window.removeEventListener("mousemove",draw);
        }
        else
        {
            window.addEventListener("mousemove",draw);
        }
        rect.onFocus = !rect.onFocus;
    }
    
}

function initialization() : void
{
    context.fillStyle = "palevioletred";
    context.save();
    rect.draw();
}

function draw() : void
{
    let event: MouseEvent = window.event as MouseEvent;

    context.clearRect(0,0,canvas.width,canvas.height);

    let position = getMousePos(event);

    rect.setPosition(position);
    rect.draw();
}


