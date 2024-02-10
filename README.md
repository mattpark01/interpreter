# Splang Interpreter

A lightweight interpreter for the Splang Interpreter (SI) language.

## Features

- Lexical analysis with support for variables, operators, numbers, and basic control structures.
- Parsing to an abstract syntax tree (AST) for evaluating SI language expressions and statements.
- Evaluation of parsed AST to execute SI language scripts.
- Extendable framework for adding new functions and control structures.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- CMake (version 3.15 or higher)
- GCC or Clang compiler
- Make (for Unix/Linux) or equivalent build system

### Building the Project

1. Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/SimpleCInterpreter.git
```

2. Navigate to the project directory:

```bash
cd SimpleCInterpreter
```

3. Run the build script:

```bash
./scripts/build.sh
```

Or, manually create a build directory and use CMake:

```bash
mkdir build && cd build
cmake ..
make
```

### Running Examples

After building the project, you can run the provided example scripts:

```bash
./SimpleCInterpreter examples/hello_world.si
```

## Documentation

For more detailed information on the SI language syntax and features, refer to the [Getting Started Guide](docs/getting_started.md) in the `docs` directory.

## Running Tests

To run the tests, navigate to the build directory and execute:

```bash
make test
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
```