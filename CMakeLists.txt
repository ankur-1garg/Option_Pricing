# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(OptionPricer CXX)

# Set the C++ standard to C++17 (good for modern features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--- Target: The Main Library ---#
# This creates a library named "pricer_lib" from our source files.
# We will create these .cpp files in the next step.
add_library(pricer_lib
    src/option.cpp
    src/european_option.cpp
    src/black_scholes_pricer.cpp
    src/american_option.cpp
    src/binomial_pricer.cpp
    src/monte_carlo_pricer.cpp
)

# Tell CMake where to find the headers for our library
target_include_directories(pricer_lib PUBLIC include)


#--- Target: The Demo Executable ---#
# This creates the main executable from main.cpp
add_executable(demo main.cpp)

# Link our demo executable against our library.
# This makes the functions in pricer_lib available to demo.
target_link_libraries(demo pricer_lib)