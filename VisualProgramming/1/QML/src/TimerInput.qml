import QtQuick 2.12


Item {
    id: s
    property alias text: edit.text
    Row
    {

        Text {
            id: someText
            text: "Введите время: "
        }
        TextInput
        {
            id: edit
            text: "00"

            onTextEdited:
            {
                //console.log(edit.text)

                if(edit.text.length>2)
                {
                    edit.text = edit.text.slice(0,2)
                }
                else
                {
                    let c = edit.text[edit.text.length-1]
                    if(c < '0' || c > '9')
                    {
                        edit.text = edit.text.slice(0,text.length - 1)
                    }
                }
            }
            x: parent.x
        }
    }

}
