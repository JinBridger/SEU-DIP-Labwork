import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window
    visible: true
    width: 640
    height: 480
    flags: Qt.FramelessWindowHint // 设置窗口标志为无边框，这将隐藏标题栏

    MouseArea {
        id: dragArea
        anchors.fill: parent
        onPressed: { window.startSystemMove(); }
    }

    Text {
        text: "Drag me anywhere"
        anchors.centerIn: parent
    }
}
