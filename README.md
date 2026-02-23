# GetConfig

A lightweight, header-only C++20 library for parsing configuration files in INI-like format.  
Designed for simplicity and easy integration into any C++ project

## Requirements

- C++20

## Integration

1. Copy the entire `src` directory into your project’s source tree.
2. Include the main header:
   ```cpp
   #include "config.h"
   ```
3. Use the `get_config::Config` class to load and query configuration files.

## Usage Example

Assume you have a configuration file `../examples/config.ini`:

```ini
# Global settings
TASK_NAME = "Seidel method"
TASK_DESCRIPTION = "Solve SLAE"
A = 0.0
B = 1.0
H = 0.01

[SEIDEL]
USE_OMP = true
TOLERANCE = 1e-8
MAX_ITERATIONS = 1000

[POWER]
USE_OMP = false
TOLERANCE = 1e-6
MAX_ITERATIONS = 500
```

You can read it and access the values as follows:

```cpp
#include <iostream>
#include "config.h"

int main() {
    try {
        get_config::Config config;
        config.load_config("../examples/config.ini");

        // Access global parameters (default block is empty)
        double a = config.get<double>("A");
        double b = config.get<double>("B");
        double h = config.get<double>("H");

        std::cout << "Global:\n";
        std::cout << "TASK_NAME = " << config["TASK_NAME"] << '\n';
        std::cout << "A = " << a << ", B = " << b << ", H = " << h << '\n';

        // Access block-specific parameters
        bool use_omp = config.get<bool>("SEIDEL", "USE_OMP");
        double tol  = config.get<double>("SEIDEL", "TOLERANCE");
        size_t max_iter = config.get<size_t>("SEIDEL", "MAX_ITERATIONS");

        std::cout << "\n[SEIDEL]\n";
        std::cout << "USE_OMP = " << use_omp << '\n';
        std::cout << "TOLERANCE = " << tol << '\n';
        std::cout << "MAX_ITERATIONS = " << max_iter << '\n';

        // Using operator() for a more compact syntax
        std::cout << "\n[POWER]\n";
        std::cout << "USE_OMP = " << config("POWER", "USE_OMP") << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```

## Configuration File Syntax

- **Comments** start with `#` and extend to the end of the line.
- **Blocks (sections)** are defined as `[block_name]` on a separate line.
- **Parameters** are written as `key = value` (one per line).  
  The value extends to the end of the line and is trimmed.
- Parameter names can contain letters, digits, and underscores; they must start with a letter or underscore.

## Overview

### Class `get_config::Config`

#### Loading
- `load_config(std::istream&)` – parse from an input stream.
- `load_config(const std::string& filepath)` – parse from a file.

#### Accessors without type conversion (returns `const std::string&`)
- `get(const std::string& parameter)` – from default block.
- `get(const std::string& block, const std::string& parameter)` – from specific block.
- `operator[](const std::string& parameter)`
- `operator()(const std::string& parameter)`
- `operator()(const std::string& block, const std::string& parameter)`.

#### Accessors with type conversion (template versions)
- `get<T>(const std::string& parameter)` – converts value to type `T`.
- `get<T>(const std::string& block, const std::string& parameter)`

Supported types: `char`, `bool`, `int`, `long`, `long long`, `unsigned long`, `unsigned long long`, `float`, `double`, `long double`.