# CMakeList.txt : CMake project for Cmake1, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Cmake1")

# Set the path to SFML
set(SFML_DIR "C:/sfml/SFML-2.6.2")

# Add source to this project's executable.
add_executable(Cmake1 "Main.cpp" "Main.h" "trieTree.cpp" "trieTree.h" "user.cpp" "user.h" "teacher.cpp" "teacher.h" "review.cpp" "review.h" "textButton.h" "textButton.cpp" "button.h" "button.cpp"  "studentUser.cpp" "studentUser.h" "teacherUser.cpp" "adminUser.h" "adminUser.cpp")

# Include SFML directories
target_include_directories(Cmake1 PRIVATE ${SFML_DIR}/include)

# Link SFML libraries
target_link_libraries(Cmake1 PRIVATE
    ${SFML_DIR}/lib/sfml-graphics.lib
    ${SFML_DIR}/lib/sfml-window.lib
    ${SFML_DIR}/lib/sfml-system.lib
    ${SFML_DIR}/lib/sfml-audio.lib
    ${SFML_DIR}/lib/sfml-network.lib
)

# Set C++ standard
set_property(TARGET Cmake1 PROPERTY CXX_STANDARD 20)
set_property(TARGET Cmake1 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.
