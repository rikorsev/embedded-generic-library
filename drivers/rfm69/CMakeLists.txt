target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm69_driver.c
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm69_iface.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm69_driver.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm69_iface.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})