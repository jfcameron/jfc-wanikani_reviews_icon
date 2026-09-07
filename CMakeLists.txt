# © Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(null)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfc-cmake/jfclib.cmake")

option(JFC_BUILD_DOCS "Build documentation" OFF)
option(JFC_BUILD_TESTS "Build unit tests" OFF)

add_subdirectory(extern)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
PKG_CHECK_MODULES(APPINDICATOR QUIET ayatana-appindicator3-0.1)

if (APPINDICATOR_FOUND)
    set(JFC_APPINDICATOR_HEADER "libayatana-appindicator/app-indicator.h")
else()
    PKG_CHECK_MODULES(APPINDICATOR REQUIRED appindicator3-0.1)

    set(JFC_APPINDICATOR_HEADER "libappindicator/app-indicator.h")
endif()

message(STATUS "tray: using ${JFC_APPINDICATOR_HEADER}")

jfc_project(executable
    NAME "wanikani_reviews_icon"
    VERSION 0.0
    DESCRIPTION "tray icon indicates reviews"
    C++_STANDARD 20
    C_STANDARD 90

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include


    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${GTK3_INCLUDE_DIRS}
        ${APPINDICATOR_INCLUDE_DIRS}
        ${jfchttp_INCLUDE_DIRECTORIES}

    LIBRARIES
        ${GTK3_LIBRARIES}
        ${APPINDICATOR_LIBRARIES}
        ${jfchttp_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/icon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/notification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/summary.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-init.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-no_connection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-reviews_complete.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wanikani-32-reviews_available.cpp
)

target_link_libraries(${PROJECT_NAME} jfchttp)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    JFC_APPINDICATOR_HEADER="${JFC_APPINDICATOR_HEADER}")

target_link_directories(${PROJECT_NAME} PRIVATE ${APPINDICATOR_LIBRARY_DIRS})

if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/io.github.jfcameron.wanikani_reviews_icon.desktop"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications")

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/wanikani-32.png"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps"
    RENAME "io.github.jfcameron.wanikani_reviews_icon.png")

if (JFC_BUILD_TESTS)
    add_subdirectory(test)
endif()

if (JFC_BUILD_DOCS)
    add_subdirectory(docs)
endif()
