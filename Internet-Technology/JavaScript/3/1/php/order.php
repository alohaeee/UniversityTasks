<html>
    <head>
        <meta charset="utf8">
        <title>Order</title>
    <style>
        .p{
            text-indent: 4%;
        }
        
    </style>
    </head>

    <body bgcolor="pink" style="font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;font-size:30px"></body>
    <?php
        $f=$_POST["furniture"];
        $m=$_POST["material"];
        $n=$_POST["num"];
        echo "<h1>Ваш заказ принят</h1>";
        echo "<p class ='p'>Заказано изделие	– $f";
        echo "<p class ='p'>Материал	– $m";
        echo "<p class ='p'>Количество – $n</p>";
    ?>
    <a href="../html/index.html">Назад</a>
</html>

