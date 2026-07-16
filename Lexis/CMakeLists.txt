add_library(lexis STATIC
    CompressedDFA.cc
    DFA.cc
    DFAState.cc
    NFA.cc
    NFAState.cc
    State.cc
)
target_link_libraries(lexis PUBLIC toolbox project_options)
target_include_directories(lexis PUBLIC ${PROJECT_SOURCE_DIR})
