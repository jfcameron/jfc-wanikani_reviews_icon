# © 2020 Joseph Cameron - All Rights Reserved
jfc_add_tests(
    C++_STANDARD 20
    C_STANDARD 90

    TEST_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/summary_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../src/summary.cpp"

    INCLUDE_DIRECTORIES
        "${${PROJECT_NAME}_INCLUDE_DIRECTORIES}"
        "${CMAKE_CURRENT_LIST_DIR}/../src/include"

    LIBRARIES
        "${${PROJECT_NAME}_LIBRARIES}"
)
