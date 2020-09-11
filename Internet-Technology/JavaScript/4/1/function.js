let images = new Array();
let select = document.getElementById("s");

function createImage(name,path=(name+".png"),optionText=name)
{
    images[name] = path;

    let option = document.createElement("option");
    option.innerHTML = optionText;
    option.value = name;
    select.appendChild(option);
}

createImage("smileOne", "imgs/imgOne.jpeg", "Смайлик");
createImage("smileTwo", "imgs/imgTwo.jpeg", "Смайлик два");
createImage("bed", "imgs/bed.png", "Кровати");
createImage("bed2", "imgs/bed2.jpg", "Кровати Два");
createImage("chest", "imgs/chest.png", "Сундуки");



let img = document.getElementById("i");
img.src = images["smileOne"];


function changeImage(sel)
{
    img.src = images[sel.value];
}