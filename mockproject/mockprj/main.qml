import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 300
    height: 420
    visible: true
    title: "Calculator"


    Rectangle {
        anchors.fill: parent
        color: "white"

        Rectangle {
            id: displayRect
            width: parent.width
            height: 100
            color: "white"
            anchors.top: parent.top

            Text {
                id: subDisplay
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 20
                anchors.topMargin: 15
                font.pixelSize: 18
                color: "black"
                text: calculator.subDisplay
            }

            Text {
                id: mainDisplay
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.rightMargin: 20
                anchors.bottomMargin: 15
                font.pixelSize: 40
                color: "black"
                text: calculator.display
            }
        }

        GridLayout {
            id: grid
            columns: 4
            anchors.top: displayRect.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 15

            Repeater {
                model: calculator.buttons
                delegate: Button {
                    id: buttonID
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: 22
                    Layout.columnSpan: calculator.buttonlayout[index]
                    background: Rectangle {
                        id: backgroundID
                        color: calculator.colors[index]
                        radius: 10
                        border.color: "black"
                    }

                    contentItem: ItemContainer {
                        id: textbuttonID
                        text: modelData
                        sourceIcon: calculator.buttoniconsource[index]
                        txtVisible: calculator.buttontxtvisible[index]
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            backgroundID.color = calculator.buttonhoveredcolors[index]
                        }
                        onPressed: {
                            buttonID.clicked()
                            backgroundID.color = calculator.buttonpressedcolors[index]
                        }
                        onReleased: {
                            backgroundID.color = calculator.buttonhoveredcolors[index]
                        }
                        onExited: {
                            backgroundID.color = calculator.colors[index]
                        }
                    }

                    onClicked: calculator.buttonClicked(textbuttonID.text)

                }
            }
        }
    }
}
