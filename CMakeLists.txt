# © 2020 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(null)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfc-cmake/jfclib.cmake")

option(JFC_BUILD_DOCS "Build documentation" OFF)
option(JFC_BUILD_TESTS "Build unit tests" OFF)

add_subdirectory(thirdparty)

# GUI
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

FIND_PACKAGE(CURL REQUIRED)

jfc_project(executable
    NAME "wanikani_reviews_icon"
    VERSION 0.0
    DESCRIPTION "tray icon indicates reviews"
    C++_STANDARD 17
    C_STANDARD 90

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include


    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${GTK3_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR}

    LIBRARIES
        ${GTK3_LIBRARIES}
        ${CURL_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/icon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/notification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-init.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-no_connection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-reviews_complete.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-reviews_available.cpp
)

if (JFC_BUILD_TESTS)
    add_subdirectory(test)
endif()

if (JFC_BUILD_DOCS)
    add_subdirectory(docs)
endif()
