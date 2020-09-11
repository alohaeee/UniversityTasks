var fromInput = document.getElementById("from");
var toInput = document.getElementById("to");
var stepInput = document.getElementById("step");
var functionSelect = document.getElementById("function");


function check(from,to,step)
{
    if(isNaN(from)) throw("От должно быть числом");
    if(isNaN(to)) throw("До должно быть числом");
    if(isNaN(step)) throw("Шаг должен быть числом");

    if((from > to && step > 0) || (from < to && step < 0)) 
    {
        throw("ЧТО-ТО НЕ ВЕРНО!!!!!!ПРИСМОТРИТЕСЬ");
    }

    if(!step) throw("Шаг равен нулю");
    
};

function makeTable(event)
{
    event.preventDefault();
    try
    {
        let functionType = functionSelect.value;

        let from = parseFloat(fromInput.value);
        let to = parseFloat(toInput.value);
        let step = parseFloat(stepInput.value);

        check(from,to,step);
        

        let table = 
        `
        <table align="center" border="1" style="border-collapse: collapse;">
            <tr align="middle">
                <td colspan="2">Угол</td>
                <td rowspan="2">${functionType}</td>
            </tr>
            <tr>
                <td>в градусах</td>
                <td>в радианах</td>
            </tr>    
        `
        let comparer = step > 0 ? (a,b)=>{ return a<=b; } : (a,b)=>{return a>=b};
        for(; comparer(from,to); from+=step)
        {
            let radian = from * Math.PI / 180; 
            
            let value;
            
            if(functionType == "tan" && Math.abs(from)>=90 && Math.abs(from)%90==0 && Math.abs(from)/2%2==1) value = "inf"
            else
            {
                value = calcTable(functionType,radian);
                value = value.toFixed(3);
            }


            radian = radian.toFixed(3);
            table += 
            `
                <tr>
                    <td> ${from} </td>
                    <td> ${radian}</td>
                    <td> ${value} </td>
                </tr>
            `
        }
        table +=         `
        </table>
        `
        
        openNewWindow(table);
    }
    catch(error)
    {
       alert(error);
       console.log(functionSelect.value);
    }
}

function calcTable(functionType, radian)
{
    
    return eval("Math." + functionType + "(" + radian + ")");
}

function openNewWindow(html)
{
    let newWindow = window.open("","","width=650,height=400");
    newWindow.document.write(html);
}