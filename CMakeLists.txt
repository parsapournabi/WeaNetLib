cmake_minimum_required(VERSION 3.5)

project(wearily-netlib VERSION 0.1 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt Setup
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# --- Library ---
set(HEADERS
        include/WeaNet/Tcp.h
        include/WeaNet/Udp.h
        include/WeaNet/Internal/error.h
        include/WeaNet/Internal/net_enums.h
        include/WeaNet/Internal/network.h
        include/WeaNet/Internal/common.h
    )
set(SOURCES
        src/Tcp.cpp
        src/Udp.cpp
        src/internal/error.cpp
        src/internal/network.cpp
)
add_library(WeaNet
    SHARED ${SOURCES} ${HEADERS}
    install.sh README.md uninstall.sh WeaNetConfig.cmake.in WeaNetUninstall.cmake.in
)

target_include_directories(WeaNet
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>
)

target_link_libraries(WeaNet PUBLIC Qt${QT_VERSION_MAJOR}::Core)

# Including Windows WinSock
if (WIN32)
    target_link_libraries(WeaNet PUBLIC wsock32 ws2_32)
endif()


# Library Install (WeaNet)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/WeaNetConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/WeaNetConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/WeaNetConfig.cmake"
        INSTALL_DESTINATION lib/cmake/WeaNet
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/WeaNetUninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/WeaNetUninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/WeaNetUninstall.cmake
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/WeaNetConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/WeaNetConfigVersion.cmake"
        DESTINATION lib/cmake/WeaNet
)

install(TARGETS WeaNet
        EXPORT WeaNetTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/WeaNet DESTINATION include)

install(EXPORT WeaNetTargets
        FILE WeaNetTargets.cmake
        NAMESPACE WeaNet::
        DESTINATION lib/cmake/WeaNet
)

option(BUILD_EXAMPLES "Build example application for WeaNet" ON)

if(BUILD_EXAMPLES)
#        add_subdirectory(examples EXCLUDE_FROM_ALL)

endif()

