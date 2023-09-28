import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    id: naviRail
    width: 60
    height: parent.height

    Rectangle {
        id: naviRailBg
        width: parent.width
        height: parent.height
        color: "white"
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