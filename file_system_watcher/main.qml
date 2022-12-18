import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
import Qt.labs.platform
import FolderTracker 1.0

Window {
    id:appWindow
    width: 700
    height: 720
    visible: true
    title: qsTr("File System Watcher")
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"
    property int buffX
    property int buffY
    property bool isFullscreen: false


    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"
        border.width: 1
        radius: 10   
        Rectangle {
            id : windowTitle
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
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            appWindow.showMinimized()
                        }
                    }
                }
            }
            Label {
                text: "File System Watcher"
                font.pointSize: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Rectangle{
            id: appBody
            width: parent.width*0.9
            height: 690
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: windowTitle.bottom
            color: "transparent"
            Rectangle{
                id: rectangleFolderPath
                color: "transparent"
                height: 30
                width: parent.width
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: parent.height*0.03
                Rectangle{
                    id: folderPathWrap
                    width: parent.width * 0.75
                    height: parent.height
                    border.color: "black"
                    border.width: 1
                    radius: 10
                    color: "transparent"
                    anchors.left: parent.left
                    ScrollView{
                        ScrollBar.horizontal.size: parent.width/folderPath.width
                        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
                        ScrollBar.vertical.interactive: false
                        width: parent.width*0.97
                        height: parent.height*0.90
                        anchors.centerIn: parent
                        TextArea {
                            id: folderPath
                            width: parent.width
                            height: parent.height
                            font.pixelSize: 15
                            Keys.onReturnPressed: {}
                            placeholderText : "Add path to watch"
                        }
                    }
                }
                Rectangle {
                    width: parent.width*0.2
                    border.color: "black"
                    border.width: 1
                    radius: 10
                    height: parent.height
                    anchors.right: parent.right
                    Label {
                        text: "Add"
                        font.pixelSize: 20
                        anchors.centerIn: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(folderPath.text){
                                mPaths.appendItem(folderPath.text)
                            } else {
                                folderDialog.open()
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: rectangleWatchedPaths
                width: parent.width
                height:parent.height*0.25
                anchors.top: rectangleFolderPath.bottom
                anchors.topMargin: parent.height*0.03
                Label{
                    id: labelWatchedPaths
                    text: "Watched paths"
                    font.pointSize: 13
                }
                Rectangle {
                    id:listViewWrap
                    width:parent.width
                    height: parent.height*0.9
                    anchors.top: labelWatchedPaths.bottom
                    anchors.topMargin:7
                    ListView{
                        id: lv
                        height: parent.height
                        width: parent.width
                        clip: true
                        anchors.fill: parent
                        model: LVModel {
                            list: mPaths
                        }

                        delegate: RowLayout{
                            width: listViewWrap.width
                            height: 20
                            Rectangle{
                                id: path
                                height:parent.height
                                width:parent.width*0.797
                                color:model.color
                                Label{
                                    anchors.left: parent.left
                                    anchors.leftMargin: parent.width*0.02
                                    text: model.path
                                }
                            }
                            Rectangle{
                                id: lvSep
                                height:parent.height
                                width:parent.width*0.003
                                color: "black"
                                anchors.left: path.right
                            }
                            Rectangle{
                                anchors.left: lvSep.right
                                height:parent.height
                                width:parent.width*0.2
                                color:model.color
                                Label{
                                    anchors.centerIn: parent
                                    text: "Remove"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: mPaths.removeItem(model.id)
                                }
                            }
                        }
                    }
                }
                Rectangle {
                    id: lvBorder
                    width:listViewWrap.width
                    height:listViewWrap.height
                    border.color: "black"
                    border.width: 1
                    color: "transparent"
                    radius: 10
                    anchors.top: listViewWrap.top
                }
            }
            Rectangle {
                id: controlButtons
                width: parent.width
                height: 30
                color:"transparent"
                anchors.top:rectangleWatchedPaths.bottom
                anchors.topMargin: 40
                Rectangle{
                    id: btnClear
                    width: 100
                    height: parent.height
                    color: "transparent"
                    border.width: 1
                    border.color: "black"
                    radius: 10
                    Label{
                        anchors.centerIn: parent
                        text: "Clear"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                    }
                }
                Rectangle{
                    id: btnStart
                    width: 100
                    height: parent.height
                    color: "transparent"
                    border.width: 1
                    border.color: "black"
                    radius: 10
                    anchors.left: btnClear.right
                    anchors.leftMargin:50
                    Label{
                        anchors.centerIn: parent
                        text: "Start"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            folderWatcher.startMonitoring()
                        }
                    }
                }
                Rectangle{
                    id: btnStop
                    width: 100
                    height: parent.height
                    color: "transparent"
                    border.width: 1
                    border.color: "black"
                    radius: 10
                    anchors.left: btnStart.right
                    anchors.leftMargin:50
                    Label{
                        anchors.centerIn: parent
                        text: "Stop"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                    }
                }
            }
        }
    }

    FolderDialog {
        id: folderDialog
        currentFolder: ""
        folder: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]
        onFolderChanged: {
            mPaths.appendItem(folder);
        }
    }
}
