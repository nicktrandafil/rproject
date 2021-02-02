cmake_minimum_required(VERSION 3.9.2)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0022 NEW)

project(yenxo VERSION 0.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(yenxo)


# If inside subdirectory.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(${PROJECT_NAME}_sub OFF)
else()
    set(${PROJECT_NAME}_sub ON)
endif()

# Options.

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

option(${PROJECT_NAME}_ENABLE_TYPE_SAFE "Enable type_safe support" ON)
if(${PROJECT_NAME}_ENABLE_TYPE_SAFE)
    set(_${PROJECT_NAME}_ENABLE_TYPE_SAFE 1)
else()
    set(_${PROJECT_NAME}_ENABLE_TYPE_SAFE 0)
endif()

option(${PROJECT_NAME}_TEST_DEFINE_STRUCT "Enable testing of DEFINE_STRUCT" OFF)

option(${PROJECT_NAME}_BUILD_DOC "Enable building documentation" OFF)

option(${PROJECT_NAME}_BUILD_SNIPPETS "Enable building snippets" OFF)

include(CMakeDependentOption)

cmake_dependent_option(${PROJECT_NAME}_TESTING
    "Enable testing"
    ON "NOT ${PROJECT_NAME}_sub" OFF
)
if(${PROJECT_NAME}_TESTING)
    enable_testing()
endif()

cmake_dependent_option(${PROJECT_NAME}_COVERAGE
    "Enable binary instrumentation to collect test coverage information in the DEBUG configuration"
    ON "NOT ${PROJECT_NAME}_sub AND ${PROJECT_NAME}_TESTING AND ${CMAKE_BUILD_TYPE} STREQUAL Debug" OFF
)


# CCache
if(NOT ${PROJECT_NAME}_sub)
    option(${PROJECT_NAME}_CCACHE "Enable CCache" ON)
    if(${PROJECT_NAME}_CCACHE)
        find_program(CCACHE_FOUND ccache)
        if(CCACHE_FOUND)
            message(STATUS "CCache enabled.")
            set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
            set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
        else()
            message(STATUS "CCache program not found, disabled.")
        endif()
    endif()
endif()


# 3rd party
if(NOT ${PROJECT_NAME}_sub)
    find_package(RapidJSON QUIET REQUIRED)
    find_package(Boost 1.65 QUIET REQUIRED)
    if(${PROJECT_NAME}_ENABLE_TYPE_SAFE)
        find_package(type_safe QUIET REQUIRED)
    endif()
    if(${PROJECT_NAME}_TESTING)
        find_package(Catch2 QUIET REQUIRED)
    endif()
    if(${PROJECT_NAME}_BUILD_SNIPPETS)
        find_package(benchmark QUIET REQUIRED)
    endif()
endif()

# Target

add_library(
    ${PROJECT_NAME} STATIC

    include/${PROJECT_NAME}/comparison_traits.hpp
    include/${PROJECT_NAME}/config.hpp
    include/${PROJECT_NAME}/define_enum.hpp
    include/${PROJECT_NAME}/define_struct.hpp
    include/${PROJECT_NAME}/enum_traits.hpp
    include/${PROJECT_NAME}/exception.hpp
    include/${PROJECT_NAME}/genuine_struct.hpp
    include/${PROJECT_NAME}/meta.hpp
    include/${PROJECT_NAME}/ostream_traits.hpp
    include/${PROJECT_NAME}/pimpl.hpp
    include/${PROJECT_NAME}/pimpl_impl.hpp
    include/${PROJECT_NAME}/preprocessor.hpp
    include/${PROJECT_NAME}/query_string.hpp
    include/${PROJECT_NAME}/string_conversion.hpp
    include/${PROJECT_NAME}/type_name.hpp
    include/${PROJECT_NAME}/value_tag.hpp
    include/${PROJECT_NAME}/variant.hpp
    include/${PROJECT_NAME}/variant_conversion.hpp
    include/${PROJECT_NAME}/variant_fwd.hpp
    include/${PROJECT_NAME}/variant_traits.hpp
    include/yenxo.hpp

    src/query_string.cpp
    src/variant.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(${PROJECT_NAME}
    SYSTEM
    PUBLIC
    $<INSTALL_INTERFACE:include>
    ${Boost_INCLUDE_DIRS}
    ${RAPIDJSON_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    BOOST_HANA_CONFIG_ENABLE_STRING_UDL
    YENXO_ENABLE_TYPE_SAFE=${_${PROJECT_NAME}_ENABLE_TYPE_SAFE}
)

if(${PROJECT_NAME}_ENABLE_TYPE_SAFE)
    target_link_libraries(${PROJECT_NAME} PUBLIC type_safe)
endif()


# compile options/definitions
if(NOT ${PROJECT_NAME}_sub)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_development)
endif()


# Setup package config

if(NOT ${PROJECT_NAME}_sub)
    install(DIRECTORY include/${PROJECT_NAME} DESTINATION include)

    include(CMakePackageConfigHelpers)
    set(CONFIG_PACKAGE_INSTALL_DIR lib/cmake/${PROJECT_NAME})

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        COMPATIBILITY SameMajorVersion
    )

    install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_development
        EXPORT ${PROJECT_NAME}-targets
        DESTINATION lib
    )

    install(EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR}
    )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        @ONLY
    )

    # because of nested @vars@
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        @ONLY
    )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR}
    )
endif()


# Doc
if(${PROJECT_NAME}_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Meta object code
add_subdirectory(moc)

# Testing
if(${PROJECT_NAME}_TESTING)
    add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Build and then run all the tests and examples."
        USES_TERMINAL)

    # Examples
    add_subdirectory(example)

    add_executable(
        test_${PROJECT_NAME}

        test/meta.cpp
        test/variant.cpp

        test/main.cpp

        test/variant_traits.cpp
        test/variant_traits_macros.cpp
        test/variant_traits_non_intrusive.cpp
        test/ostream_traits.cpp
        test/ostream_traits_macros.cpp
        test/comparison_traits.cpp
        test/comparison_traits_macros.cpp

        test/type_name.cpp
        test/json_struct.cpp
        test/type_safe.cpp
        test/string_conversion.cpp
        test/query_string.cpp

        test/variant_conversion.cpp

        test/define_enum.cpp

        $<$<BOOL:${${PROJECT_NAME}_TEST_DEFINE_STRUCT}>:test/define_struct.cpp>
        $<$<BOOL:${${PROJECT_NAME}_TEST_DEFINE_STRUCT}>:test/define_struct_part2.cpp>
        $<$<BOOL:${${PROJECT_NAME}_TEST_DEFINE_STRUCT}>:test/define_struct_part3.cpp>
    )

    set_target_properties(test_${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

    target_link_libraries(
        test_${PROJECT_NAME}
        PRIVATE

        Catch2::Catch2
        ${PROJECT_NAME}
        ${PROJECT_NAME}_development
    )

    add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
    add_dependencies(check test_${PROJECT_NAME})
endif()

# Snippets
if(${PROJECT_NAME}_BUILD_SNIPPETS)
    add_executable(${PROJECT_NAME}_snippets snippets/snippets.cpp)
    set_target_properties(${PROJECT_NAME}_snippets PROPERTIES CXX_STANDARD 17)
    target_link_libraries(${PROJECT_NAME}_snippets benchmark::benchmark ${PROJECT_NAME}_development ${PROJECT_NAME})
endif()

# Coverage
if(${PROJECT_NAME}_COVERAGE)
    add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/cov.sh
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/scripts/cov.sh ${CMAKE_BINARY_DIR}
        DEPENDS scripts/cov.sh)
    add_custom_target(${PROJECT_NAME}_cov ALL DEPENDS ${CMAKE_BINARY_DIR}/cov.sh)
endif()
