import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "Icon.js" as MdiFont

Item {
    id: naviRail
    width: 60
    height: parent.height

    Rectangle {
        id: naviRailBg
        width: parent.width
        height: parent.height
        color: "white"

        Column {
            anchors.top:parent.top
            anchors.horizontalCenter:parent.horizontalCenter
            // anchors.fill: parent
            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }
                onClicked: console.log("clicked")
                contentItem: Text {
                    text: MdiFont.Icon.folder
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }
        }
    }

    DropShadow {
        anchors.fill: source
        horizontalOffset: -3
        radius: 15.0
        samples: 10
        color: "#80000000"
        source: naviRailBg
    }
}