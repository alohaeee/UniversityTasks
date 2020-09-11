var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");
var Rectangle = /** @class */ (function () {
    function Rectangle(w, h) {
        this._rect = {
            x: 0,
            y: 0,
            w: w,
            h: h
        };
        this._rect.x = (canvas.width - this._rect.w) / 2;
        this._rect.y = (canvas.height - this._rect.h) / 2;
    }
    Rectangle.prototype.draw = function () {
        context.fillRect(this._rect.x, this._rect.y, this._rect.w, this._rect.h);
        context.strokeRect(this._rect.x, this._rect.y, this._rect.w, this._rect.h);
    };
    Rectangle.prototype.setPosition = function (position) {
        var newX = position.x - this._rect.w / 2;
        var newY = position.y - this._rect.h / 2;
        if (newX + this._rect.w > canvas.width) {
            newX = canvas.width - this._rect.w;
        }
        if (newY + this._rect.h > canvas.height) {
            newY = canvas.height - this._rect.h;
        }
        if (newX < 0) {
            newX = 0;
        }
        if (newY < 0) {
            newY = 0;
        }
        this._rect.x = newX;
        this._rect.y = newY;
    };
    Rectangle.prototype.isWithin = function (position) {
        if (this._rect.x + this._rect.w < position.x || this._rect.x > position.x)
            return false;
        if (this._rect.y + this._rect.h < position.y || this._rect.y > position.y)
            return false;
        return true;
    };
    return Rectangle;
}());
var rect = new Rectangle(50, 50);
window.addEventListener("load", initialization);
canvas.addEventListener("click", mouseClick);
function getMousePos(event) {
    var rect = canvas.getBoundingClientRect();
    return {
        x: event.clientX - rect.left,
        y: event.clientY - rect.top
    };
}
function mouseClick() {
    var event = window.event;
    var position = getMousePos(event);
    if (rect.isWithin(position)) {
        if (rect.onFocus) {
            window.removeEventListener("mousemove", draw);
        }
        else {
            window.addEventListener("mousemove", draw);
        }
        rect.onFocus = !rect.onFocus;
    }
}
function initialization() {
    context.fillStyle = "palevioletred";
    context.save();
    rect.draw();
}
function draw() {
    var event = window.event;
    context.clearRect(0, 0, canvas.width, canvas.height);
    var position = getMousePos(event);
    rect.setPosition(position);
    rect.draw();
}
