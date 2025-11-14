# CMakeList.txt : CMake project for huffman_encoding, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (echo_server  "echo_server.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET echo_server PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.