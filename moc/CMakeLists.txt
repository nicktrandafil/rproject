project(moc)

set(test_data
    test/data/class.cpp
    test/data/attribute.cpp
    test/data/identifier.cpp
    test/data/literal.cpp
)

##########################################################################################
# Core
add_library(${PROJECT_NAME}_core
    include/${PROJECT_NAME}/ast.hpp
    include/${PROJECT_NAME}/parse.hpp

    src/parse.cpp
)
target_link_libraries(${PROJECT_NAME}_core PRIVATE yenxo_development PUBLIC yenxo)
target_include_directories(${PROJECT_NAME}_core PUBLIC include)
set_target_properties(${PROJECT_NAME}_core PROPERTIES CXX_STANDARD 17)

##########################################################################################
# Tool
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_core)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

##########################################################################################
# Testing
if(yenxo_TESTING)
    set(test_data_headers)

    foreach(x ${test_data})
        get_filename_component(name ${x} NAME_WE)
        add_library(${name} OBJECT EXCLUDE_FROM_ALL ${x})
        set_target_properties(${name} PROPERTIES CXX_STANDARD 17)
        target_compile_options(${name} PRIVATE -Wno-attributes -Wno-multichar)
        set(gen_name ${name}-gen.h)
        set(gen_file ${CMAKE_CURRENT_BINARY_DIR}/data/${gen_name})
        add_custom_command(
            OUTPUT ${gen_file}
            DEPENDS ${x} ${name}
            COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/data
            COMMAND xxd -i ${x} > ${gen_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "make test data ${name}"
        )
        list(APPEND test_data_headers ${gen_file})
    endforeach()

    add_executable(test_${PROJECT_NAME}
        test/main.cpp
        test/parse.cpp

        ${test_data_headers}
    )
    target_link_libraries(test_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_core yenxo_development Catch2::Catch2)
    target_include_directories(test_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties(test_${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

    add_test(test_moc test_${PROJECT_NAME})
endif()
