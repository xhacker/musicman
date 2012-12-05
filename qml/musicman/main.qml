import QtQuick 1.1

Rectangle {
    id: rect
    width: 640
    height: 480

    Rectangle {
        id: rect_start
        x: 120
        y: 50
        width: 400
        height: 100
        color: activeFocus ? "#ffeb86" : "#ccc"
        border.color: activeFocus ? "#ffb515" : "#aaa"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        signal start()
        onStart: text_start.text = "Start Fired"

        focus: true
        KeyNavigation.down: rect_tutorial; KeyNavigation.up: rect_exit
        Keys.onPressed: {
            if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter) {
                event.accepted = true
                start()
            }
        }

        Text {
            id: text_start
            color: parent.border.color
            text: qsTr("Start")
            font.family: "Futura"
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 56
        }

        MouseArea {
            id: mouse_area_start
            anchors.fill: parent
            onClicked: parent.start()
        }
    }

    Rectangle {
        id: rect_tutorial
        x: 120
        y: 190
        width: 400
        height: 100
        color: activeFocus ? "#ffa0a0" : "#ccc"
        border.color: activeFocus ? "#c90016" : "#aaa"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 0

        signal tutorial()
        onTutorial: text_tutorial.text = "Tutorial Fired"

        KeyNavigation.down: rect_exit; KeyNavigation.up: rect_start
        Keys.onPressed: {
            if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter) {
                event.accepted = true
                tutorial()
            }
        }

        Text {
            id: text_tutorial
            color: parent.border.color
            text: qsTr("Tutorial")
            font.family: "Futura"
            font.pixelSize: 56
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouse_area_tutorial
            anchors.fill: parent
            onClicked: parent.tutorial()
        }
    }

    Rectangle {
        id: rect_exit
        x: 120
        y: 330
        width: 400
        height: 100
        color: activeFocus ? "#bbf790" : "#ccc"
        border.color: activeFocus ? "#13ad50" : "#aaa"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 0

        signal exit()
        onExit: Qt.quit()

        KeyNavigation.down: rect_start; KeyNavigation.up: rect_tutorial
        Keys.onPressed: {
            if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter) {
                event.accepted = true
                exit()
            }
        }

        Text {
            id: text_exit
            color: parent.border.color
            text: qsTr("Exit")
            font.family: "Futura"
            font.pixelSize: 56
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouse_area_exit
            anchors.fill: parent
            onClicked: parent.exit()
        }
    }
    states: [
        State {
            name: "State1"
        }
    ]
}
