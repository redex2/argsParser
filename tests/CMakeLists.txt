include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main)
add_test(NAME tests COMMAND $<TARGET_FILE:tests>)
target_link_libraries(tests PRIVATE argsParser)
target_include_directories(tests PRIVATE ../include)
