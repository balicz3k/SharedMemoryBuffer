find_package(GTest REQUIRED)

add_executable(unit_tests 
    SharedMemoryTest.cpp
    HeapMemoryTest.cpp
)

target_link_libraries(unit_tests PRIVATE 
    smb 
    GTest::gtest 
    GTest::gtest_main
)

add_test(NAME UnitTests COMMAND unit_tests)