import QtQuick 2.0
import OpenGLMesh 1.0

Item {

    MouseArea {
        property vector2d begin: Qt.vector2d(1,1)
        property vector2d current: Qt.vector2d(1,1)
        property vector2d axs: Qt.vector2d(1,1)
        property int angle
        hoverEnabled: false
        anchors.fill: parent
        onClicked: {
            console.log(mouseX,"and " , mouseY);

            begin.x= mouseX;
            begin.y = mouseY

        }
        onPositionChanged: {

            current.x = mouseX;
            current.y = mouseY;
            axs.x = current.x - begin.x;
            axs.y = current.y - begin.y;



            myMesh.axis = axs;
            begin = current;
    }
    }
    width: 320
    height: 480

    MeshQ {
        id: myMesh
        x: 0
        y: 50
        width: 320
        height: 319

     }
//! [1] //! [2]
    Rectangle {
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "The background here is a squircle rendered with raw OpenGL using the 'beforeRender()' signal in QQuickWindow. This text label and its border is rendered using QML"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
