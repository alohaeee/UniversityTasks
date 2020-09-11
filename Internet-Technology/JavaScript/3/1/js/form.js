


function formCheck()
{
    let f = document.getElementById("f");
    let m = document.getElementById('m');
    let n = document.getElementById("n");
    let strAlert = "";

    if(f.value == "") strAlert+="  *Мебель\n";
    
    if(m.value == "") strAlert+="  *Материал\n";

    if(n.value == "") strAlert+="  *Количество\n";

    if(strAlert.length==0)
    {
        let val = n.value;
        for(c of val)
        {
            if(c >= '0' && c<='9') continue;
            alert("В пункте количество товара должны быть только цифры!");
            return;
        }
        if(val == 0)
        {
            alert("Количество товаров не может быть равным нулю!");
            return;
        }
        document.forms[0].action="../php/order.php";
    }
    else
    {
        alert("Вы не заполнили следующие пункты формы:\n" + strAlert);
    }
    
    

    
}