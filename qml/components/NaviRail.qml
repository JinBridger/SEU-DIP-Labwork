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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }
                onClicked: { appView.loadImg(); oriMapImg.reloadImage(); oriMapImgHist.reloadImage(); }
                contentItem: Text {
                    text: MdiFont.Icon.folder
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Load Image")
            }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        appView.saveImg();
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Save Image")

                contentItem: Text {
                    text: MdiFont.Icon.contentSave
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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        appView.swapImg();
                        mapImg.reloadImage();
                        mapImgHist.reloadImage();
                        oriMapImg.reloadImage();
                        oriMapImgHist.reloadImage();
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Swap left and right image")

                contentItem: Text {
                    text: MdiFont.Icon.shuffle
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
                            mapImgHist.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customFourierTrans();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Fourier Transform\n  · Left click for OpenCV version\n  · Right click for self-made version")

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
                            mapImgHist.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customHistogramEqualization();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Histogram Equalization\n  · Left click for OpenCV version\n  · Right click for self-made version")

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
                            mapImgHist.reloadImage();
                        } else if (mouse.button === Qt.RightButton) {
                            appView.customCLAHE();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("CLAHE\n  · Left click for OpenCV version\n  · Right click for self-made version")


                contentItem: Text {
                    text: MdiFont.Icon.imageAutoAdjust
                    color: "gray"
                    font.family: materialIcon.font.family
                    font.pointSize: 18
                }
            }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             if (mouse.button === Qt.LeftButton) {
            //                 appView.gaussianNoise();
            //                 mapImg.reloadImage();
            //                 mapImgHist.reloadImage();
            //             } else if (mouse.button === Qt.RightButton) {
            //                 appView.saltPepperNoise();
            //                 mapImg.reloadImage();
            //                 mapImgHist.reloadImage();
            //             }
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Add Noise\n  · Left click for gaussian noise\n  · Right click for salt & pepper noise")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.checkerboardPlus
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.medianFilter();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Median Filter")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.alphaMBoxOutline
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.averagingFilter();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Averaging Filter")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.alphaABoxOutline
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.adaptiveMedianFilter();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Adaptive Median Filter")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.alphaDBoxOutline
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.adaptiveLocalFilter();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Adaptive Local Noise Reduction Filter")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.alphaLBoxOutline
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.nonLocalMeansFilter();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Nonlocal Means")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.alphaNBoxOutline
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.gaussianBlur();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Gaussian Blur")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.blur
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.laplaceSharpening();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Laplace Sharpening")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.multiplicationBox
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             appView.unsharpMasking();
            //             mapImg.reloadImage();
            //             mapImgHist.reloadImage();
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("USM Sharpening")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.knife
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             if (mouse.button === Qt.LeftButton) {
            //                 appView.jpgCompress();
            //                 mapImg.reloadImage();
            //                 mapImgHist.reloadImage();
            //             } else if (mouse.button === Qt.RightButton) {
            //                 appView.jpg2KCompress();
            //                 mapImg.reloadImage();
            //                 mapImgHist.reloadImage();
            //             }
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("JPEG Compress\n  · Left click for JPEG Compress\n  · Right click for JPEG2000 Compress")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.fileJpgBox
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }

            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             if (mouse.button === Qt.LeftButton) {
            //                 appView.calcMSE();
            //             } else if (mouse.button === Qt.RightButton) {
            //                 appView.calcPSNR();
            //             }
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Diff\n  · Left click for MSE\n  · Right click for PSNR")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.vectorDifference
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }
            //
            // Item {
            //     width: 1
            //     height: 10
            // }
            //
            // ToolButton {
            //     background: Rectangle {
            //         width: parent.width
            //         color: "transparent"
            //     }
            //
            //     MouseArea {
            //         anchors.fill: parent
            //         acceptedButtons: Qt.AllButtons
            //
            //         onClicked: {
            //             if (mouse.button === Qt.LeftButton) {
            //                 appView.testFun();
            //             }
            //         }
            //     }
            //
            //     ToolTip.visible: hovered
            //     ToolTip.text: qsTr("Test Function")
            //
            //
            //     contentItem: Text {
            //         text: MdiFont.Icon.flask
            //         color: "gray"
            //         font.family: materialIcon.font.family
            //         font.pointSize: 18
            //     }
            // }

            Item {
                width: 1
                height: 10
            }

            ToolButton {
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.dilation();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Dilation")


                contentItem: Text {
                    text: MdiFont.Icon.arrowExpandAll
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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.erosion();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Erosion")


                contentItem: Text {
                    text: MdiFont.Icon.arrowCollapseAll
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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.globalThreshold();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Global Threshold")


                contentItem: Text {
                    text: MdiFont.Icon.squareWave
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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.otsuThreshold();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Otsu Threshold")


                contentItem: Text {
                    text: MdiFont.Icon.alphaOBox
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
                background: Rectangle {
                    width: parent.width
                    color: "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons

                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            appView.cannyBorderDetect();
                            mapImg.reloadImage();
                            mapImgHist.reloadImage();
                        }
                    }
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Canny Border Detect")


                contentItem: Text {
                    text: MdiFont.Icon.circleHalfFull
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