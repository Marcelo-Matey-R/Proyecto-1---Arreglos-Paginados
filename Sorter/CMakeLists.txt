file(GLOB SORTER_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Sorter
    ${SORTER_SOURCES}
)

target_include_directories(Sorter
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sorter
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Sorter
    PRIVATE LibbCommon
)

target_compile_features(Sorter PRIVATE cxx_std_17)