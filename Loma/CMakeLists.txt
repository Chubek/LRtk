add_library(loma STATIC
    File.cc
    Fragment.cc
    Group.cc
    Module.cc
    Output.cc
)
target_link_libraries(loma PUBLIC toolbox project_options)
target_include_directories(loma PUBLIC ${PROJECT_SOURCE_DIR})
