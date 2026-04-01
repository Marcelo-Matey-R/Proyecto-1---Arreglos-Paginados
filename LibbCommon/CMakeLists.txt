file(GLOB LIBBCOMMON_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(LibbCommon STATIC
    ${LIBBCOMMON_SOURCES}
)

target_include_directories(LibbCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(LibbCommon PUBLIC cxx_std_17)