file(GLOB BC_SOURCES
    "*.cpp"
    "lock/*.cpp"
    "time/*.cpp"
    "system/*.cpp"
)

add_library(bc STATIC
    ${BC_SOURCES}
)

target_include_directories(bc
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(bc
    PUBLIC
        storm
)
