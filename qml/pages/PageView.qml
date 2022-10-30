import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Timro

Rectangle {
    anchors.fill: parent
    color: Style.background.appColor

    ColumnLayout {
        anchors {
            top: parent.top
            left: mainMenu.right
            right: parent.right
            bottom: parent.bottom
            leftMargin: 10
            rightMargin: 10
            topMargin: 5
        }

        TimeControlPanel {
            Layout.alignment: Qt.AlignHCenter
        }

        Flickable {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentHeight: stackView.currentItem.height
            bottomMargin: 10
            boundsBehavior: Flickable.StopAtBounds
            ScrollIndicator.vertical: ScrollIndicator { }

            StackView {
                id: stackView

                function showPage(pageComponent) {
                    goBackToHomePage()
                    push(pageComponent)
                }
                function goBackToHomePage() {
                    while (depth > 1) {
                        closeCurrentPage()
                    }
                }
                function closeCurrentPage(instant) {
                    if (instant) {
                        pop(StackView.Immediate)
                    } else {
                        pop()
                    }
                }

                anchors.fill: parent
                initialItem: HomePage { }
            }
        }
    }

    Component {
        id: projectListPage
        ProjectListPage { }
    }

    Component {
        id: aboutPage
        AboutPage { }
    }

    MainMenu {
        id: mainMenu
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        onHomeMenuClicked: stackView.goBackToHomePage()
        onProjectListMenuClicked: stackView.showPage(projectListPage)
        onAboutMenuClicked: stackView.showPage(aboutPage)
    }
}
