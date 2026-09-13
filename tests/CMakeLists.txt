# ---------------------------------------------------------------------------
# Catch2, fetched at configure time.
#
# FetchContent downloads and builds a dependency as part of your build. Note
# what it replaces: `Game 1` has the entire SFML SDK committed into its git
# repo -- 100+ headers under Dependencies/. This is the alternative. The
# dependency is declared, pinned to a tag, and never checked in.
#
# GIT_SHALLOW skips the history (faster). The tag is pinned on purpose: an
# unpinned dependency means your build can break because someone else pushed.
# ---------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)

# ---------------------------------------------------------------------------
# One test executable for the whole suite.
#
# Add a line here for each module as you write it. Explicitly, one per line --
# resist the urge to file(GLOB). CMake only re-runs when it thinks something
# changed, and a glob is evaluated at configure time, so a newly added file is
# silently missing from the build until you configure again by hand. An
# explicit list is one line of typing and never lies to you.
# ---------------------------------------------------------------------------
add_executable(tests
    test_m0_rig.cpp
    # test_m1_vec3.cpp
    # test_m2_uniqueptr.cpp
    # test_m3_vector.cpp
    # test_m4_sharedptr.cpp
)

# pv carries the include path AND the warning flags (INTERFACE), so linking it
# is all that is needed. Catch2WithMain gives you main() for free.
target_link_libraries(tests
    PRIVATE
        pv::pv
        Catch2::Catch2WithMain
)

# Registers each TEST_CASE with CTest individually, so `ctest` reports them by
# name rather than as one pass/fail lump.
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)
