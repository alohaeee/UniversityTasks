var date = new Date();
var time;


function count()
{
    if(time > 1)
    {
        time--;

        date.setSeconds(0);
        date.setMinutes(0);
        date.setHours(0);

        date.setSeconds(time);

        return true;
    }
    date = new Date();
    return false;
}


function setDate(d)
{
    date = d
    time = date.getSeconds() + date.getMinutes() * 60 + date.getHours()* 60*60;
}
