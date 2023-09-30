import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Icon.js" as MdiFont

Rectangle {
    height: 50
    z: 1
    color: "#590de4"

    RowLayout {
        anchors.fill: parent
        Item {
            width: 10
        }

        Text {
            text: "SEU DIP Labwork"
            color: "white"
            font.pointSize: 12
            font.family: sarasaSemibold.font.family
            font.weight: sarasaSemibold.font.weight
            Layout.alignment: Qt.AlignLeft
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            hoverEnabled: false
            background: Rectangle { color: "transparent" }
            onClicked: Qt.quit()
            contentItem: Text {
                text: MdiFont.Icon.close
                color: "white"
                font.family: materialIcon.font.family
                font.pointSize: 18
            }
            Layout.alignment: Qt.AlignRight
        }

        Item {
            width: 5
        }
    }
}
