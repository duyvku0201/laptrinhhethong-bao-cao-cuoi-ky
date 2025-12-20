# CPU Scheduling Algorithms Simulator
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C](https://img.shields.io/badge/language-C-brightgreen.svg)
![Status](https://img.shields.io/badge/status-In%20Development-yellow.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

A comprehensive C program implementing six CPU scheduling algorithms with advanced visualization and comparison features for Operating Systems course final project.

---

## 📑 Table of Contents

- [Features](#features)
- [Algorithms Implemented](#algorithms-implemented)
- [Project Structure](#project-structure)
- [Build System](#build-system)
- [Installation](#installation)
- [Usage](#usage)
- [Input/Output Format](#inputoutput-format)
- [Team Members](#team-members)
- [Performance Metrics](#performance-metrics)
- [Screenshots](#screenshots)
- [Testing](#testing)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)
- [References](#references)

---

## ✨ Features

### 🔄 Six Scheduling Algorithms
- **FCFS** (First Come First Serve) - Non-preemptive
- **SJF** (Shortest Job First) - Non-preemptive
- **SRTF** (Shortest Remaining Time First) - Preemptive
- **Priority Scheduling** (Non-preemptive)
- **Priority Scheduling** (Preemptive)
- **Round Robin** (configurable time quantum)

### 📊 Advanced Visualization
- **Gantt Chart Display** - Real-time execution timeline
- **Colored Terminal Output** - ANSI color support for better readability
- **Process Timeline Tracking** - Detailed execution history
- **Progress Bars** - Visual feedback for long operations
- **Bar Chart Comparison** - Visual comparison of algorithm performance

### 📈 Comprehensive Performance Analysis
- **Waiting Time (WT)** - Average, Min, Max
- **Turnaround Time (TAT)** - Average, Min, Max
- **Response Time (RT)** - First execution time
- **CPU Utilization** - Percentage of CPU usage
- **Throughput** - Processes completed per time unit
- **Context Switches** - Number of process switches (for preemptive algorithms)

### 💾 Flexible Input/Output
- **File Input** - Read from `.txt` files
- **Interactive Keyboard Input** - Manual process entry
- **Sample Data** - Pre-configured test cases
- **Result Export** - Save results to file
- **Detailed Logging** - Execution timeline and metrics

### 🔍 Advanced Comparison Mode
- **Run All Algorithms** - Compare all 6 algorithms on same input
- **Side-by-Side Comparison** - Visual comparison table
- **Performance Ranking** - Identify best algorithm for given input
- **Individual Gantt Charts** - Separate visualization for each algorithm
- **Best Algorithm Highlighting** - Automatic best performer detection

### ✅ Robust Validation
- **Input Data Validation** - Check for valid process data
- **Error Handling** - Graceful error messages
- **Edge Case Testing** - Handle corner cases
- **Duplicate PID Detection** - Prevent data conflicts

---

## 🔧 Algorithms Implemented

### 1. FCFS (First Come First Serve)
- **Type:** Non-preemptive
- **Complexity:** O(n log n)
- **Pros:** Simple to implement, no starvation
- **Cons:** Convoy effect, high average waiting time
- **Best for:** Batch systems, simple workloads

### 2. SJF (Shortest Job First)
- **Type:** Non-preemptive
- **Complexity:** O(n²)
- **Pros:** Optimal average waiting time (among non-preemptive)
- **Cons:** Starvation possible for long jobs, requires burst time prediction
- **Best for:** Minimizing average waiting time when burst times are known

### 3. SRTF (Shortest Remaining Time First)
- **Type:** Preemptive
- **Complexity:** O(n × T) where T = total time
- **Pros:** Optimal average waiting time (among all algorithms)
- **Cons:** High context switching overhead, potential starvation
- **Best for:** Interactive systems requiring quick response

### 4. Priority Scheduling (Non-preemptive)
- **Type:** Non-preemptive
- **Complexity:** O(n²)
- **Pros:** Reflects process importance, flexible priority assignment
- **Cons:** Starvation possible (can be solved with aging)
- **Best for:** Systems with priority-based task management

### 5. Priority Scheduling (Preemptive)
- **Type:** Preemptive
- **Complexity:** O(n × T)
- **Pros:** More responsive to priority changes, better for real-time systems
- **Cons:** High context switching, potential starvation
- **Best for:** Real-time systems with dynamic priorities

### 6. Round Robin
- **Type:** Preemptive
- **Complexity:** O(n × T / TQ) where TQ = time quantum
- **Pros:** Fair distribution, no starvation, good for time-sharing
- **Cons:** Performance depends on time quantum size
- **Best for:** Time-sharing systems, interactive applications

---

## 📁 Project Structure

```
CPU-Scheduling-Algorithms/
│
├── README.md                    # Project documentation
├── BUILD_GUIDE.md              # Detailed build instructions
├── LICENSE                      # MIT License
├── .gitignore                   # Git ignore rules
├── Makefile                     # GNU Make build system
├── CMakeLists.txt              # CMake build configuration
│
├── docs/                        # Documentation (to be added)
│   └── report/                  # Project report
│
├── src/                         # Source code
│   ├── main.c                   # Main entry point ✅
│   │
│   ├── algorithms/              # Scheduling algorithms
│   │   ├── fcfs.c              # First Come First Serve ✅
│   │   ├── sjf.c               # Shortest Job First ✅
│   │   ├── srtf.c              # Shortest Remaining Time First ✅
│   │   ├── priority_np.c       # Priority Non-Preemptive ✅
│   │   ├── priority_p.c        # Priority Preemptive ✅
│   │   └── round_robin.c       # Round Robin ✅
│   │
│   ├── core/                    # Core functionality
│   │   ├── process.c           # Process operations ✅
│   │   ├── metrics.c           # Metrics calculation ✅
│   │   └── queue.c             # Queue for RR ✅
│   │
│   ├── io/                      # Input/Output
│   │   ├── input.c             # Keyboard input ✅
│   │   ├── output.c            # Result output ✅
│   │   └── file_handler.c      # File operations ✅
│   ├── io.c                     # IO wrapper functions ✅
│   │
│   ├── ui/                      # User Interface
│   │   ├── menu.c              # Main menu ✅
│   │   ├── display.c           # Display results ✅
│   │   ├── gantt.c             # Gantt chart ✅
│   │   └── comparison.c        # Algorithm comparison ✅
│   │
│   └── utils/                   # Utilities
│       ├── colors.c            # ANSI colors ✅
│       ├── sort.c              # Sorting functions ✅
│       └── validation.c        # Input validation ✅
│
├── include/                     # Header files
│   ├── algorithms.h            # Algorithm declarations ✅
│   ├── process.h               # Process structure ✅
│   ├── metrics.h               # Metrics functions ✅
│   ├── queue.h                 # Queue structure ✅
│   ├── io.h                    # IO functions ✅
│   ├── display.h               # Display functions ✅
│   ├── menu.h                  # Menu functions ✅
│   └── utils.h                 # Utility functions ✅
│
├── tests/                       # Test files
│   ├── test_cases/             # Input test cases ✅
│   │   ├── test1.txt
│   │   ├── test_complex.txt
│   │   ├── test_edge_cases.txt
│   │   ├── test_priority_np_*.txt (1-9)
│   │   ├── test_pp_*.txt (1-8 + main)
│   │   ├── test_rr_*.txt
│   │   ├── test_fcfs_*.txt
│   │   └── test_sjf_*.txt
│   │
│   ├── test_round_robin.c      # RR test program ✅
│   ├── test_priority_p.c       # Priority P test ✅
│   ├── test_srtf.c             # SRTF test ✅
│   ├── test_io.c               # IO module test ✅
│   └── test_output.c           # Output test ✅
│
├── build/                       # Compiled files (generated)
│   └── .gitkeep
│
└── samples/                     # Sample input files ✅
    ├── README.md
    ├── sample_input.txt
    ├── sample_complex.txt
    └── sample_edge_cases.txt
```

**Legend:**
- ✅ = Fully implemented and tested
- ⚠️ = Partially implemented
- ❌ = Not implemented

---

## 🛠️ Build System

The project supports **two build systems**:

### Option 1: CMake (Recommended - Cross-platform)
```bash
mkdir build && cd build
cmake ..
make
./scheduler
```

### Option 2: GNU Make (Traditional)
```bash
make
./build/scheduler
```

**Supported Platforms:**
- ✅ Windows (Visual Studio, MinGW, MSYS2)
- ✅ Ubuntu/Linux (GCC, Clang)
- ✅ NetBSD (GCC)
- ✅ macOS (Clang)

For detailed build instructions, see [BUILD_GUIDE.md](BUILD_GUIDE.md)

---

## 📦 Installation

### Prerequisites

```bash
# Check required tools
gcc --version    # GCC 10.0+ or Clang
make --version   # GNU Make (optional)
cmake --version  # CMake 3.10+ (optional)
git --version    # Git
```

### Quick Start

```bash
# 1. Clone repository
git clone https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky.git
cd laptrinhhethong-bao-cao-cuoi-ky

# 2. Build (choose one)
make              # Using Makefile
# OR
mkdir build && cd build && cmake .. && make  # Using CMake

# 3. Run
./build/scheduler  # Makefile
# OR
./scheduler        # CMake (from build directory)
```

---

## 🚀 Usage

### Running the Program

```bash
# Interactive mode
./build/scheduler

# Run with sample input (auto-feed)
make run-sample

# Run specific algorithm tests
make test-rr      # Test Round Robin
```

### Main Menu

```
================================================================================
                      CPU Scheduling Simulator
================================================================================

Please select a scheduling algorithm:

  1. FCFS (First Come First Serve)
  2. SJF (Shortest Job First)
  3. SRTF (Shortest Remaining Time First)
  4. Priority Scheduling (Non-preemptive)
  5. Priority Scheduling (Preemptive)
  6. Round Robin
  7. Compare All Algorithms
  8. Exit

Enter your choice [1-8]: _
```

### Input Options

```
How do you want to input process data?
  1. Read from file
  2. Enter from keyboard

Enter your choice [1-2]: _
```

---

## 📄 Input/Output Format

### File Input Format

```
n
PID1 ArrivalTime1 BurstTime1 Priority1
PID2 ArrivalTime2 BurstTime2 Priority2
...
PIDn ArrivalTimen BurstTimen Priorityn
```

**Example (`sample_input.txt`):**
```
4
1 0 5 2
2 1 3 1
3 2 8 3
4 3 6 2
```

### Input Constraints

| Field | Constraint |
|-------|------------|
| Number of processes (n) | 1 ≤ n ≤ 100 |
| Process ID (PID) | Must be positive and unique |
| Arrival Time (AT) | AT ≥ 0 |
| Burst Time (BT) | BT > 0 |
| Priority | Priority ≥ 0 (lower = higher priority) |

### Output Format

#### Results Table
```
╔═════╦═════╦═════╦══════════╦═════╦═════╦═════╦═════╗
║ PID ║  AT ║  BT ║ Priority ║  CT ║ TAT ║  WT ║  RT ║
╠═════╬═════╬═════╬══════════╬═════╬═════╬═════╬═════╣
║   1 ║   0 ║   5 ║        2 ║   5 ║   5 ║   0 ║   0 ║
║   2 ║   1 ║   3 ║        1 ║   8 ║   7 ║   4 ║   4 ║
║   3 ║   2 ║   8 ║        3 ║  16 ║  14 ║   6 ║   8 ║
║   4 ║   3 ║   6 ║        2 ║  22 ║  19 ║  13 ║  13 ║
╚═════╩═════╩═════╩══════════╩═════╩═════╩═════╩═════╝

┌──────────────────────────────────────────────────┐
│ Performance Metrics                              │
├──────────────────────────────────────────────────┤
│ Average Waiting Time    : 5.75                   │
│ Average Turnaround Time : 11.25                  │
│ Average Response Time   : 6.50                   │
│ Min/Max Waiting Time    : 0 / 13                 │
│ Min/Max Turnaround Time : 5 / 19                 │
│ CPU Utilization         : 100.00%                │
│ Throughput              : 0.1818 proc/time       │
└──────────────────────────────────────────────────┘
```

#### Gantt Chart
```
┌──────────────────────────────────────────────────┐
│ GANTT CHART - Process Execution Timeline        │
└──────────────────────────────────────────────────┘
+----+----+----+----+
| P1 | P2 | P3 | P4 |
+----+----+----+----+
0    5    8   16   22

═══ Execution Timeline Details ═══
Process    Start      End        Duration
─────────────────────────────────────────
      P1   0          5          5
      P2   5          8          3
      P3   8          16         8
      P4   16         22         6
```

---

## 👥 Team Members

| Name | Student ID | GitHub | Progress | Responsibilities |
|------|-----------|--------|----------|------------------|
| Le Thi Duc Hanh | 23IT065 | [@laptrinhhethong-bao-cao-cuoi-ky](https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky) | 100% | **Team Leader**<br>• FCFS Algorithm (fcfs.c)<br>• Priority Non-Preemptive (priority_np.c)<br>• Main Menu System (menu.c)<br>• Core Process Management (process.c)<br>• Project Integration & Testing<br>• Documentation & Report Coordination |
| Truong Phuoc Toan | 23IT278 | - | 100% | **Core Developer**<br>• SJF Algorithm (sjf.c)<br>• SRTF Algorithm (srtf.c)<br>• I/O Module (input.c, output.c, file_handler.c)<br>• Metrics Calculation (metrics.c)<br>• Sorting Utilities (sort.c)<br>• Comprehensive Testing & Validation |
| Pham Duy Kha | 23IT118 | - | 100% | **UI/UX Developer**<br>• Round Robin Algorithm (round_robin.c)<br>• Priority Preemptive (priority_p.c)<br>• Queue Implementation (queue.c)<br>• Display System (display.c, gantt.c)<br>• Comparison Module (comparison.c)<br>• Color & Visual Enhancements (colors.c) |

### Detailed Task Distribution

#### Le Thi Duc Hanh (33.3% total contribution)
**Algorithms (15%):**
- ✅ FCFS implementation with timeline tracking
- ✅ Priority Non-Preemptive with tie-breaking

**Core Systems (10%):**
- ✅ Process structure and management functions
- ✅ Main program flow and menu system

**Integration (8.3%):**
- ✅ Module integration and coordination
- ✅ Build system configuration (Makefile, CMake)
- ✅ Documentation (README, BUILD_GUIDE)

#### Truong Phuoc Toan (33.3% total contribution)
**Algorithms (15%):**
- ✅ SJF implementation
- ✅ SRTF with preemption handling

**I/O Module (10%):**
- ✅ File reading/writing (file_handler.c)
- ✅ Console input (input.c)
- ✅ Results output (output.c)

**Testing & Utilities (8.3%):**
- ✅ Metrics calculation module
- ✅ Sorting utilities (6 sorting functions)
- ✅ Validation functions
- ✅ Comprehensive test cases

#### Pham Duy Kha (33.3% total contribution)
**Algorithms (15%):**
- ✅ Round Robin with circular queue
- ✅ Priority Preemptive with context switching

**UI/Visualization (10%):**
- ✅ Gantt chart with color coding
- ✅ Results display with formatting
- ✅ Algorithm comparison module

**Advanced Features (8.3%):**
- ✅ Queue data structure
- ✅ ANSI color system
- ✅ Bar chart visualization
- ✅ Timeline tracking system

---

## 📊 Performance Metrics

### Calculated Metrics

| Metric | Formula | Description |
|--------|---------|-------------|
| **Completion Time (CT)** | Time when process finishes | Absolute time of completion |
| **Turnaround Time (TAT)** | CT - AT | Total time from arrival to completion |
| **Waiting Time (WT)** | TAT - BT | Time spent waiting in ready queue |
| **Response Time (RT)** | Start Time - AT | Time from arrival to first execution |
| **CPU Utilization** | (Total BT / Total Time) × 100% | Percentage of time CPU is busy |
| **Throughput** | Number of Processes / Total Time | Processes completed per unit time |

### Example Calculation

**Input:**
```
PID  AT  BT  Priority
1    0   5   2
2    1   3   1
3    2   8   3
```

**FCFS Results:**
```
PID  CT   TAT   WT   RT
1    5    5     0    0
2    8    7     4    4
3    16   14    6    8

Averages:
- Avg WT  = (0+4+6)/3 = 3.33
- Avg TAT = (5+7+14)/3 = 8.67
- Avg RT  = (0+4+6)/3 = 3.33
- CPU Utilization = (5+3+8)/16 × 100% = 100%
- Throughput = 3/16 = 0.1875 proc/time
```

---

## 📸 Screenshots

### Main Menu
```
╔══════════════════════════════════════════════════════════════════════════════╗
║                           CPU SCHEDULING ALGORITHMS MENU                     ║
╚══════════════════════════════════════════════════════════════════════════════╝

  1. FCFS (First Come First Serve)
  2. SJF (Shortest Job First - Non-Preemptive)
  3. SRTF (Shortest Remaining Time First - Preemptive)
  4. Priority Scheduling (Non-Preemptive)
  5. Priority Scheduling (Preemptive)
  6. Round Robin
  7. Compare All Algorithms
  8. Exit
```

### Comparison Mode
```
╔══════════════════════════════════════════════════════════════════════════════╗
║                            ALGORITHM COMPARISON                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

╔════════════════╦══════════╦══════════╦══════════╦══════════╦═══════════╗
║ Algorithm      ║ Avg WT   ║ Avg TAT  ║ Avg RT   ║ CPU Util ║ Throughput║
╠════════════════╬══════════╬══════════╬══════════╬══════════╬═══════════╣
║ FCFS           ║     5.75 ║    11.25 ║     5.75 ║  100.00% ║    0.1818 ║
║ SJF            ║     3.50 ║     9.00 ║     3.50 ║  100.00% ║    0.1818 ║
║ SRTF           ║     2.75 ║     8.25 ║     2.75 ║  100.00% ║    0.1818 ║
║ Priority NP    ║     4.25 ║     9.75 ║     4.25 ║  100.00% ║    0.1818 ║
║ Priority P     ║     3.00 ║     8.50 ║     3.00 ║  100.00% ║    0.1818 ║
║ Round Robin    ║     7.50 ║    13.00 ║     7.50 ║  100.00% ║    0.1818 ║
╚════════════════╩══════════╩══════════╩══════════╩══════════╩═══════════╝

┌──────────────────────────────────────────────────┐
│ Best Performing Algorithms                       │
├──────────────────────────────────────────────────┤
│ ★ Lowest Avg Waiting Time    : SRTF (2.75)      │
│ ★ Lowest Avg Turnaround Time : SRTF (8.25)      │
│ ★ Lowest Avg Response Time   : SRTF (2.75)      │
└──────────────────────────────────────────────────┘
```

---

## 🧪 Testing

### Running Tests

```bash
# Build and run all tests
make test

# Test specific algorithms
make test-rr              # Round Robin tests
./build/test_rr tests/test_cases/test_rr_main.txt 3

# Run with sample data
make run-sample
```

### Test Categories

#### 1. Algorithm Tests
- **Basic Tests:** Standard input validation
- **Edge Cases:** Single process, same arrival times, zero burst times
- **Stress Tests:** Large datasets (50+ processes)
- **Starvation Tests:** Long-running processes with interruptions

#### 2. Test Case Files

| Category | Files | Description |
|----------|-------|-------------|
| FCFS | `test_fcfs_*.txt` (3 files) | Various arrival patterns |
| SJF | `test_sjf_*.txt` (3 files) | Burst time variations |
| Priority NP | `test_priority_np_*.txt` (9 files) | Priority scenarios |
| Priority P | `test_pp_*.txt` (9 files) | Preemptive priority cases |
| Round Robin | `test_rr_*.txt` (6 files) | Different time quantums |
| General | `test1.txt`, `test_complex.txt` | Standard test cases |

#### 3. Module Tests
- ✅ `test_io.c` - I/O module validation
- ✅ `test_output.c` - Output formatting
- ✅ `test_round_robin.c` - RR algorithm
- ✅ `test_priority_p.c` - Priority preemptive
- ✅ `test_srtf.c` - SRTF with 9 test cases

### Test Results Summary

```
Total Test Cases: 45+
- FCFS: 3 tests ✅
- SJF: 3 tests ✅
- SRTF: 9 tests ✅
- Priority NP: 9 tests ✅
- Priority P: 9 tests ✅
- Round Robin: 6 tests ✅
- I/O Module: 6 tests ✅
```

---

## 📚 Documentation

### Available Documents

- **README.md** (this file) - Project overview and usage
- **BUILD_GUIDE.md** - Detailed build instructions for all platforms
- **Source Code Comments** - Inline documentation in Vietnamese and English

### Code Documentation

All source files include:
- **Function headers** with parameter descriptions
- **Algorithm explanations** in comments
- **Complexity analysis** where applicable
- **Example usage** in test files

---

## 🤝 Contributing

This is a course project, but suggestions and improvements are welcome!

### How to Contribute

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Coding Standards

- **C Standard:** C99
- **Indentation:** 4 spaces
- **Naming:**
  - Functions: `PascalCase` or `snake_case`
  - Variables: `PascalCase` or `snake_case`
  - Constants: `UPPER_CASE`
- **Comments:** Detailed function headers and inline explanations

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 CPU Scheduling Simulator Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

## 📖 References

### Books
1. **Advanced Programming in the UNIX Environment (3rd Edition)**  
   *Authors:* W. Richard Stevens, Stephen A. Rago  
   *Topics:* Process management, system calls

2. **The C Programming Language (2nd Edition)**  
   *Authors:* Brian W. Kernighan, Dennis M. Ritchie  
   *Topics:* C fundamentals, data structures

### Online Resources
1. [GeeksforGeeks - CPU Scheduling](https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/)
2. [Tutorialspoint - OS Scheduling Algorithms](https://www.tutorialspoint.com/operating_system/os_process_scheduling.htm)
3. [Wikipedia - Scheduling (computing)](https://en.wikipedia.org/wiki/Scheduling_(computing))

### Tools & Libraries
- **GCC** - GNU Compiler Collection
- **CMake** - Cross-platform build system
- **Make** - Build automation tool

---

## 📞 Contact & Support

### Team Contact
- **Primary Email:** hanhltd.23it@vku.udn.vn
- **GitHub Repository:** [laptrinhhethong-bao-cao-cuoi-ky](https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky)
- **Issues:** [Open an issue](https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky/issues)

### Academic Information
- **Course:** Operating Systems - System Programming
- **Institution:** Vietnam-Korea University of Information and Communication Technology (VKU)
- **University:** University of Danang
- **Semester:** Fall 2024 - Spring 2025
- **Instructor:** PhD. Nguyen Nhat An

---

## 🎯 Project Status

### Completion Summary

| Component | Status | Files | Progress |
|-----------|--------|-------|----------|
| **Algorithms** | ✅ Complete | 6/6 | 100% |
| **Core Modules** | ✅ Complete | 3/3 | 100% |
| **I/O System** | ✅ Complete | 4/4 | 100% |
| **UI/Display** | ✅ Complete | 4/4 | 100% |
| **Utilities** | ✅ Complete | 3/3 | 100% |
| **Build System** | ✅ Complete | 2/2 | 100% |
| **Testing** | ✅ Complete | 5+ | 100% |
| **Documentation** | ✅ Complete | 2/2 | 100% |

### Project Milestones

- [x] Project structure setup
- [x] Header files created
- [x] Core algorithms implementation (6/6)
- [x] I/O module implementation
- [x] UI/Display implementation
- [x] Comparison mode
- [x] Gantt chart visualization
- [x] Timeline tracking system
- [x] Testing and debugging
- [x] Documentation completion
- [x] Build system (Make + CMake)
- [ ] Final presentation (Upcoming)

---

## 🌟 Key Features Highlight

### Advanced Implementation
- ✅ **Timeline Tracking** - Real-time execution history
- ✅ **Context Switch Counting** - Preemptive algorithm analysis
- ✅ **Circular Queue** - Efficient Round Robin implementation
- ✅ **Merge Timeline** - Automatic execution block merging
- ✅ **Color-Coded Visualization** - Process-specific colors

### Code Quality
- ✅ **Modular Design** - Separated concerns (algorithms, I/O, UI)
- ✅ **Error Handling** - Robust input validation
- ✅ **Memory Safety** - No memory
