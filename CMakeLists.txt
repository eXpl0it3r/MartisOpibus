cmake_minimum_required(VERSION 3.15)

project(MartisOpibus LANGUAGES CXX)

# Set options
option(MARTISOPIBUS_STATIC_LIBS "Use static libraries?" OFF)
option(MARTISOPIBUS_STATIC_STD_LIBS "Use statically linked standard/runtime libraries? This option must match the one used for SFML." OFF)

# Martis Opibus uses C++17 features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Request static SFML libraries when building statically
if(MARTISOPIBUS_STATIC_LIBS)
	set(SFML_STATIC_LIBRARIES true)
endif()

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Tell CMake to build a executable
add_executable(MartisOpibus 
	src/main.cpp
	src/Game.hpp
	src/Game.cpp
	src/Grid.hpp
	src/Grid.cpp
	src/Unit.hpp
	src/Unit.cpp
	src/MathUtil.hpp
)

# Make sure that the runtime library gets linked statically
if(MARTISOPIBUS_STATIC_STD_LIBS)
	if(NOT SFML_STATIC_LIBRARIES)
		message("\n-> If you check MARTISOPIBUS_STATIC_STD_LIBS, you also need to check SFML_STATIC_LIBRARIES.")
		message("-> It would lead to multiple runtime environments which results in undefined behavior.\n")
	elseif(WIN32 AND MSVC)
		set_property(TARGET MartisOpibus PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		# Note: Doesn't work for TDM compiler, since it's compiling the runtime libs statically by default
		target_compile_options(MartisOpibus PRIVATE -static)
	endif()
endif()

# Link SFML
target_link_libraries(MartisOpibus sfml-graphics)

# Install executable
install(TARGETS MartisOpibus
		RUNTIME DESTINATION .)

# Install game data
install(DIRECTORY assets
		DESTINATION .)