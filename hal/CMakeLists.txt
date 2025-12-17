target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_block.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_clock.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_crc.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_iface.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_pio.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_plat.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_pm.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_timer.h
        ${CMAKE_CURRENT_LIST_DIR}/egl_value.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})