var divVariantBlock = document.getElementById("variantBlock");


function creatorVariant(buttonLabel : string, dataL_0 : string, dataL_1 : string) : HTMLDivElement
{
    let divVariant = document.createElement("div");
    divVariant.setAttribute("name", "variant");

    let input = document.createElement("input");
    input.setAttribute("type", "button");
    input.setAttribute("value", buttonLabel);
    input.addEventListener("click", (event) => 
        {
            let target = event.target as HTMLInputElement;
            let sideDiv = target.parentElement.getElementsByTagName("div").item(0) as HTMLDivElement;
            let display = window.getComputedStyle(sideDiv).getPropertyValue("display");

            if (display == "block") 
            {
                sideDiv.style.display = "none";
            }
            else 
            {
                sideDiv.style.display = "block";
            }
        });
    

    let divData = document.createElement("div");

    let taskList = document.createElement("ol");
    let l_0 = document.createElement("li");
    let l_1 = document.createElement("li");
    l_0.textContent = dataL_0;
    l_1.textContent = dataL_1;
    taskList.appendChild(l_0);
    taskList.appendChild(l_1);

    divData.appendChild(taskList);

    divVariant.appendChild(input);
    divVariant.appendChild(divData);
    divVariantBlock.appendChild(divVariant);
    input.click();
    
    return divVariant;
}

function initialization() : void
{
    window.fetch("data.txt").then((response) =>
    {
        return response.text(); 
    }).then((text) =>
    {   
        let data = text;

        let indexLeft = data.indexOf("Вариант",0);       
        let indexRight = data.indexOf("Вариант",1);

        while(indexLeft !=-1 && indexRight != -1)
        {
            
            let variantData = data.slice(indexLeft,indexRight);
            let head = variantData.slice(0,variantData.indexOf("1.")-1);
            let task_0 = variantData.slice(variantData.indexOf("1.")+2,variantData.indexOf("2."));
            let task_1 = variantData.slice(variantData.indexOf("2.")+2);

            creatorVariant(head,task_0,task_1);
            
            data = data.slice(indexRight);
            indexLeft = data.indexOf("Вариант",0);
            indexRight = data.indexOf("Вариант",1);
        }

    }).catch((reason) =>
    {
        alert(reason);
    });

    window.fetch("request.json").then((response) =>
    {
        return response.json();
    }).then((value) =>
    {
        let sort : Array<JSON> = value["sort"];
        let find : Array<JSON> = value["find"];

        let make = (data :HTMLElement,array: Array<JSON>)=>
            {
                let helper = document.createElement("ul");
                for(let j = 0; j < array.length; j++)
                {
                    if(data.textContent.toLowerCase().indexOf(array[j]["search"]) != -1)
                    {
                        let ulData = document.createElement("li");
                        let url = document.createElement("a");

                        url.textContent = array[j]["label"];
                        url.setAttribute("href", array[j]["url"]);
                       
                        ulData.appendChild(url);
                        helper.appendChild(ulData);
                    }
                }
                data.appendChild(helper);
            }

        let children = divVariantBlock.children;
        
        for(let i = 1; i < children.length; i++)
        {
            let variantData = children.item(i).getElementsByTagName("div").item(0);
            let list = variantData.getElementsByTagName("ol").item(0);
            
            
            make(list.children.item(0),sort);
            make(list.children.item(1),find);
        }
            
        
    }).catch((reason) =>
    {
        alert(reason);
    })

   

    
    
//     divVariants.forEach((v) => 
//     {
//         let input = v.getElementsByTagName("input");
//         input.item(0).addEventListener("click", (event) => 
//         {
//             let target = event.target as HTMLInputElement;
//             let sideDiv = target.parentElement.getElementsByTagName("div").item(0) as HTMLDivElement;
//             let display = window.getComputedStyle(sideDiv).getPropertyValue("display");

//             if (display == "block") 
//             {
//                 sideDiv.style.display = "none";
//             }
//             else 
//             {
//                 sideDiv.style.display = "block";
//             }
//         });
//   });
}



window.addEventListener("load", initialization);