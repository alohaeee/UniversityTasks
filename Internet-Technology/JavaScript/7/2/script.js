var table = document.getElementById("table");
var select = document.getElementById("select");



function enter()
{
    let id = select.value;

    let tr = document.getElementById(id.toString());

    let tds = tr.children;

    let price = document.getElementById("price").value;
    let count = document.getElementById("count").value;

    try
    {
       
        let isNum = /^\d+$/.test(count);    
        
        if(!isNum)
        {
            throw("Неккоректный ввод количества!");
        }
        isNum = /^\d*\.?\d+$/.test(price);
        if(!isNum)
        {
            throw("Неккоректный ввод цены!");
        }
         


        if(price <=0) throw("ЦЕНА!");
        if(count <=0) throw("Количество!");
        price = parseFloat(price).toFixed(2);
        if(tds[1].innerHTML == price && tds[2].innerHTML == count) return;
        tds[1].innerHTML = price.toString();
        tds[2].innerHTML = count.toString();
    
        counter();
    }
    catch(error)
    {
        alert(error);
    }

}


function counter()
{
    let tableChildren = table.children[0].children;
    let sum = 0;

    for(let i=1; i<(tableChildren.length-1); i++)
    {
        let row = tableChildren[i].children;
        sum += parseFloat(row[1].innerHTML) * parseInt(row[2].innerHTML);
        row[3].innerHTML = parseFloat(row[1].innerHTML) * parseInt(row[2].innerHTML).toFixed(2);
    }
    tableChildren[tableChildren.length-1].children[1].innerHTML = sum.toFixed(2);
}

counter();

