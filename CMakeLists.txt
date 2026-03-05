cmake_minimum_required(VERSION 3.19)
project(MacroCommandApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(UI_SOURCES
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/ui/clickcanvaswidget.h
    src/ui/clickcanvaswidget.cpp
)

set(COMMAND_SOURCES
    src/core/commands/imacrocommand.h
    src/core/commands/mouseclickcommand.h
    src/core/commands/mouseclickcommand.cpp
    src/core/commands/mousemovecommand.h
    src/core/commands/mousemovecommand.cpp
    src/core/commands/keyboardkeypresscommand.h
    src/core/commands/keyboardkeypresscommand.cpp
)

set(SERIALIZATION_SOURCES

    src/core/serialization/iscriptserializer.h
    src/core/serialization/textscriptserializer.h
    src/core/serialization/textscriptserializer.cpp
)

set(CORE_SOURCES
    src/core/interactionsrecorder.h
    src/core/interactionsrecorder.cpp
    src/core/eventfilter.h
    src/core/eventfilter.cpp
)

qt_add_executable(command
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${UI_SOURCES}
    ${CORE_SOURCES}
    ${COMMAND_SOURCES}
    ${SERIALIZATION_SOURCES}
    src/core/serialization/visitors/icommandvisitor.h
    src/core/serialization/visitors/textsavevisitor.h src/core/serialization/visitors/textsavevisitor.cpp
)

target_include_directories(command PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

target_link_libraries(command
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

if(WIN32 OR APPLE)
    qt_generate_deploy_app_script(
        TARGET command
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()