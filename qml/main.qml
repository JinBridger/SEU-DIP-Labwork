import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        anchors.centerIn: parent
        text: "Hello, World!"
    }
    
    Button {
        x: 100
        y: 100
        text: "test"
        onClicked: {
            console.log("clicked")
        }
    }
}