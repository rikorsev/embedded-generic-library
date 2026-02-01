target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_os_threadx.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_os_threadx.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC threadx)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CONFIG_EGL_OS_THREADEX_PATH}/common/inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CONFIG_EGL_OS_THREADEX_PATH}/ports/${THREADX_ARCH}/${THREADX_TOOLCHAIN}/inc)
