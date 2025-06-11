find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
#find_package(WeaNet REQUIRED)

add_executable(WeaNetTests main.cpp
    src/MainClass.h src/MainClass.cpp)

target_include_directories(WeaNetTests PRIVATE ${WEANET_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(WeaNetTests PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick WeaNet)

