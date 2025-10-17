import QtQuick 2.0

Item {
    property alias imgortxtVisible: imageID.visible
    property alias textbutton: textID.text
    property alias txtVisible: textID.visible

    Image {
        id: imageID
        anchors.centerIn: parent
        width: 20; height: 20
        source: "c.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: textID
        anchors.centerIn: parent
        font { pointSize: 16 }
    }
}
