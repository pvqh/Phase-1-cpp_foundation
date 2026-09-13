cmake_minimum_required(VERSION 3.21)

project(cpp_foundations
    VERSION 0.1.0
    DESCRIPTION "Implementing the standard library from scratch, to learn what it is doing"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Standard
#
# Set on the target, not globally (see below) -- but these two are genuinely
# project-wide policy, so they live here.
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, not -std=gnu++20. Portability.

# Put binaries somewhere predictable instead of scattered per-config.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---------------------------------------------------------------------------
# The library itself.
#
# INTERFACE, because everything in include/pv/ is a header-only template.
# A template is not compiled until it is instantiated, so there is nothing to
# put in a .lib -- the target exists purely to carry the include path and the
# compile options to whoever links it.
#
# Read the three keywords as answers to "who needs this?":
#   PRIVATE   - only this target, consumers do not see it
#   INTERFACE - only consumers, not this target
#   PUBLIC    - both
# An INTERFACE library has no "this target" to speak of, so everything it
# carries is INTERFACE.
# ---------------------------------------------------------------------------
add_library(pv INTERFACE)
add_library(pv::pv ALIAS pv)      # so it is used the same way in-tree and out

target_include_directories(pv INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Warnings. Same policy you put on Timberman: /W4 /WX and conformance mode.
# Kept generator-agnostic so this still builds if you ever try clang or gcc.
if(MSVC)
    target_compile_options(pv INTERFACE /W4 /WX /permissive- /w15038)
else()
    target_compile_options(pv INTERFACE -Wall -Wextra -Wpedantic -Werror)
endif()

# /w15038 above is the one you could not have known about: it enables C5038,
# "data member will be initialized after data member", which is OFF by default
# even at /W4. It is the warning that would have caught the Timberman T1 bug.
# It is on from line one here.

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
include(CTest)
add_subdirectory(tests)

# Experiments (M5). Added when you get there:
# add_subdirectory(experiments)
