file(GLOB GENERATOR_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Generator
    ${GENERATOR_SOURCES}
)

target_include_directories(Generator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Generator
    PRIVATE LibbCommon
)

target_compile_features(Generator PRIVATE cxx_std_17)