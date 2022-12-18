import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import TitleBarHandlerPKG 1.0

Window {
    id:appWindow
    width: 700
    height: 720
    visible: true
    title: qsTr("File System Watcher")
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"
    property int buffX: ({})
    property int buffY: ({})
    property bool isFullscreen: False
    TitleBarHandler{
        id: titleBarHandler
    }

    Rectangle{
        width: parent.width
        height: parent.height
        border.color: black
        border.width: 1
        radius: 10
        Rectangle {
            id : windowTitle
            objectName: windowTitle
            width: parent.width
            height: 30
            border.width: 1
            radius: 10
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    buffX = mouseX
                    buffY = mouseY
                }
                onMouseXChanged: {
                    var dx = mouseX-buffX
                    appWindow.setX(appWindow.x+dx)
                }
                onMouseYChanged: {
                    var dy = mouseY-buffY
                    appWindow.setY(appWindow.y+dy)
                }
            }
            Rectangle{
                id: wrapClose
                color: "transparent"
                width: 20
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: 5
                Rectangle {
                    id: close
                    anchors.centerIn: parent
                    anchors.right: parent.right
                    width: parent.width
                    height: 20
                    border.color: "black"
                    border.width: 1
                    radius: 5
                    Image {
                        width: parent.width-10
                        height: parent.height-10
                        source: "icons/close.png"
                        autoTransform: true
                        anchors.centerIn: parent
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Qt.callLater(Qt.quit)
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: wrapFullscreen
                color: "transparent"
                width:20
                height:parent.height
                anchors.right: wrapClose.left
                anchors.rightMargin: 5
                Rectangle {
                    id: fullscreen
                    color: "transparent"
                    anchors.centerIn: parent
                    anchors.right: parent.right
                    width: parent.width
                    height: 20
                    border.color: "black"
                    border.width: 1
                    radius: 5
                    Image {
                        width: parent.width-10
                        height: parent.height-10
                        source: "icons/square.png"
                        autoTransform: true
                        anchors.centerIn: parent
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(isFullscreen){
                                    appWindow.showNormal()
                                    isFullscreen = false
                                } else {
                                    appWindow.showFullScreen()
                                    isFullscreen = true
                                }
                            }
                        }
                    }
                }
            }
            Rectangle{
                id:wrapMinimize
                color: "transparent"
                width:20
                height:parent.height
                anchors.right: wrapFullscreen.left
                anchors.rightMargin: 5
                Rectangle {
                    id: minimize
                    anchors.centerIn: parent
                    anchors.right: parent.right
                    width: parent.width
                    height: 20
                    border.color: "black"
                    border.width: 1
                    radius: 5
                    Image {
                        width: parent.width-10
                        height: parent.height-10
                        source: "icons/minimalize.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        autoTransform: true
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                appWindow.showMinimized()
                            }
                        }
                    }
                }
            }
            Text {
                text: "File System Watcher"
                font.pointSize: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
