# Build Type flags handling

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DEBUG_BUILD true)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(DEBUG_BUILD false)
    add_compile_definitions(QT_NO_DEBUG)
endif()

add_compile_definitions(DEBUG_BUILD=\"${DEBUG_BUILD}\")
