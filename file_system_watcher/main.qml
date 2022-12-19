import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
import Qt.labs.platform
import Qt.labs.qmlmodels 1.0
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
            width: 630
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
                    color: "transparent"
                    anchors.left: parent.left
                    TextArea {
                        id: folderPath
                        width: parent.width
                        height: parent.height
                        font.pixelSize: 15
                        Keys.onReturnPressed: {}
                        placeholderText : "Add path to watch"
                    }
                    Rectangle{
                        color: "transparent"
                        border.color: "black"
                        border.width: 1
                        radius: 10
                        anchors.fill: parent
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
                        boundsBehavior: Flickable.DragOverBounds
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
                                id: lvPath
                                height:parent.height
                                width:parent.width*0.8
                                anchors.left: parent.left
                                color:model.color
                                Label{
                                    anchors.leftMargin: 5
                                    anchors.left: parent.left
                                    text: model.path
                                }
                            }
                            Rectangle{
                                anchors.left: lvPath.right
                                height:parent.height
                                width:parent.width*0.2
                                color:model.color
                                Label{
                                    anchors.centerIn: parent
                                    text: "Remove"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        mPaths.removeItem(model.id)
                                    }
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
                Rectangle {
                    id: lvBorderInternal
                    width: parent.width*0.002
                    height: listViewWrap.height
                    color: "black"
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.8
                    anchors.top: listViewWrap.top
                }
            }
            Rectangle {
                id:tableViewWrap
                width: parent.width
                height: parent.height*0.35
                color:"transparent"
                border.color: "black"
                border.width: 1
                radius: 10
                anchors.top:rectangleWatchedPaths.bottom
                anchors.topMargin: 50
                TableView {
                    boundsBehavior: Flickable.StopAtBounds
                    columnSpacing: 0
                    rowSpacing: 1
                    width: parent.width*0.99
                    height: parent.height*0.99
                    anchors.centerIn: parent
                    anchors.fill: parent
                    clip: true
                    model: TVModel {
                        handler: tableHandler
                    }
                    delegate: Rectangle {
                        implicitWidth: tableViewWrap.width*model.size
                        implicitHeight: 50
                        color: model.color
                        Label {
                            font.pixelSize: 10
                            text: model.value
                            anchors.centerIn: parent
                       }
                    }
                }
                Rectangle {
                    color:"transparent"
                    border.color: "black"
                    border.width: 1
                    radius: 10
                    anchors.fill: parent
                }
                Rectangle {
                    color:"black"
                    width: 1
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.2
                }
                Rectangle {
                    color:"black"
                    width: 1
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.6+1
                }
                Rectangle {
                    color:"black"
                    width: 1
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.7+2
                }
            }

            Rectangle {
                id: controlButtons
                width: parent.width
                height: 30
                color:"transparent"
                anchors.top:tableViewWrap.bottom
                anchors.topMargin: 15
                Rectangle{
                    id: btnClear
                    width: 100
                    height: parent.height
                    color: "transparent"
                    border.width: 1
                    border.color: "black"
                    radius: 10
                    Text{
                        anchors.centerIn: parent
                        text: "Clear"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            tableHandler.initTable()
                        }
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
                        onClicked: {
                            folderWatcher.stopMonitoring()
                        }
                    }
                }
            }
        }
    }

    FolderDialog {
        id: folderDialog
        currentFolder: ""
        onFolderChanged: {
            mPaths.appendItem(folder);
        }
    }
}
