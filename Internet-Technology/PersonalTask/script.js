var divVariantBlock = document.getElementById("variantBlock");
function creatorVariant(buttonLabel, dataL_0, dataL_1) {
    var divVariant = document.createElement("div");
    divVariant.setAttribute("name", "variant");
    var input = document.createElement("input");
    input.setAttribute("type", "button");
    input.setAttribute("value", buttonLabel);
    input.addEventListener("click", function (event) {
        var target = event.target;
        var sideDiv = target.parentElement.getElementsByTagName("div").item(0);
        var display = window.getComputedStyle(sideDiv).getPropertyValue("display");
        if (display == "block") {
            sideDiv.style.display = "none";
        }
        else {
            sideDiv.style.display = "block";
        }
    });
    var divData = document.createElement("div");
    var taskList = document.createElement("ol");
    var l_0 = document.createElement("li");
    var l_1 = document.createElement("li");
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
function initialization() {
    window.fetch("data.txt").then(function (response) {
        return response.text();
    }).then(function (text) {
        var data = text;
        var indexLeft = data.indexOf("Вариант", 0);
        var indexRight = data.indexOf("Вариант", 1);
        while (indexLeft != -1 && indexRight != -1) {
            var variantData = data.slice(indexLeft, indexRight);
            var head = variantData.slice(0, variantData.indexOf("1.") - 1);
            var task_0 = variantData.slice(variantData.indexOf("1.") + 2, variantData.indexOf("2."));
            var task_1 = variantData.slice(variantData.indexOf("2.") + 2);
            creatorVariant(head, task_0, task_1);
            data = data.slice(indexRight);
            indexLeft = data.indexOf("Вариант", 0);
            indexRight = data.indexOf("Вариант", 1);
        }
    })["catch"](function (reason) {
        alert(reason);
    });
    window.fetch("request.json").then(function (response) {
        return response.json();
    }).then(function (value) {
        var sort = value["sort"];
        var find = value["find"];
        var make = function (data, array) {
            var helper = document.createElement("ul");
            for (var j = 0; j < array.length; j++) {
                if (data.textContent.toLowerCase().indexOf(array[j]["search"]) != -1) {
                    var ulData = document.createElement("li");
                    var url = document.createElement("a");
                    url.textContent = array[j]["label"];
                    url.setAttribute("href", array[j]["url"]);
                    ulData.appendChild(url);
                    helper.appendChild(ulData);
                }
            }
            data.appendChild(helper);
        };
        var children = divVariantBlock.children;
        for (var i = 1; i < children.length; i++) {
            var variantData = children.item(i).getElementsByTagName("div").item(0);
            var list = variantData.getElementsByTagName("ol").item(0);
            make(list.children.item(0), sort);
            make(list.children.item(1), find);
        }
    })["catch"](function (reason) {
        alert(reason);
    });
}
window.addEventListener("load", initialization);
