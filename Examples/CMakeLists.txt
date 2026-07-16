set(EXAMPLE_NAMES
    01_escape_sequences
    02_sets
    03_stacks
    04_hash_tables
    05_paths
    06_nfa
    07_dfa
    08_grammar_symbols
    09_grammar_automaton
    10_loma_output
)

foreach(example_name IN LISTS EXAMPLE_NAMES)
    add_executable(example_${example_name} ${example_name}.cc)
    target_link_libraries(example_${example_name} PRIVATE lexis gramatika loma)
    target_link_libraries(example_${example_name} PRIVATE project_options)
endforeach()
