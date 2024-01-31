# the build for Windows X64
project(zpad-win64 CXX)

set(WOCHATAPP_DIR "${CMAKE_CURRENT_LIST_DIR}"
    CACHE PATH "ZPad application directory")

add_executable(${PROJECT_NAME} WIN32 ZPad.cpp stdafx.cpp notepad2.c styles.c helpers.c edit.c dialogs.c dlapi.c print.cpp ZPad.rc)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT zpad-win64)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/wtl ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} scintilla)

set_property(TARGET ${PROJECT_NAME} PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# target_link_libraries(${PROJECT_NAME} debug d:/mywork/scintilla/bin/libscintilla.lib)
# target_link_libraries(${PROJECT_NAME} optimized d:/mywork/scintilla/bin/release/libscintilla.lib)
