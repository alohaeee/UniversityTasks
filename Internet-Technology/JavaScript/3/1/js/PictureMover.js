let pics = new Array();
pics.push("../img/bed.png");
pics.push("../img/bed2.jpg");
pics.push("../img/chest.png");

let currentPicture = 0;

document.getElementById("imgs").src = pics[currentPicture];
resetLabel();



let lastTime = Date.now();
let deltaTime = 0.0;
let changeTime = 10000;

let opacity = 1.0;
let opacityRange = 0.1;
let opacityDelta = 0.02;
let opactiySpeed = 20;

let fromTimeID = setInterval(changePictureFromTime, 1000);

let offTransperent = -1;

let isChanging = false;



function changePicture(move)
{
    currentPicture+=move;
    if(currentPicture >= pics.length) currentPicture = 0;
    else if(currentPicture < 0) currentPicture = pics.length - 1;

    if(!isChanging) downTransperent();
}

function changePictureFromTime()
{
    var curTime = Date.now();
    deltaTime += curTime - lastTime;
    lastTime=curTime;
    if(deltaTime >= changeTime) 
    {
        changePicture(1);
        deltaTime = 0;
    }
}
function downTransperent()
{
    isChanging = true;
    clearInterval(fromTimeID);
    offTransperent = setInterval(function()
    {
        if(opacity < opacityRange) 
        {
            clearInterval(offTransperent);
            document.getElementById("imgs").src = pics[currentPicture];
            resetLabel();
            upTransperent();
            return;
        }

        opacity-=opacityDelta;
        document.getElementById("imgs").style = "opacity: " + opacity.toString();
    }, opactiySpeed);
}
function upTransperent()
{
    offTransperent = setInterval(function()
    {
        if(opacity>1) 
        {
            clearInterval(offTransperent);
            
            deltaTime = 0;
            fromtTimeID = setInterval(changePictureFromTime,1000);

            isChanging = false;
            return;
        }
        opacity+=opacityDelta;
        document.getElementById("imgs").style = "opacity: " + opacity.toString();
    }, opactiySpeed);
}
function resetLabel()
{
    document.getElementById("curPic").textContent = (currentPicture+1).toString() + "/" + pics.length.toString();
}

