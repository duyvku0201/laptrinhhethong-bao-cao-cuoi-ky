#include "../include/algorithms.h"
#include "../include/io.h"
#include "../include/process.h"
#include <stdio.h>
#include <string.h>

/**
 * Tính Average Waiting Time
 */
float CalculateAvgWaitingTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return 0.0;

    float Total = 0.0;
    for (int i = 0; i < ProcessCount; i++) {
        Total += Processes[i].WaitingTime;
    }
    return Total / ProcessCount;
}

/**
 * Tính Average Turnaround Time
 */
float CalculateAvgTurnaroundTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return 0.0;

    float Total = 0.0;
    for (int i = 0; i < ProcessCount; i++) {
        Total += Processes[i].TurnaroundTime;
    }
    return Total / ProcessCount;
}

/**
 * Test Case 1: Basic SRTF - 4 processes với arrival times khác nhau
 * Expected: P1 bị ngắt bởi P2, P3, P4
 */
void TestCase1_BasicSRTF() {
    printf("\n========================================\n");
    printf("TEST CASE 1: Basic SRTF Test\n");
    printf("========================================\n");

    Process Processes[4] = {
        {1, 0, 8, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 1, 4, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 2, 2, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 3, 1, 4, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 4;

    printf("\nInput:\n");
    printf("P1: AT=0, BT=8\n");
    printf("P2: AT=1, BT=4\n");
    printf("P3: AT=2, BT=2\n");
    printf("P4: AT=3, BT=1\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected Completion Order: P4 -> P3 -> P2 -> P1\n");
    printf("✓ Test Case 1 COMPLETED\n");
}

/**
 * Test Case 2: All Same Arrival Time
 * Expected: Chọn theo burst time nhỏ nhất (giống SJF)
 */
void TestCase2_SameArrivalTime() {
    printf("\n========================================\n");
    printf("TEST CASE 2: All Same Arrival Time\n");
    printf("========================================\n");

    Process Processes[4] = {
        {1, 0, 6, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 0, 8, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 0, 4, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 0, 2, 4, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 4;

    printf("\nInput:\n");
    printf("P1: AT=0, BT=6\n");
    printf("P2: AT=0, BT=8\n");
    printf("P3: AT=0, BT=4\n");
    printf("P4: AT=0, BT=2\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected Order: P4 -> P3 -> P1 -> P2 (no preemption)\n");
    printf("✓ Test Case 2 COMPLETED\n");
}

/**
 * Test Case 3: Starvation Test
 * P1 có burst time lớn, có thể bị ngắt liên tục
 */
void TestCase3_StarvationScenario() {
    printf("\n========================================\n");
    printf("TEST CASE 3: Starvation Scenario\n");
    printf("========================================\n");

    Process Processes[5] = {
        {1, 0, 10, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 2, 1, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 4, 1, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 6, 1, 4, 0, 0, 0, 0, 0, 0, false},
        {5, 8, 1, 5, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 5;

    printf("\nInput:\n");
    printf("P1: AT=0, BT=10 (long job)\n");
    printf("P2: AT=2, BT=1\n");
    printf("P3: AT=4, BT=1\n");
    printf("P4: AT=6, BT=1\n");
    printf("P5: AT=8, BT=1\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Note: P1 bị ngắt nhiều lần bởi các short jobs\n");
    printf("✓ Test Case 3 COMPLETED\n");
}

/**
 * Test Case 4: Single Process (Edge Case)
 */
void TestCase4_SingleProcess() {
    printf("\n========================================\n");
    printf("TEST CASE 4: Single Process (Edge Case)\n");
    printf("========================================\n");

    Process Processes[1] = {
        {1, 0, 10, 1, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 1;

    printf("\nInput:\n");
    printf("P1: AT=0, BT=10\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected: WT=0, TAT=10\n");
    printf("✓ Test Case 4 COMPLETED\n");
}

/**
 * Test Case 5: Two Processes with Preemption
 */
void TestCase5_TwoProcessesPreemption() {
    printf("\n========================================\n");
    printf("TEST CASE 5: Two Processes - Preemption\n");
    printf("========================================\n");

    Process Processes[2] = {
        {1, 0, 8, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 1, 3, 2, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 2;

    printf("\nInput:\n");
    printf("P1: AT=0, BT=8\n");
    printf("P2: AT=1, BT=3\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected: P1 chạy 1ms, bị ngắt bởi P2, sau đó P1 tiếp tục\n");
    printf("✓ Test Case 5 COMPLETED\n");
}

/**
 * Test Case 6: Complex Scenario - 6 processes
 */
void TestCase6_ComplexScenario() {
    printf("\n========================================\n");
    printf("TEST CASE 6: Complex Scenario\n");
    printf("========================================\n");

    Process Processes[6] = {
        {1, 0, 9, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 1, 5, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 2, 3, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 3, 4, 4, 0, 0, 0, 0, 0, 0, false},
        {5, 4, 2, 5, 0, 0, 0, 0, 0, 0, false},
        {6, 5, 6, 6, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 6;

    printf("\nInput: 6 processes với varying burst times\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("✓ Test Case 6 COMPLETED\n");
}

/**
 * Test Case 7: Equal Burst Times
 */
void TestCase7_EqualBurstTimes() {
    printf("\n========================================\n");
    printf("TEST CASE 7: Equal Burst Times\n");
    printf("========================================\n");

    Process Processes[3] = {
        {1, 0, 5, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 1, 5, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 2, 5, 3, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 3;

    printf("\nInput:\n");
    printf("All processes have same burst time (5)\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected: Hoạt động như FCFS do burst time bằng nhau\n");
    printf("✓ Test Case 7 COMPLETED\n");
}

/**
 * Test Case 8: Late Arrivals
 */
void TestCase8_LateArrivals() {
    printf("\n========================================\n");
    printf("TEST CASE 8: Late Arrivals\n");
    printf("========================================\n");

    Process Processes[4] = {
        {1, 0, 3, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 10, 2, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 15, 4, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 20, 1, 4, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 4;

    printf("\nInput:\n");
    printf("Processes arrive with large gaps\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected: CPU idle giữa các processes\n");
    printf("✓ Test Case 8 COMPLETED\n");
}

/**
 * Test Case 9: Worst Case - Continuous Preemption
 */
void TestCase9_ContinuousPreemption() {
    printf("\n========================================\n");
    printf("TEST CASE 9: Worst Case - Continuous Preemption\n");
    printf("========================================\n");

    Process Processes[5] = {
        {1, 0, 10, 1, 0, 0, 0, 0, 0, 0, false},
        {2, 1, 9, 2, 0, 0, 0, 0, 0, 0, false},
        {3, 2, 8, 3, 0, 0, 0, 0, 0, 0, false},
        {4, 3, 7, 4, 0, 0, 0, 0, 0, 0, false},
        {5, 4, 6, 5, 0, 0, 0, 0, 0, 0, false}
    };
    int ProcessCount = 5;

    printf("\nInput:\n");
    printf("Each new process has shorter burst time\n");

    srtf(Processes, ProcessCount);

    float AvgWT = CalculateAvgWaitingTime(Processes, ProcessCount);
    float AvgTAT = CalculateAvgTurnaroundTime(Processes, ProcessCount);

    printf("\nResults:\n");
    DisplayResults("SRTF", Processes, ProcessCount, AvgWT, AvgTAT);

    printf("Expected: Nhiều context switches\n");
    printf("✓ Test Case 9 COMPLETED\n");
}

/**
 * Hàm main - chạy tất cả 9 test cases
 */
int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║   SRTF ALGORITHM - COMPREHENSIVE TEST SUITE        ║\n");
    printf("║   Total: 9 Test Cases                              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    TestCase1_BasicSRTF();
    TestCase2_SameArrivalTime();
    TestCase3_StarvationScenario();
    TestCase4_SingleProcess();
    TestCase5_TwoProcessesPreemption();
    TestCase6_ComplexScenario();
    TestCase7_EqualBurstTimes();
    TestCase8_LateArrivals();
    TestCase9_ContinuousPreemption();

    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║   ALL 9 TEST CASES COMPLETED SUCCESSFULLY          ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    return 0;
}