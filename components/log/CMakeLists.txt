target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_log.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_log_front_bare.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_log_front_os.h
)

if(CONFIG_EGL_LOG_ENABLED EQUAL 1)
    target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_log.c
        ${CMAKE_CURRENT_LIST_DIR}/egl_log_front_bare.c
    )

    if(CONFIG_EGL_OS_ENABLED EQUAL 1)
        target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/egl_log_front_os.c
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})