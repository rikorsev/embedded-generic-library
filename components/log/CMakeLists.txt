target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_log.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_log_front.h
)

if(DEFINED CONFIG_EGL_LOG_ENABLED AND CONFIG_EGL_LOG_ENABLED EQUAL 1)
    target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_log.c
        ${CMAKE_CURRENT_LIST_DIR}/egl_log_front.c
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})