find_package(Catch2 3 REQUIRED)

add_executable(project_tests
    test_toolbox.cc
    test_lexis.cc
    test_gramatika.cc
)
target_link_libraries(project_tests PRIVATE lexis gramatika loma)
target_link_libraries(project_tests PRIVATE project_options Catch2::Catch2WithMain)
include(Catch)
add_test(NAME project_tests COMMAND project_tests)
