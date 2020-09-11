var firstDiv = document.getElementsByTagName("div")[0].style;
var beforeStyle = new Array(3)
beforeStyle.color=firstDiv.color;
beforeStyle.background=firstDiv.background;
beforeStyle.fontSize=firstDiv.fontSize;

var clickStyle = Array(3);
clickStyle.color = "white";
clickStyle.background = "blue";
clickStyle.fontSize = "48px";


var beforeFlag = false;
function changFirst()
{          
    if(beforeFlag)
    {
        firstDiv.color = beforeStyle.color;
        firstDiv.background = beforeStyle.background;
        firstDiv.fontSize = beforeStyle.fontSize;
        firstDiv.width = "max-content";
        beforeFlag = !beforeFlag;
    }
    else
    {
        firstDiv.color = clickStyle.color;
        firstDiv.background = clickStyle.background;
        firstDiv.fontSize = clickStyle.fontSize;
        firstDiv.width = "max-content";
        beforeFlag = !beforeFlag;
    }
}

function changeBGColor(object, bgcolor)
{
    object.style.background = bgcolor;
    object.style.width = "max-content";
}