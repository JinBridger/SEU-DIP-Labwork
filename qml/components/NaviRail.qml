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
            Item {
                width: 1
                height: 10
            }
            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }
                onClicked: { appView.loadImg(); oriMapImg.reloadImage();}
                contentItem: Text {
                    text: MdiFont.Icon.folder
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.fourierTrans();
                            mapImg.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customFourierTrans();
                            mapImg.reloadImage();
                        }
                    }
                }

                contentItem: Text {
                    text: MdiFont.Icon.waveform
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.getHistogram();
                            mapImg.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customGetHistogram();
                            mapImg.reloadImage();
                        }
                    }
                }

                contentItem: Text {
                    text: MdiFont.Icon.chartHistogram
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.histogramEqualization();
                            mapImg.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customHistogramEqualization();
                            mapImg.reloadImage();
                        }
                    }
                }

                contentItem: Text {
                    text: MdiFont.Icon.chartBoxPlusOutline
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                hoverEnabled: false
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.CLAHE();
                            mapImg.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.CLAHE();
                            mapImg.reloadImage();
                        }
                    }
                }

                contentItem: Text {
                    text: MdiFont.Icon.imageAutoAdjust
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