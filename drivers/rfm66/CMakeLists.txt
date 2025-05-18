target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/egl_rfm66.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})