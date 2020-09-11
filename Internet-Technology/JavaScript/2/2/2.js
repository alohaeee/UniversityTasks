var imgOne = "imgOne.jpeg";
var labelOne = "смойлик один";
var imgTwo = "imgTwo.jpeg";
var labelTwo = "смойлик Два";

document.getElementById("i").src = imgOne;
document.getElementById("c").textContent = labelOne;
var isOne = true;

function parentEvent(event)
{
    var eventTarget = event.target;
    var idTarget = eventTarget.id;
    var docTarget = document.getElementById(idTarget);
    switch(idTarget)
    {                
        case "i":
            console.log(isOne);
            if(isOne)
            {
                docTarget.src = imgTwo;
                document.getElementById("c").textContent=labelTwo;
                isOne=false;
            }
            else
            {
                docTarget.src = imgOne;
                document.getElementById("c").textContent=labelOne;
                isOne=true;
            }
            break;
        case "c":
            docTarget.style.color = '#'+(Math.floor(Math.random()*0xFFFFFF)).toString(16);
            break;

    }

}