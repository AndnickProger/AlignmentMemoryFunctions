
add_executable (AlignmentMemory "main.cpp"  "alignment.cpp" "alignment.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AlignmentMemory PROPERTY CXX_STANDARD 20)
endif()
