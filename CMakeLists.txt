cmake_minimum_required(VERSION 3.16)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Timro VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.4 COMPONENTS REQUIRED Core Quick Sql Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core ShaderTools Sql Widgets)

include_directories(src)

qt_standard_project_setup()

set(PROJECT_HEADERS
    src/TimroCore.h
    src/controllers/TimeController.h
    src/controllers/ProjectController.h
    src/controllers/TrayController.h
    src/helpers/DirHelper.h
    src/database/DatabaseProvider.h
    src/database/SqliteDatabaseProvider.h
    src/database/DatabaseMigrationWorker.h
    src/database/DatabaseCleaner.h
    src/sql/SqlWorker.h
    src/models/SqlModel.h
    src/models/ProjectModel.h
    src/QtSingleApp.h
    src/helpers/QmlHelper.h
)

set(PROJECT_SOURCES
    src/main.cpp
    src/TimroCore.cpp
    src/controllers/TimeController.cpp
    src/controllers/ProjectController.cpp
    src/controllers/TrayController.cpp
    src/helpers/DirHelper.cpp
    src/database/DatabaseProvider.cpp
    src/database/SqliteDatabaseProvider.cpp
    src/database/DatabaseMigrationWorker.cpp
    src/database/DatabaseCleaner.cpp
    src/sql/SqlWorker.cpp
    src/models/SqlModel.cpp
    src/models/ProjectModel.cpp
    src/QtSingleApp.cpp
    src/helpers/QmlHelper.cpp
)

qt_add_executable(Timro
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

qt_add_qml_module(Timro
    URI Timro
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/panels/BasePanel.qml
        qml/panels/TimeControlPanel.qml
        qml/panels/ProjectPanel.qml
        qml/panels/TimePanel.qml
        qml/panels/MainMenu.qml
        qml/panels/ProjectListPanel.qml
        qml/panels/TaskListPanel.qml
        qml/panels/ListPanel.qml
        qml/pages/BasePage.qml
        qml/pages/HomePage.qml
        qml/pages/ProjectListPage.qml
        qml/popups/BaseConfirmPopup.qml
        qml/popups/TimeTumblerPopup.qml
        qml/popups/PopupContainer.qml
        qml/popups/BreakWindow.qml
        qml/components/AutoSizeText.qml
        qml/components/panel/PanelTitle.qml
        qml/components/time/TimeDisplay.qml
        qml/components/time/TimeEditDisplay.qml
        qml/components/time/TimeProgressCircle.qml
        qml/components/time/TimeNumberSpinner.qml
        qml/components/time/TimeProgressArc.qml
        qml/components/time/TimeTumbler.qml
        qml/components/controls/RotatingButton.qml
        qml/components/controls/ImageButton.qml
        qml/components/controls/BaseButton.qml
        qml/components/controls/TextButton.qml
        qml/components/controls/BaseComboBox.qml
        qml/components/controls/MenuButton.qml
        qml/components/controls/DialogDragMouseArea.qml
        qml/components/delegates/PanelListDelegate.qml
        qml/components/effects/RotatingShadowEffect.qml
        qml/components/effects/GradientEffect.qml
        qml/utils/ModelUtils.js
    RESOURCES
        resources/button/time/play.png
        resources/button/time/pause.png
        resources/button/time/stop.png
        resources/button/time/clock.png
        resources/button/edit.png
        resources/button/check.png
        resources/button/reset.png
        resources/button/cancel.png
        resources/button/select_all.png
        resources/button/add.png
        resources/button/trash.png
        resources/menu/menu_show.png
        resources/menu/settings.png
        resources/menu/task.png
        resources/menu/home.png
        resources/selected.png
        resources/app_icon.png
)

qt_add_shaders(Timro "basic_shaders"
    PREFIX /
    FILES
        resources/shaders/linearGradient.frag
        resources/shaders/buttonRotate.frag
        resources/shaders/timeListOpacity.frag
        resources/shaders/rotatingShadow.frag
)

set_target_properties(Timro PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE ON
)

target_link_libraries(Timro PRIVATE Qt6::Sql Qt6::Quick Qt6::Core Qt6::Widgets)
