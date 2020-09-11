


function changeColor(id)
{
    var object = document.getElementById(id);
    if(object.style.color == "black")
    {
        object.style.color = "white";
        object.style.background = "black";
        object.style.width = "max-content";
    }
    else
    {
        object.style.color = "black";
        object.style.background = "white";
        object.style.width = "max-content";
    }
}

function changeColorAll(id)
{
    var object = document.all.namedItem(id);
    if(object.style.color == "black")
    {
        object.style.color = "red";
        object.style.background = "yellow";
        object.style.width = "max-content";
    }
    else
    {
        object.style.color = "black";
        object.style.background = "white";
        object.style.width = "max-content";
    }
}