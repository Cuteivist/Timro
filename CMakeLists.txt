cmake_minimum_required(VERSION 3.16)

project(Timro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS ShaderTools)

qt_add_executable(appTimro
    src/main.cpp
)

qt_add_qml_module(appTimro
    URI Timro
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/panels/BasePanel.qml
        qml/panels/TimeControlPanel.qml
        qml/panels/ProjectPanel.qml
        qml/panels/TimePanel.qml
        qml/components/time/TimeDisplay.qml
        qml/components/time/TimeEditDisplay.qml
        qml/components/time/TimeProgressCircle.qml
        qml/components/time/TimeNumberSpinner.qml
        qml/components/time/TimeProgressArc.qml
        qml/components/buttons/RotatingButton.qml
        qml/components/buttons/ImageButton.qml
        qml/components/effects/RotatingShadowEffect.qml
        qml/components/effects/GradientEffect.qml
    RESOURCES
        resources/button/time/play.png
        resources/button/time/pause.png
        resources/button/time/stop.png
        resources/button/time/edit.png
        resources/button/time/check.png
        resources/button/time/reset.png
        resources/button/time/cancel.png
)

qt6_add_shaders(appTimro "basic_shaders"
    PREFIX /
    FILES
        resources/shaders/linearGradient.frag
        resources/shaders/buttonRotate.frag
        resources/shaders/timeListOpacity.frag
        resources/shaders/rotatingShadow.frag
)

set_target_properties(appTimro PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTimro
    PRIVATE Qt6::Quick)

install(TARGETS appTimro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
