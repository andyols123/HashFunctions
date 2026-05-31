# Custom HashMap & Dynamic Array Implementation

A high-performance, lightweight C++ implementation of a Hash Map (Hash Table) with dynamic chaining using a custom-built Dynamic Array. This project features auto-resizing capabilities based on load factor thresholds and supports three distinct hashing algorithms to demonstrate collision distribution and performance characteristics.

Developed purely in standard modern C++ as a clean-code demonstration for technical internship evaluations.
 
---
## Building and Running 

### Prerequisites
Before building the project, ensure you have the following installed:
* **Operating System**: Windows 10 / 11
* **IDE**: Microsoft Visual Studio 2022 (Community, Professional, or Enterprise)
* **Toolset**: Microsoft Visual C++ (MSVC) supporting **C++17** or higher

### Build Instructions (Visual Studio)
1.  **Clone or Download the Repository**: Extract the project files to your local directory.
2.  **Open the Project**: Launch Visual Studio, select `Open a project or solution`, and navigate to the `.sln` (Solution) file or the main directory containing the source files.
3.  **Configure Build Target**: 
    * Set the build configuration dropdown to **Release** (optimized for performance) or **Debug** (for step-by-step debugging).
    * Set the platform architecture to **x64** or **x86** depending on your target system.
4.  **Compile the Solution**: 
    * Press F5 or click the green Start button to compile

---

## Key Features

* **Zero Standard Library Containers:** Built entirely without `std::vector`, `std::map`, or `std::list`. Both the hash map buckets and chain elements utilize a custom template-based `DynamicArray`.
* **Automatic Resizing (Rehashing):** Actively monitors the system's Load Factor ($\alpha = n/m$). It triggers an upscale (doubling buckets) when $\alpha > 2.0$ and a downscale (halving buckets) when $\alpha < 0.5$, ensuring optimal $O(1)$ average-time complexity for lookups.
* **Pluggable Hashing Algorithms:** Supports three distinct hashing modes selectable at runtime:
  1. **ASCII Modulo:** Linear mapping using the sum of character byte values.
  2. **Multiplication Method:** Uses the fractional part of the Golden Ratio ($\approx 0.618033$) for enhanced distribution consistency.
  3. **DJB2 Algorithm:** A highly optimized bitwise hashing function famous for exceptionally low collision rates.
* **Memory Safety & Robustness:** Implements the *Rule of Three* (custom copy constructor, assignment operator, and destructor) within the custom `DynamicArray` to completely eliminate memory leaks, dangling pointers, and double-free vulnerabilities during rehashing.

---

## Project Structure

```text
HashFunctions/
├── HashFunctions.sln         # Visual Studio Solution file
└── HashFunctions/            # Project source directory
    ├── HashFunctions.vcxproj # Visual Studio Project configuration
    ├── HashFunctions.cpp     # Main entry point with the automated test suite
    ├── DynamicArray.h        # Template-based dynamic array declaration & implementation
    ├── DynamicArray.cpp      # Source file for array (reserved for future non-template scaling)
    ├── HashMap.h             # HashMap class definition and structure layouts
    └── HashMap.cpp           # Core HashMap logic, hashing functions, and rehashing mechanisms
```
