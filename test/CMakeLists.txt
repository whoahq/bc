file(GLOB_RECURSE TEST_SOURCES "*.cpp")

if(WHOA_SYSTEM_MAC)
    set_source_files_properties(${TEST_SOURCES}
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )

    add_executable(BcTest ${TEST_SOURCES})

    target_link_libraries(BcTest
        PRIVATE
            bc
            "-framework AppKit"
    )
endif()

if(WHOA_SYSTEM_LINUX OR WHOA_SYSTEM_WIN)
    add_executable(BcTest ${TEST_SOURCES})

    target_link_libraries(BcTest
        PRIVATE
            bc
    )
endif()

target_include_directories(BcTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

install(TARGETS BcTest DESTINATION "bin")
