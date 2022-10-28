# Application information
if (DEBUG_BUILD)
    set(APP_NAME "Timro - debug")
else()
    set(APP_NAME "Timro")
endif()

set(APP_DESCRIPTION "A work time management application for freelancers")
set(APP_VERSION 0.1.0)

# add defines
add_compile_definitions(APP_NAME=\"${APP_NAME}\")
add_compile_definitions(APP_DESCRIPTION=\"${APP_DESCRIPTION}\")
add_compile_definitions(APP_VERSION=\"${APP_VERSION}\")
