add_library(toolbox STATIC
    Character.cc
    CharacterSet.cc
    EscapeSequence.cc
    List.cc
    PathName.cc
    Set.cc
    String.cc
    Stack.cc
)
target_link_libraries(toolbox PUBLIC project_options)
target_include_directories(toolbox PUBLIC ${PROJECT_SOURCE_DIR})
