class Function
{
    constructor(name,exceptions=[])
    {
        this.name = name;
        this.exceptions = exceptions;
    }
    compute(degree)
    {
        if(this.exceptions.includes(degree)) return NaN;

        let radian=degree*Math.PI/180;
        return eval("Math." + this.name + "(" + radian.toString() + ")");
       
    }
    get name()
    {
        return this._name;
    }
    set name(name)
    {
        this._name = name;
    }
}

let funcs = new Array();
funcs.push(new Function("sin"));
funcs.push(new Function("cos"));
funcs.push(new Function("tan", [90,270]));

let currentFunc = 0;
let isBad = false;

let value = 0;

function onChangeCheck(input)
{
    value = input.value;

    try
    {
        value = parseInt(value, 10);
        if(isNaN(value)) throw new Error("Некорректный ввод градусов!");
        input.value = value.toString();

        if(value < 0 || value > 360) throw new Error("Угол должен быть больше нуля и меньше 360 градусов!");

        isBad=false;
    }
    catch(err)
    {
        alert(err);
        input.focus();
        input.select();
        isBad=true;
    }
}

function onChangeFunction(selection)
{
    let value = selection.value;
    currentFunc = funcs.findIndex(func => func.name == value);

    onChangeCheck(document.getElementById("d"));
}

function onSubmition()
{
    if(isBad) alert("Допущена ошибка в заполнении формы!");
    else
    {
        let answer = funcs[currentFunc].compute(value);
        answer = answer.toFixed(3);
        let p = document.getElementById("a");
        if(isNaN(answer)) 
        {
            p.textContent="inf";
        }
        else
        {
            p.textContent=funcs[currentFunc].name + "(" + value + String.fromCharCode(0x00B0) + ") = " + answer.toString();
        }
    }
    

}



