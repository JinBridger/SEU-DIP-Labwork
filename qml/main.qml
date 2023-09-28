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
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton

        property int edges: 0;
        property int edgeOffest: 5;

        function setEdges(x, y) {
            edges = 0;
            if(x < edgeOffest) edges |= Qt.LeftEdge;
            if(x > (width - edgeOffest))  edges |= Qt.RightEdge;
            if(y < edgeOffest) edges |= Qt.TopEdge;
            if(y > (height - edgeOffest)) edges |= Qt.BottomEdge;
        }

        cursorShape: {
            return !containsMouse ? Qt.ArrowCursor:
                   edges == 3 || edges == 12 ? Qt.SizeFDiagCursor :
                   edges == 5 || edges == 10 ? Qt.SizeBDiagCursor :
                   edges & 9 ? Qt.SizeVerCursor :
                   edges & 6 ? Qt.SizeHorCursor : Qt.ArrowCursor;
        }

        onPositionChanged: setEdges(mouseX, mouseY);
        onPressed: {
            setEdges(mouseX, mouseY);
            if(edges && containsMouse) {
                startSystemResize(edges);
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
