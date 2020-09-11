import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0

import "worker.js" as WorkerJs

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Таймер")
    color: "gray"
    id: window

    minimumHeight: 400
    minimumWidth: 400

    property alias cellColor: window.color


    Row
    {
        id: clockContainer
        spacing: 10
        width: parent.width*0.8
        height: parent.height*0.7
        anchors.centerIn: parent


        function setSizeOfText()
        {
            let len = clockContainer.children.length
            for (var i = 0; i < len; i++)
            {
                let child = clockContainer.children[i]
                child.font.pointSize = clockContainer.width/(len*1.4)
                child.anchors.verticalCenter=clockContainer.verticalCenter
            }

        }

        Component.onCompleted: setSizeOfText();
        onWidthChanged: setSizeOfText();
        onHeightChanged: setSizeOfText();



        Dialog
        {
            id: changeTimeDialog
            title: "Введите время"

            property Text markedText;

            TimerInput
            {
                id: timerInput
            }

            function openWithText(text)
            {
                if(!button.count)
                {
                    markedText = text
                    timerInput.text = markedText.text;
                    open()
                }


            }

            standardButtons: Dialog.No | Dialog.Apply

            onApply:
            {
                markedText.text = timerInput.text;
                close();

            }

            onNo:
            {
                timerInput.text = "00";
            }





        }

        Text {
            id: hoursText
            text: qsTr("00")


            MouseArea
            {
                anchors.fill: parent
                onClicked: changeTimeDialog.openWithText(hoursText)
            }

        }
        Text {
            id: separator1
            text: qsTr(":")

        }

        Text {
            id: minutesText
            text: qsTr("00")
            MouseArea
            {
                anchors.fill: parent
                onClicked: changeTimeDialog.openWithText(minutesText)
            }
        }
        Text {
            id: separator2
            text: qsTr(":")
        }
        Text {
            id: secondsText
            text: qsTr("00")
            MouseArea
            {
                anchors.fill: parent
                onClicked: changeTimeDialog.openWithText(secondsText)
            }
        }
    }

    Button
    {
        id: button
        text: "Start"
        property bool count: false
        property date timer: new Date()

        anchors.horizontalCenter: clockContainer.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70

        width: parent.width/2



        Timer
        {
            id: qtimer
            interval: 1000; running: false; repeat:true



            onTriggered:
            {

                if(WorkerJs.count())
                {

                    var to_normal_form = function (n)
                    {

                        if(n<10)
                        {
                            return '0' + n.toString()
                        }
                        return n.toString()
                    }

                    secondsText.text = to_normal_form(WorkerJs.date.getSeconds());
                    minutesText.text = to_normal_form(WorkerJs.date.getMinutes());
                    hoursText.text = to_normal_form(WorkerJs.date.getHours());
                }
                else
                {
                    //console.log("conc");
                    button.reset()
                }






            }
        }

        function reset()
        {
            button.text = "Start"
            background.color = "white"
            qtimer.running = false;

            pauseButton.enabled = false;

            count = false;


            hoursText.text = minutesText.text = secondsText.text = "00";

        }

        onClicked:
        {

            count = !count
            if(count)
            {
                pauseButton.enabled = true

                button.text = "Stop"
                background.color = "red"

                let t = new Date()

                t.setSeconds(Number(secondsText.text))
                t.setMinutes(Number(minutesText.text))
                t.setHours(Number(hoursText.text))

                WorkerJs.setDate(t);

                console.log(WorkerJs.date)

                qtimer.running = true

            }
            else
            {
                reset()

            }

        }

    }

    Button{
        id: pauseButton
        text:"Pause"

        anchors.horizontalCenter: clockContainer.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        width: parent.width/2

        enabled: false

        onClicked:
        {
            qtimer.running = !qtimer.running
            if(qtimer.running)
            {
               pauseButton.text = "Pause";
            }
            else
            {
                pauseButton.text = "Resume";
            }
        }



    }









}
