import QtQuick
import QtQuick.Layouts

import Timro

BasePage {
    id: page

    BasePanel {
        id: panel
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height + Style.panel.padding
        onHeightChanged: page.height = panel.height // For some reason binding page.height = panel.height doesn't update itself

        readonly property var licenses: ({
            "Flaticon": "https://www.freepikcompany.com/legal#nav-flaticon"
        })

        function getLicenseLink(license) {
            const link = licenses[license]
            if (link.length == 0) {
                return "ERROR_NOT_FOUND"
            }
            return link
        }

        function formatLink(link, description) {
            return "<a href=\"" + link + "\">" + description + "</a>";
        }

        PanelTitle {
            id: panelTitle
            text: qsTr("About")

            MouseArea {
                anchors.fill: parent; acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: {
                   console.error(page.height, panel.height, column.height)
                }
            }
        }

        Image {
            anchors {
                top: parent.top
                right: parent.right
                margins: Style.panel.padding
            }
            source: "qrc:/Timro/resources/app_icon.png"
            width: 48
            height: width
        }

        ColumnLayout {
            id: column

            anchors {
                top: panelTitle.bottom
                left: parent.left
                right: parent.right
                margins: Style.panel.padding
            }

            spacing: Style.listDelegate.spacing * 2

            Text {
                text: {
                    let value = app.applicationName
                    value += "\n" + qsTr("ver. %1").arg(app.applicationVersion)
                    if (isDebug) {
                        value += " - debug"
                    }
                    return value
                }
                Layout.fillWidth: true
                Layout.preferredHeight: paintedHeight
                font.pixelSize: Style.global.defaultFontSize
            }

            CollapsableSection {
                Layout.fillWidth: true
                Layout.preferredHeight: childrenRect.height

                title: qsTr("Icons attributions")
                model: IconAttributionsModel { }

                delegate: Rectangle {
                    width: ListView.width
                    height: childrenRect.height + Style.collapsableSection.padding * 2
                    radius: Style.collapsableSection.radius
                    color: Style.collapsableSection.delegateBackgroundColor
                    Column {
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: Style.collapsableSection.padding
                        }
                        Text {
                            text: name
                            width: parent.width
                            wrapMode: Text.WordWrap
                            font.pixelSize: Style.collapsableSection.contentsFontSize
                        }
                        Text {
                            text: panel.formatLink(url, urlDescription)
                            width: parent.width
                            wrapMode: Text.WordWrap
                            font.pixelSize: Style.collapsableSection.contentsFontSize
                            textFormat: Text.RichText
                            onLinkActivated: Qt.openUrlExternally(url)
                        }
                        Text {
                            text: qsTr("License: %1").arg(panel.formatLink(panel.getLicenseLink(license), license))
                            width: parent.width
                            wrapMode: Text.WordWrap
                            font.pixelSize: Style.collapsableSection.contentsFontSize
                            textFormat: Text.RichText
                            onLinkActivated: Qt.openUrlExternally(panel.getLicenseLink(license))
                        }
                    }
                }
            }

            Image {
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Timro/resources/qt_logo.png"
            }
        }
    }
}
