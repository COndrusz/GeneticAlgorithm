## add the genetic algorithm library

add_library(geneticAlgorithm Genetic_Algorithm.cpp)

#find_package(OpenMP REQUIRED)
#if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")# ${OpenMP_CXX_FLAGS}")    
#    target_link_libraries(geneticAlgorithm PUBLIC OpenMP::OpenMP_CXX)
#endif()

set_target_properties( geneticAlgorithm
    PROPERTIES
    CXX_STANDARD 17
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# build the circuit simulator as a testable library

add_library(circuitSimulator CCircuit.cpp CSimulator.cpp CUnit.cpp)
set_target_properties( circuitSimulator
    PROPERTIES
    CXX_STANDARD 17
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# build the executable

add_executable(Circuit_Optimizer main.cpp)
target_link_libraries(Circuit_Optimizer PUBLIC geneticAlgorithm circuitSimulator)

set_target_properties( Circuit_Optimizer
    PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
