# Import this line of code to your project (for locating WeaNet library).
find_package(WeaNet REQUIRED)


# DON'T IMPORT
add_executable(WeaNetExamples
    TcpClientExample.cpp
    TcpServerExample.cpp
    UdpExample.cpp
)
# DON'T IMPORT
target_compile_definitions(WeaNetExamples PRIVATE EXAMPLE_MODE)

# Import this line of code to your project (for including WeaNet library).
target_link_libraries(WeaNetExamples PRIVATE WeaNet::WeaNet)

