#include "../include/io.h"
#include "../include/process.h"
#include <stdio.h>
#include <string.h>

/**
 * Test 1: Kiểm tra hàm DisplayResults với dữ liệu chuẩn
 */
void Test1_DisplayResults_WithValidData() {
    printf("\n========================================\n");
    printf("TEST 1: DisplayResults - Valid Data\n");
    printf("========================================\n");

    Process TestProcesses[3] = {
        {1, 0, 8, 1, 0, 5, 13, 5, 13, 0, true},
        {2, 1, 4, 2, 0, 7, 10, 6, 10, 1, true},
        {3, 2, 2, 3, 0, 0, 2, 0, 4, 2, true}
    };

    float AvgWT = 4.0;
    float AvgTAT = 8.33;

    DisplayResults("SRTF", TestProcesses, 3, AvgWT, AvgTAT);
    printf("✓ Test 1 PASSED\n");
}

/**
 * Test 2: Kiểm tra hàm DisplayResults với NULL
 */
void Test2_DisplayResults_WithNull() {
    printf("\n========================================\n");
    printf("TEST 2: DisplayResults - NULL Check\n");
    printf("========================================\n");

    DisplayResults("SRTF", NULL, 0, 0.0, 0.0);
    printf("✓ Test 2 PASSED (no crash)\n");
}

/**
 * Test 3: Kiểm tra hàm SaveResultsToFile
 */
void Test3_SaveResultsToFile() {
    printf("\n========================================\n");
    printf("TEST 3: SaveResultsToFile\n");
    printf("========================================\n");

    Process TestProcesses[2] = {
        {1, 0, 5, 1, 0, 0, 5, 0, 5, 0, true},
        {2, 1, 3, 2, 0, 4, 7, 4, 8, 1, true}
    };

    bool Result = SaveResultsToFile("tests/test_results/test_output_result.txt",
        "SRTF",
        TestProcesses,
        2,
        2.0,
        6.0);

    if (Result) {
        printf("✓ Test 3 PASSED - File created successfully\n");
    }
    else {
        printf("✗ Test 3 FAILED\n");
    }
}

/**
 * Test 4: Kiểm tra SaveResultsToFile với NULL
 */
void Test4_SaveResultsToFile_WithNull() {
    printf("\n========================================\n");
    printf("TEST 4: SaveResultsToFile - NULL Check\n");
    printf("========================================\n");

    bool Result = SaveResultsToFile(NULL, NULL, NULL, 0, 0.0, 0.0);

    if (!Result) {
        printf("✓ Test 4 PASSED - Correctly handled NULL\n");
    }
    else {
        printf("✗ Test 4 FAILED\n");
    }
}

/**
 * Test 5: Kiểm tra FileExists
 */
void Test5_FileExists() {
    printf("\n========================================\n");
    printf("TEST 5: FileExists Function\n");
    printf("========================================\n");

    // Test với file tồn tại
    bool Exists = FileExists("tests/test_cases/test_sjf_1.txt");
    printf("Test existing file: %s\n", Exists ? "PASSED" : "FAILED");

    // Test với file không tồn tại
    bool NotExists = FileExists("nonexistent_file.txt");
    printf("Test non-existing file: %s\n", !NotExists ? "PASSED" : "FAILED");

    printf("✓ Test 5 COMPLETED\n");
}

/**
 * Test 6: Kiểm tra ValidateProcessData
 */
void Test6_ValidateProcessData() {
    printf("\n========================================\n");
    printf("TEST 6: ValidateProcessData\n");
    printf("========================================\n");

    // Valid process
    Process ValidProcess = { 1, 0, 5, 1, 5, 0, 0, 0, 0, 0, false };
    bool IsValid = ValidateProcessData(&ValidProcess);
    printf("Valid process test: %s\n", IsValid ? "PASSED" : "FAILED");

    // Invalid process (negative arrival time)
    Process InvalidProcess = { 1, -1, 5, 1, 5, 0, 0, 0, 0, 0, false };
    bool IsInvalid = ValidateProcessData(&InvalidProcess);
    printf("Invalid process test: %s\n", !IsInvalid ? "PASSED" : "FAILED");

    printf("✓ Test 6 COMPLETED\n");
}

/**
 * Main function - chạy tất cả test cases
 */
int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║   OUTPUT FUNCTIONS TEST SUITE                      ║\n");
    printf("║   Testing: DisplayResults, SaveResultsToFile,     ║\n");
    printf("║            FileExists, ValidateProcessData         ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    Test1_DisplayResults_WithValidData();
    Test2_DisplayResults_WithNull();
    Test3_SaveResultsToFile();
    Test4_SaveResultsToFile_WithNull();
    Test5_FileExists();
    Test6_ValidateProcessData();

    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║   ALL TESTS COMPLETED                              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    return 0;
}