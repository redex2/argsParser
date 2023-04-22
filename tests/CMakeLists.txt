include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_argumentOpt argumentOpt.cpp)
add_test(NAME test_argumentOpt COMMAND $<TARGET_FILE:test_argumentOpt>)
target_link_libraries(test_argumentOpt PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_argumentOpt PRIVATE ../include)

add_executable(test_argumentOptShort argumentOptShort.cpp)
add_test(NAME test_argumentOptShort COMMAND $<TARGET_FILE:test_argumentOptShort>)
target_link_libraries(test_argumentOptShort PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_argumentOptShort PRIVATE ../include)

add_executable(test_incorrect incorrect.cpp)
add_test(NAME test_incorrect COMMAND $<TARGET_FILE:test_incorrect>)
target_link_libraries(test_incorrect PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_incorrect PRIVATE ../include)

add_executable(test_opt opt.cpp)
add_test(NAME test_opt COMMAND $<TARGET_FILE:test_opt>)
target_link_libraries(test_opt PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_opt PRIVATE ../include)

add_executable(test_optShort optShort.cpp)
add_test(NAME test_optShort COMMAND $<TARGET_FILE:test_optShort>)
target_link_libraries(test_optShort PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_optShort PRIVATE ../include)

add_executable(test_mixed mixed.cpp)
add_test(NAME test_mixed COMMAND $<TARGET_FILE:test_mixed>)
target_link_libraries(test_mixed PRIVATE argsParser GTest::gtest_main)
target_include_directories(test_mixed PRIVATE ../include)