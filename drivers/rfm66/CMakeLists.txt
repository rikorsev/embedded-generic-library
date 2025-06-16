target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66_driver.c
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66_iface.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66_driver.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66_iface.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})