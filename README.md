# Gerardium rush

This project aims to develop a software tool using a genetic algorithm to optimize the recovery of valuable materials in mineral processing circuits.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler (e.g., g++, clang++)
- Python 3.x (for post-processing and visualization)

### Build Instructions

1. Clone the repository:
```sh
git clone https://github.com/ese-msc-2023/acs-gerardium-rush-bauxite.git
cd acs-gerardium-rush-bauxite
```

2. Create a build directory and run CMake:
```sh
mkdir build
cd build
cmake ..
```

3. Build the project:
```sh
make
```

### Usage
#### Running the Genetic Algorithm
After building the project, you can run the main executable `Circuit_Optimizer` to perform the genetic algorithm optimization:
```sh
./bin/Circuit_Optimizer
```

#### Running Tests
To run the tests, use the following command:
```sh
ctest
```

#### Post-processing
Post-processing scripts are provided to visualize the optimized circuits. Ensure you have Python installed and the necessary libraries. Make sure to install

##### Step 1: Install Graphviz

##### Windows

1. Download Graphviz from the [official website](https://graphviz.org/download/).
2. Run the installer and follow the installation instructions.
3. Add the Graphviz `bin` directory to your system `PATH` environment variable. This is usually something like `C:\Program Files\Graphviz\bin`.

#####  macOS

You can install Graphviz using Homebrew:

```sh
brew install graphviz
```

#####  Linux
On Debian-based systems, you can install Graphviz using apt-get:

```sh
sudo apt-get update
sudo apt-get install graphviz
```

##### Step 2: Install Dependencies

To install all the dependencies, we can use the command below
```sh
pip install -r requirements.txt
```

##### Step 3: Run the Python script to create the circuit
You can use the Python script to generate visual representations of the circuits. Make sure you are in the base folder of the project and run:

```sh
python Post_processing.py
```
The circuit will be generated in the /circuit_diagram folder in the project.

##### Step 4: Run the Python script to create the circuit animation
You can then use the Python script to generate animation of the circuit. Make sure you are in the base folder of the project and run:

```sh
python Post_processing_animation.py
```
The animation will be generated in the /animations folder in the project.

#### Project Structure
```scss
├── CMakeLists.txt
├── include
│   └── CCircuit.h
│   └── CSimulator.h
│   └── CUnit.h
│   └── Genetic_Algorithm.h
├── src
│   └── CMakeLists.txt
│   └── CCircuit.cpp
│   └── CSimulator.cpp
│   └── CUnit.cpp
│   ├── Genetic_Algorithm.cpp
│   ├── main.cpp
├── tests
│   ├── test_circuit_simulator.cpp
│   ├── test_genetic_algorithm.cpp
│   └── test_genetic_crossover.cpp
│   └── test_genetic_mutation.cpp
│   └── test_validity_checker.cpp
│   └── CMakeLists.txt
├── ...
└── README.md
```

#### CMakeLists.txt
The project is configured using CMake. The main `CMakeLists.txt` sets up the project structure, includes directories, and adds subdirectories for source code and tests.

#### Source Code
`Genetic_Algorithm.cpp`: Contains the implementation of the genetic algorithm.
`main.cpp`: Entry point of the application, which sets up and runs the genetic algorithm.

#### Tests
Tests are organized under the tests directory and include various unit tests to ensure the correctness of the circuit simulator and genetic algorithm.

### License
This project is licensed under the MIT License - see the LICENSE file for details.