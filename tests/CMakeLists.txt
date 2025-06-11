find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
#find_package(WeaNet REQUIRED)
#find_package(WeaNet REQUIRED PATHS "D:/parsa/WeaNetLib")

add_executable(WeaNetTests main.cpp
    src/MainClass.h src/MainClass.cpp)

if (WIN32)
    cmake_policy(SET CMP0079 NEW)
    target_link_libraries(WeaNetTests PUBLIC wsock32 ws2_32)
    target_compile_definitions(WeaNetTests PRIVATE _WIN32_WINNT=0x0A00)

endif()

target_include_directories(WeaNetTests PRIVATE ${WEANET_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(WeaNetTests PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick WeaNet)

