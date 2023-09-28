import QtQuick
import QtQuick.Window
import "components"

Window {
    id: window
    visible: true
    width: 1366
    height: 768
    flags: Qt.FramelessWindowHint | Qt.Window

    MouseArea {
        id: resizeArea
        width: 20
        height: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        cursorShape: Qt.SizeFDiagCursor

        property real startX: 0
        property real startY: 0

        onPressed: {
            startX = mouse.x;
            startY = mouse.y;
        }

        onMouseXChanged: {
            var dx = mouse.x - startX;
            if (window.width + dx > window.minimumWidth) {
                window.width += dx;
            }
        }

        onMouseYChanged: {
            var dy = mouse.y - startY;
            if (window.height + dy > window.minimumHeight) {
                window.height += dy;
            }
        }
    }

    Column {
        anchors.fill: window

        TitleBar {
            id: titleBar
            width: window.width
            MouseArea {
                id: dragArea
                anchors.fill: parent
                onPressed: { window.startSystemMove(); }
            }
        }

        Rectangle {
            id: mainWindow
            height: window.height - titleBar.height
            width: window.width

            Row {
                anchors.fill: mainWindow
                NaviRail {
                    height: mainWindow.height
                }
            }
        }
    }
}
