add_library(gramatika STATIC
    ActionRecord.cc
    Automaton.cc
    GotoRecord.cc
    Item.cc
    ItemSet.cc
    ParseTable.cc
    Partition.cc
    Production.cc
    State.cc
    Symbol.cc
    SymbolTable.cc
)
target_link_libraries(gramatika PUBLIC toolbox project_options)
target_include_directories(gramatika PUBLIC ${PROJECT_SOURCE_DIR})
