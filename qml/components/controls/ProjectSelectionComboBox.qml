import QtQuick

import Timro

BaseComboBox {
    id: projectComboBox

    function updateCurrentIndex() {
        const id = projectController.currentProjectId
        if (id < 0) {
            currentIndex = 0
            return
        }
        currentIndex = indexOfValue(projectController.currentProjectId)
    }

    model: projectController.model
    onCountChanged: updateCurrentIndex()
    textRole: "name"
    valueRole: "id"
    onActivated: projectController.currentProjectId = currentValue

    Connections {
        target: projectController
        function onCurrentProjectIdChanged() {
            projectComboBox.updateCurrentIndex()
        }
    }
}
