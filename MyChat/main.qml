import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Window {
    visible: true
    width: 800
    height: 800


    Rectangle {
        anchors.fill: parent
        anchors.margins: 10

        Rectangle {
            id: chatUi
            width: 500
            height: parent.height

            anchors.horizontalCenter: parent.horizontalCenter

            ListView {
                width: parent.width

                anchors.top: parent.top
                anchors.bottom: inputMessageContainer.top
                anchors.margins: 10

                verticalLayoutDirection: ListView.BottomToTop
                spacing: 5

                model: chatModel
                delegate: Component {
                    Rectangle {
                        id: messageContainer

                        width: parent.width * 0.8
                        height: messageText.height + 30

                        border.color: "#111111"
                        radius: 5

                        Component.onCompleted: {
                            if (isMyRole) {
                                messageContainer.anchors.right = parent.right;
                                messageContainer.color = "#ffffff";
                            } else {
                                messageContainer.anchors.left = parent.left;
                                messageContainer.color = "#ffffff"
                            }
                        }

                        Column {
                            id: messageTextField
                            anchors.fill: parent
                            anchors.margins: 10

                            Text {
                                color: "#111111"
                                font.family: "consolas"

                                text: "From: " + nameRole
                            }
                            Text {
                                id: messageText;
                                width: parent.width

                                color: "#111111"
                                font.family: "consolas"
                                font.pixelSize: 20

                                wrapMode: Text.WordWrap

                                text: textRole
                            }
                        } // Column
                    } // Rectangle
                } // Component
            } // ListView

            Rectangle {
                id: inputMessageContainer
                width: parent.width
                height: inputMessageTextEdit.height

                anchors.bottom: userInfoContainer.top
                anchors.margins: 5

                border.color: "black"
                radius: 5

                TextArea {
                    id: inputMessageTextEdit
                    width: parent.width

                    anchors.margins: 10
                    wrapMode: TextEdit.WordWrap
                } // TextEdit

                Button {
                    id: sendMessageButton

                    width: 100
                    height: 30

                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 5

                    contentItem: Text {
                        text: "Send"
                        color: "white"
                        font.family: "consolas"
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        color: "darkblue"
                        radius: 5
                    }

                    onClicked: {
                        userModel.sendMessage(inputMessageTextEdit.text);
                        inputMessageTextEdit.clear();
                    }
                }
            } // Rectangle inputMessageField

            Rectangle {
                id: userInfoContainer

                width: parent.width
                height: 40

                anchors.bottom: parent.bottom
                anchors.margins: 5

                border.color: "black"
                radius: 5

                state: "notChangingUsername"

                Row {
                    anchors.fill: parent
                    anchors.margins: 5

                    Text {
                        anchors.verticalCenter: parent.verticalCenter

                        text: "Username:"
                        font.family: "consolas"
                        font.pixelSize: 20

                    }

                    TextArea {
                        id: enterUsernameArea
                        width: 200
                        anchors.verticalCenter: parent.verticalCenter

                        font.family: "consolas"
                        font.pixelSize: 20
                        text: userModel.username
                        readOnly: true
                    }

                    Button {
                        id: changeUsernameButton
                        anchors.verticalCenter: parent.verticalCenter

                        background: Rectangle {
                            border.color: "black"
                            radius: 5
                        }

                        onClicked: {
                            if (userInfoContainer.state == "changingUsername") {
                                userInfoContainer.state = "notChangingUsername";
                                userModel.username = enterUsernameArea.text;
                            } else if (userInfoContainer.state == "notChangingUsername") {
                                userInfoContainer.state = "changingUsername";
                            }
                        }
                    }
                } // Row

                states: [
                    State {
                        name: "changingUsername"
                        PropertyChanges {
                            target: changeUsernameButton
                            text: "confirm"
                        }
                        PropertyChanges {
                            target: enterUsernameArea
                            readOnly: false
                        }
                    },
                    State {
                        name: "notChangingUsername"
                        PropertyChanges {
                            target: changeUsernameButton
                            text: "change username"
                        }
                        PropertyChanges {
                            target: enterUsernameArea
                            readOnly: true
                        }
                    }

                ]
            } // Rectangle userFeildContainer
        } // Rectangle chatUi
    }


} // Window
