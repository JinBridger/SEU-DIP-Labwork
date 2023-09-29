import QtQuick 2.15

Rectangle {
    height: 50
    z: 1
    color: "#590de4"

    Row {
        anchors.verticalCenter: parent.verticalCenter
        Item {
            height: 10
            width: 20
        }

        Text {
            text: "SEU DIP Labwork"
            color: "white"
            font.pointSize: 12
            font.family: sarasaSemibold.font.family
            font.weight: sarasaSemibold.font.weight
        }
    }
}