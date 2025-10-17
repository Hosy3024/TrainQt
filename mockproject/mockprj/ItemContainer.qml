import QtQuick 2.0

Item {
    property alias text: textID.text
    property alias txtVisible: textID.visible
    property alias sourceIcon: imageID.source

    Image {
        id: imageID
        anchors.centerIn: parent
        width: 20; height: 20
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: textID
        anchors.centerIn: parent
        font { pointSize: 16 }
    }
}
