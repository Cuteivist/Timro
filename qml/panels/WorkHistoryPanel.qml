import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Timro

BasePanel {
    id: panel

    height: column.implicitHeight

    ColumnLayout {
        id: column
        anchors {
            left: parent.left
            right: parent.right
        }

        Text {
            text: qsTr("Session work time: %1").arg(qmlHelper.secondsToTimeString(timeController.currentSessionWorkTime))
            font.pixelSize: Style.global.defaultFontSize

            Layout.leftMargin: Style.panel.padding * 2
            Layout.fillWidth: true
            Layout.minimumHeight: paintedHeight
        }

        Text {
            text: qsTr("History:")
            font.pixelSize: Style.global.smallFontSize

            Layout.leftMargin: Style.panel.padding * 2
            Layout.fillWidth: true
            Layout.minimumHeight: paintedHeight
        }

        Rectangle {
            color: "black"
            opacity: 0.15
            Layout.fillWidth: true
            Layout.minimumHeight: 1
        }

        ListView {
            id: listView

            Layout.leftMargin: Style.panel.padding * 2
            Layout.fillWidth: true
            height: contentHeight + bottomMargin

            model: projectController.workHistoryModel
            spacing: Style.listDelegate.listSpacing
            bottomMargin: spacing * 2

            clip: true
            boundsBehavior: ListView.StopAtBounds

            delegate: Column {
                id: delegate
                width: listView.width
                height: Style.listDelegate.height * (index === 0 ? 1.3 : 1.0)
                readonly property int fontSize: index === 0 ? Style.listDelegate.fontSize : Style.global.smallFontSize

                Text {
                    text: qsTr("Project: %1").arg(name)
                    width: parent.width
                    elide: Text.ElideRight
                    font.pixelSize: delegate.fontSize
                }

                Text {
                    text: {
                        let projectWorkTime = 0
                        if (projectId === projectController.currentProjectId) {
                            projectWorkTime = timeController.workTime
                        } else {
                            projectWorkTime = workTime
                        }
                        const percent = Math.round((projectWorkTime / maxWorkTime) * 100)
                        const valueStr = String("%1  [%2%]").arg(qmlHelper.secondsToTimeString(projectWorkTime)).arg(percent)
                        return qsTr("Work time: %1").arg(valueStr)
                    }
                    font.pixelSize: delegate.fontSize
                }
            }
        }
    }
}
