function get_name_browser(){
    var ua = navigator.userAgent;    

    if (ua.search(/Chrome/) > 0) return 'Google Chrome';
    if (ua.search(/Firefox/) > 0) return 'Firefox';
    if (ua.search(/Opera/) > 0) return 'Opera';
    if (ua.search(/Safari/) > 0) return 'Safari';
    if (ua.search(/MSIE/) > 0 || ua.search(/Trident/)>0) return 'Internet Explorer';

    return 'Не определен';
}
 

if(get_name_browser() != "Internet Explorer") document.body.innerHTML = "Страница правильно отображается только в браузере Internet Explorer";
else
{
    flag=0;
    function rodEl(evt) 
    {  var e = evt || window.event;  //e -это объект event
       var elem = e.target || e.srcElement; //elem - элемент (объект), 
                                      // на котором произошло событие
       id1=elem.id
       z1=document.getElementById(id1)
     switch(id1)
     { case "k1": //Изменение цвета внешнего прямоугольника
          z=z1.style.backgroundColor 
          if(z!="red")z="red"
          else z="green"
          z1.style.backgroundColor=z
          break
       case "k2": 	//Изменение цвета внутреннего прямоугольника
          z=z1.style.backgroundColor 
          if(z!='rgb(0, 255, 255)'){z='rgb(0, 255, 255)'}
          else{z='rgb(0, 255, 0)'}
          z1.style.backgroundColor=z
          break
       case "B": //Изменение цвета заднего плана документа
          z=z1.style.backgroundColor 
          if(z!='rgb(190, 190, 190)'){z='rgb(190, 190, 190)'}
          else {z='rgb(0, 190, 190)'}
          z1.style.backgroundColor=z
          break
       case "HH": //Изменение цвета слова "Цвет"
          if(flag==0)
          {  document.getElementById(id1).style.color='rgb(170,0,170)';
             flag=1;
          }
          else 
          {   document.getElementById(id1).style.color='rgb(0,255,170)';
              flag=0;
          }
     }
    }
}