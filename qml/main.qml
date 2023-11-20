import QtQuick
import QtQuick.Window
import "components"

Rectangle {
    id: window
    // visible: true
    width: 1600
    height: 900
    // flags: Qt.FramelessWindowHint | Qt.Window

    FontLoader {
        id: sarasaRegular
        source: "qrc:/res/font/sarasa-ui-sc-regular.ttf"
    }

    FontLoader {
        id: sarasaSemibold
        source: "qrc:/res/font/sarasa-ui-sc-semibold.ttf"
    }

    FontLoader {
        id: materialIcon
        source: "qrc:/res/font/materialdesignicons-webfont.ttf"
    }

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
                appView.startSystemResize(edges);
            }
        }
    }

    Column {
        anchors.fill: window

        MouseArea {
            id: dragArea
            height: 50
            width: window.width
            onPressed: { appView.startSystemMove(); }
            TitleBar {
                id: titleBar
                width: window.width
            }
        }

        Rectangle {
            id: mainWindow
            height: window.height - titleBar.height
            width: window.width

            Row {
                anchors.fill: mainWindow
                NaviRail {
                    id: naviRail
                    height: mainWindow.height
                }

                Rectangle{
                    id: oriMapItemArea
                    height: mainWindow.height
                    width: (mainWindow.width - naviRail.width)/2
                    clip: true
                    color: "gray"

                    Image {
                        id: oriMapImg
                        x: oriMapItemArea.width/2-oriMapImg.width/2
                        y: oriMapItemArea.height/2-oriMapImg.height/2
                        source: "image://imgprovider/ori"

                        function reloadImage() {
                            source += "1"
                        }
                    }

                    Item {
                        id: oriHistogram
                        Rectangle {
                            width: 256
                            height: 128
                            color: "black"
                            opacity: 0.4
                            z: 100

                            Image {
                                id: oriMapImgHist
                                source: "image://imgprovider/hist_ori"
                                anchors.fill: parent
                                fillMode: Image.Stretch

                                function reloadImage() {
                                    source += "1"
                                }
                            }
                        }
                    }

                    MouseArea {
                        id: oriMapDragArea
                        width: oriMapImg.width * oriMapImg.scale
                        height: oriMapImg.height * oriMapImg.scale
                        anchors.centerIn: oriMapImg
                        drag.target: oriMapImg

                        onWheel: {
                            var delta = wheel.angleDelta.y/120;
                            if(delta > 0)
                            {
                                oriMapImg.scale = oriMapImg.scale/0.9
                            }
                            else
                            {
                                oriMapImg.scale = oriMapImg.scale*0.9
                            }
                        }
                    }
                }

                Rectangle {
                    width: 1
                    height: mainWindow.height
                    color: "black"
                }

                Rectangle{
                    id: mapItemArea
                    height: mainWindow.height
                    width: (mainWindow.width - naviRail.width)/2 -1
                    clip: true
                    color: "gray"

                    Image {
                        id: mapImg
                        x: mapItemArea.width/2-mapImg.width/2
                        y: mapItemArea.height/2-mapImg.height/2
                        source: "image://imgprovider/dst"

                        function reloadImage() {
                            source += "1"
                        }
                    }

                    Item {
                        id: distHistogram
                        Rectangle {
                            width: 256
                            height: 128
                            color: "black"
                            opacity: 0.4
                            z: 100

                            Image {
                                id: mapImgHist
                                source: "image://imgprovider/hist_dst"
                                anchors.fill: parent
                                fillMode: Image.Stretch

                                function reloadImage() {
                                    source += "1"
                                }
                            }
                        }
                    }

                    MouseArea {
                        id: mapDragArea
                        width: mapImg.width * mapImg.scale
                        height: mapImg.height * mapImg.scale
                        anchors.centerIn: mapImg
                        drag.target: mapImg

                        onWheel: {
                            var delta = wheel.angleDelta.y/120;
                            if(delta > 0)
                            {
                                mapImg.scale = mapImg.scale/0.9
                            }
                            else
                            {
                                mapImg.scale = mapImg.scale*0.9
                            }
                        }
                    }
                }
            }
        }
    }
}
