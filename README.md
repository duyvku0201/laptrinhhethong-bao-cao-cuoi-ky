# CPU Scheduling Algorithms Simulator
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C](https://img.shields.io/badge/language-C-brightgreen.svg)
![Status](https://img.shields.io/badge/status-In%20Development-yellow.svg)
A comprehensive C program implementing six CPU scheduling algorithms for Operating Systems course final project.
---
## Table of Contents
- [Features](#features)
- [Algorithms Implemented](#algorithms-implemented)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Team Members](#team-members)
- [Performance Metrics](#performance-metrics)
- [Screenshots](#screenshorts)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [References](#references)
---
## Features
 - Six Scheduling Algorithms
   - FCFS (First Come First Serve)
   - SJF (Shortest Job First - Non-preemptive)
   - SRTF (Shortest Remaining Time First - Preemptive)
   - Priority Scheduling (Non-preemptive)
   - Priority Scheduling (Preemptive)
   - Round Robin (configurable time quantum)
 - Visualization
   - Gantt chart display
   - Colored terminal output
   - Progress bars and animations
 - Performance Analysis
   - Waiting Time (WT)
   - Turnaround Time (TAT)
   - Response Time (RT)
   - CPU Utilization
   - Throughput calculation
 - Flexible Input/Output
   - Read from file (.txt, .csv)
   - Interactive keyboard input
   - Export results to file
   - CSV export for Excel analysis
 - Comparison Mode
   - Run all algorithms on same input
   - Side-by-side comparison
   - Performance ranking
 - Robust Validation
   - Input data validation
   - Error handling
   - Edge case testing
---
##  Algorithms Implemented
### 1. FCFS (First Come First Serve)
- Type: Non-preemptive
- Complexity: O(n log n)
- Pros: Simple, no starvation
- Cons: Convoy effect, high average WT
### 2. SJF (Shortest Job First)
- Type: Non-preemptive
- Complexity: O(n²)
- Pros: Optimal average WT (among non-preemptive)
- Cons: Starvation possible, need to know BT in advance
### 3. SRTF (Shortest Remaining Time First)
- Type: Preemptive
- Complexity: O(n × T) where T = total time
- Pros: Optimal average WT (among all algorithms)
- Cons: High context switching, starvation possible
### 4. Priority Scheduling (Non-preemptive)
- Type: Non-preemptive
- Complexity: O(n²)
- Pros: Can reflect process importance
- Cons: Starvation possible (solved with aging)
### 5. Priority Scheduling (Preemptive)
- Type: Preemptive
- Complexity: O(n × T)
- Pros: More responsive to priority changes
- Cons: High context switching, starvation possible
### 6. Round Robin
- Type: Preemptive
- Complexity: O(n × T / TQ) where TQ = time quantum
- Pros: Fair, no starvation, good for time-sharing
- Cons: Performance depends on TQ size
---
## 📁 Project Structure
```
CPU-Scheduling-Algorithms/
│
├── README.md                          # This file
├── LICENSE                            # MIT License
├── .gitignore                         # Git ignore rules
├── Makefile                           # Build automation
│
├── docs/                              # Documentation
│   ├── report/                        # Project report
│   │   ├── report.pdf
│   │   └── images/
│   │       ├── architecture.png
│   │       ├── flowcharts/
│   │       └── screenshots/
│   │
│   ├── presentation/                  # Presentation slides
│   │   ├── slides.pptx
│   │   └── demo_video.mp4
│   │
│   └── user_manual.md                 # User manual
│
├── src/                               # Source code
│   ├── main.c                         # Main entry point
│   │
│   ├── algorithms/                    # Scheduling algorithms
│   │   ├── fcfs.c
│   │   ├── sjf.c
│   │   ├── srtf.c
│   │   ├── priority_np.c
│   │   ├── priority_p.c
│   │   └── round_robin.c
│   │
│   ├── core/                          # Core functionality
│   │   ├── process.c                  # Process operations
│   │   ├── metrics.c                  # Metrics calculation
│   │   └── queue.c                    # Queue for RR
│   │
│   ├── io/                            # Input/Output
│   │   ├── input.c                    # File/keyboard input
│   │   ├── output.c                   # Result output
│   │   └── file_handler.c             # File operations
│   │
│   ├── ui/                            # User Interface
│   │   ├── menu.c                     # Main menu
│   │   ├── display.c                  # Display results
│   │   └── gantt.c                    # Gantt chart
│   │
│   └── utils/                         # Utilities
│       ├── sort.c                     # Sorting functions
│       ├── validation.c               # Input validation
│       └── colors.c                   # ANSI colors
│
├── include/                           # Header files
│   ├── algorithms.h
│   ├── process.h
│   ├── metrics.h
│   ├── queue.h
│   ├── io.h
│   ├── display.h
│   └── utils.h
│
├── tests/                             # Test files
│   ├── test_cases/                    # Input test cases
│   │   ├── test1.txt
│   │   ├── test2.txt
│   │   ├── test_complex.txt
│   │   ├── test_edge_cases.txt
│   │   └── README.md
│   │
│   ├── expected_outputs/              # Expected results
│   │   ├── test1_fcfs_expected.txt
│   │   └── ...
│   │
│   └── test_results/                  # Actual results
│       └── .gitkeep
│
├── build/                             # Compiled files
│   └── .gitkeep
│
└── samples/                           # Sample files
    ├── sample_input.txt
    ├── sample_complex.txt
    ├── sample_edge_cases.txt
    └── README.md
```
---
## Installation
### Prerequisites
- GCC Compiler (version 10.0 or higher)
- Make (optional, for using Makefile)
- Git (for cloning repository)
Check if installed:
```bash
gcc --version
make --version
git --version
```
### Installation Steps
#### Option 1: Clone from GitHub
```bash
# Clone repository
git clone https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky
# Navigate to project directory
cd ./laptrinhhethong-bao-cao-cuoi-ky
# Build project
make
# Run
./build/scheduler
```
#### **Option 2: Download ZIP**
1. Download ZIP from GitHub
2. Extract to desired location
3. Open terminal in extracted folder
4. Run `make`
5. Run `./build/scheduler`
---
## Usage
### Running the Program
```bash
# Build and run
make run
# Or build first, then run
make
./build/scheduler
```
### Main Menu
When you run the program, you'll see:
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
After selecting an algorithm, you'll choose input method:
```
How do you want to input process data?
  1. Read from file
  2. Enter from keyboard
  3. Use sample data

Enter your choice [1-3]: _
```
---
##  Input Format

### File Input Format

Text File (.txt):
```
n
PID1 ArrivalTime1 BurstTime1 Priority1
PID2 ArrivalTime2 BurstTime2 Priority2
...
PIDn ArrivalTimen BurstTimen Priorityn
```
Example (`test1.txt`):
```
4
1 0 5 2
2 1 3 1
3 2 8 3
4 3 6 2
```
Explanation:
- Line 1: `4` = Number of processes
- Line 2: `1 0 5 2` = PID=1, AT=0, BT=5, Priority=2
- Line 3: `2 1 3 1` = PID=2, AT=1, BT=3, Priority=1
- And so on...
### CSV Input Format
```csv
PID,ArrivalTime,BurstTime,Priority
1,0,5,2
2,1,3,1
3,2,8,3
4,3,6,2
```
### Keyboard Input
```
Enter number of processes: 4
Enter process details (Format: PID AT BT Priority)
Process 1: 1 0 5 2
Process 2: 2 1 3 1
Process 3: 3 2 8 3
Process 4: 4 3 6 2
```
### Input Constraints
- **Number of processes (n):** 1 ≤ n ≤ 100
- **Process ID (PID):** Must be positive and unique
- **Arrival Time (AT):** AT ≥ 0
- **Burst Time (BT):** BT > 0
- **Priority:** Priority ≥ 0 (lower number = higher priority)
---
## Output Format

### Results Table
```
================================================================================
                       FCFS Scheduling Results
================================================================================
+-----+-----+-----+----------+-----+-----+-----+-----+
| PID |  AT |  BT | Priority |  CT | TAT |  WT |  RT |
+-----+-----+-----+----------+-----+-----+-----+-----+
|   1 |   0 |   5 |        2 |   5 |   5 |   0 |   0 |
|   2 |   1 |   3 |        1 |   8 |   7 |   4 |   5 |
|   3 |   2 |   8 |        3 |  16 |  14 |   6 |   8 |
|   4 |   3 |   6 |        2 |  22 |  19 |  13 |  13 |
+-----+-----+-----+----------+-----+-----+-----+-----+

Average Waiting Time    : 5.75
Average Turnaround Time : 11.25
Average Response Time   : 6.50
CPU Utilization         : 100.00%
Throughput              : 0.18 processes/unit
================================================================================
```

### Gantt Chart
```
Gantt Chart:
+----+----+----+----+
| P1 | P2 | P3 | P4 |
+----+----+----+----+
0    5    8   16   22
```
### Comparison Output
```
================================================================================
                    Algorithm Comparison
================================================================================
+-------------------+---------+---------+---------+
| Algorithm         | Avg WT  | Avg TAT | Avg RT  |
+-------------------+---------+---------+---------+
| FCFS              |    5.75 |   11.25 |    6.50 |
| SJF               |    3.50 |    9.00 |    4.75 |
| SRTF              |    2.75 |    8.25 |    3.50 |
| Priority (NP)     |    4.25 |    9.75 |    5.25 |
| Priority (P)      |    3.00 |    8.50 |    4.00 |
| Round Robin (TQ=2)|    7.50 |   13.00 |    8.25 |
+-------------------+---------+---------+---------+

⭐ Best Algorithm (Lowest Avg WT): SRTF (2.75)
================================================================================
```

---

## 👥 Team Members

| Name | Student ID | Role | Responsibilities |
|------|-----------|------|------------------|
| Le Thi Duc Hanh  | 23IT065 | Team Leader | FCFS, Priority NP, Main Menu, Integration, Report Coordination |
| Truong Phuoc Toan  | 23IT278 | Developer | SJF, SRTF, I/O Module, Metrics Calculation, Testing |
| Pham Duy Kha | 23IT118 | Developer | Round Robin, Priority P, UI/Display, Gantt Chart, Documentation |
### Task Distribution
**Member 1 (40% code workload):**
- Algorithms: FCFS, Priority Non-preemptive
- Main menu and program flow
- Integration and code review
- Report: Introduction, System Design, Conclusion
**Member 2 (45% code workload):**
- Algorithms: SJF, SRTF
- I/O module (file/keyboard input, output)
- Metrics calculation
- Report: Implementation, Testing
**Member 3 (50% code workload):**
- Algorithms: Round Robin, Priority Preemptive
- UI/Display module
- Gantt chart visualization
- Report: Results, Analysis
---
## Performance Metrics
### Calculated Metrics
1. Completion Time (CT)
- Time when process finishes execution
- CT = Time when process completes
2. Turnaround Time (TAT)
- Total time from arrival to completion
- Formula: `TAT = CT - AT`
3. Waiting Time (WT)
- Time spent waiting in ready queue
- Formula: `WT = TAT - BT`
4. Response Time (RT)
- Time from arrival to first execution
- Formula: `RT = Start Time - AT`
5. CPU Utilization
- Percentage of time CPU is busy
- Formula: `CPU Util = (Total Burst Time / Total Time) × 100%`
6. Throughput
- Number of processes completed per unit time
- Formula: `Throughput = Number of Processes / Total Time`
### Example Calculation
Input:
```
PID  AT  BT
1    0   5
2    1   3
3    2   8
```
FCFS Calculation:
- P1: CT=5, TAT=5-0=5, WT=5-5=0, RT=0-0=0
- P2: CT=8, TAT=8-1=7, WT=7-3=4, RT=5-1=4
- P3: CT=16, TAT=16-2=14, WT=14-8=6, RT=8-2=6
Averages:
- Avg WT = (0+4+6)/3 = 3.33
- Avg TAT = (5+7+14)/3 = 8.67
- Avg RT = (0+4+6)/3 = 3.33
---
## Screenshots
(Screenshots will be added after implementation)
- Main Menu
- FCFS Results
- Gantt Chart
- Comparison Table
- Input from File
---
## Testing
### Running Tests
```bash
# Run all tests
make test
# Run specific test
./build/scheduler < tests/test_cases/test1.txt
```
### Test Cases
**test1.txt** - Basic example (4 processes)
**test2.txt** - Medium complexity (7 processes)
**test_complex.txt** - Stress test (10+ processes)
**test_edge_cases.txt** - Edge cases (same AT, same BT)
### Creating Custom Tests
1. Create file in `tests/test_cases/`
2. Follow input format
3. Run: `./build/scheduler < tests/test_cases/your_test.txt`
4. Verify results manually
---
## Contributing
This is a course project, but suggestions are welcome!
1. Fork the repository
2. Create feature branch (`git checkout -b feature/YourFeature`)
3. Commit changes (`git commit -m 'Add YourFeature'`)
4. Push to branch (`git push origin feature/YourFeature`)
5. Open Pull Request
---
##  License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```
MIT License
Copyright (c) 2025 FireWind Schedulers Team
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```
---
## References
### Books
1. Advanced Programming in the UNIX Environment (3rd Edition)  
   Author: W.Richard Stevens, Stephen A.Rago 

2. The_C_Programming_Language_(2nd_Edition_Ritchie_Kernighan).pdf
   Author: Brian W. Kernighan , Dennis M. Ritchie 

### Online Resources
1. [GeeksforGeeks - CPU Scheduling](https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/)
2. [Tutorialspoint - OS Scheduling Algorithms](https://www.tutorialspoint.com/operating_system/os_process_scheduling.htm)
3. [Wikipedia - Scheduling (computing)](https://en.wikipedia.org/wiki/Scheduling_(computing))
---
## Contact
For questions, issues, or suggestions:
- Email: hanhltd.23it@vku.udn.vn
- GitHub Issues: [Open an issue](https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky/issues)
- Course: Operating Systems - System Programming
- Institution: VIETNAM-KOREA UNIVERSITY OF INFORMATION AND COMMUNICATION TECHNOLOGY (VKU) - UNIVERSITY OF DANANG
- Semester: Fall 2025 / Spring 2026
---
## Project Status
- [x] Project structure setup
- [x] Header files created
- [ ] Core algorithms implementation
- [ ] I/O module implementation
- [ ] UI/Display implementation
- [ ] Testing and debugging
- [ ] Documentation completion
- [ ] Final presentation
---
## Acknowledgments
- Instructor: PhD.Nguyen Nhat An for guidance and support
- Teaching Assistants: For answering questions
- Classmates: For discussions and feedback
- Open Source Community: For inspiration and resources
---
Last Updated: December 3, 2025  
Version: 0.1.0 (In Development)  
Maintained by: FireWind Schedulers Team
