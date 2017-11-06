import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import com.mohabouje.soundmaps 1.0
Item {
    anchors.centerIn: parent
    width: 450
    height: 350
    signal dialogClosed;
    Dialog {
        id: dialog
        width: parent.width
        height: parent.height
        standardButtons: Dialog.Ok
        modal: true
        padding: 10
        header: Rectangle {
            visible: false
            color: ThemeManager.accentColor()
            width: parent.width
            height: 40
        }

        Rectangle {
            id: groupBox
            width: parent.width
            ColumnLayout {
                width: parent.width

                Label {
                    text: qsTr("Device")
                }
                ComboBox {
                    editable: false
                    model: AudioManager.recorder.inputDevices()
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Frequency")
                }
                ComboBox {
                    id: comboBox
                    model: AudioManager.recorder.supportedSampleRates
                    onCurrentTextChanged: AudioManager.recorder.sampleRate = parseInt(currentText)
                    Layout.fillWidth: true
                }
                Label {
                    text: qsTr("Frame Rate")
                }
                ColumnLayout {
                    id: slider
                    Layout.fillWidth: true
                    RadioButton {
                        id : lowProcessing
                        checked: ComponentsManager.refreshRate == ComponentsManager.Low
                        onClicked: ComponentsManager.refreshRate = (ComponentsManager.Low)
                        text: qsTr("Low (10 FPS)")
                    }
                    RadioButton {
                        id : mediumProcessing
                        checked: ComponentsManager.refreshRate == ComponentsManager.Medium
                        onClicked: ComponentsManager.refreshRate = (ComponentsManager.Medium)
                        text: qsTr("Medium (20 FPS)")
                    }

                    RadioButton {
                        id : highProcessing
                        checked: ComponentsManager.refreshRate == ComponentsManager.Hight
                        onClicked: ComponentsManager.refreshRate = (ComponentsManager.Hight)
                        text: qsTr("Hight (40 FPS)")
                    }
                }
            }
        }
        onAccepted: {
            close()
        }
        onClosed: dialogClosed()
    }

    function show() {
        dialog.open();
    }
}