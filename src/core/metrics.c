#include "metrics.h"
#include <stdio.h>
#include <stdbool.h>

// Tính Waiting Time cho một process
// Công thức: WT = TAT - BT
void CalculateWaitingTime(Process* ProcessData) {
    if (ProcessData == NULL) {
        return;
    }
    ProcessData->WaitingTime = ProcessData->TurnaroundTime - ProcessData->BurstTime;
}

// Tính Turnaround Time cho một process
// Công thức: TAT = CT - AT
void CalculateTurnaroundTime(Process* ProcessData) {
    if (ProcessData == NULL) {
        return;
    }
    ProcessData->TurnaroundTime = ProcessData->CompletionTime - ProcessData->ArrivalTime;
}

// Tính Response Time cho một process
// Công thức: RT = Thời điểm bắt đầu thực thi lần đầu - AT
void CalculateResponseTime(Process* ProcessData, int FirstResponseTime) {
    if (ProcessData == NULL) {
        return;
    }
    ProcessData->ResponseTime = FirstResponseTime - ProcessData->ArrivalTime;
}

// Tính Average Waiting Time cho tất cả processes
// Trả về giá trị trung bình thời gian chờ của tất cả các process
float CalculateAverageWaitingTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) {
        return 0.0f;
    }

    float TotalWaitingTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalWaitingTime += Processes[Index].WaitingTime;
    }

    return TotalWaitingTime / ProcessCount;
}

// Tính Average Turnaround Time cho tất cả processes
// Trả về giá trị trung bình thời gian hoàn thành vòng đời của tất cả các process
float CalculateAverageTurnaroundTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) {
        return 0.0f;
    }

    float TotalTurnaroundTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalTurnaroundTime += Processes[Index].TurnaroundTime;
    }

    return TotalTurnaroundTime / ProcessCount;
}

// Tính Average Response Time cho tất cả processes
// Trả về giá trị trung bình thời gian phản hồi của tất cả các process
float CalculateAverageResponseTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) {
        return 0.0f;
    }

    float TotalResponseTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalResponseTime += Processes[Index].ResponseTime;
    }

    return TotalResponseTime / ProcessCount;
}

// Tính tất cả metrics cho một process
// Tính toán đầy đủ các chỉ số: Turnaround Time, Waiting Time và Response Time
void CalculateProcessMetrics(Process* ProcessData, int FirstResponseTime) {
    if (ProcessData == NULL) {
        return;
    }

    // Tính theo thứ tự: TAT -> WT -> RT
    CalculateTurnaroundTime(ProcessData);
    CalculateWaitingTime(ProcessData);
    CalculateResponseTime(ProcessData, FirstResponseTime);
}

// Tính tất cả metrics cho danh sách processes
// Tính toán metrics cho từng process trong danh sách
void CalculateAllMetrics(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) {
        return;
    }

    for (int Index = 0; Index < ProcessCount; Index++) {
        // Sử dụng StartTime làm FirstResponseTime
        CalculateProcessMetrics(&Processes[Index], Processes[Index].StartTime);
    }
}

// Tính CPU Utilization
// Công thức: CPU Utilization = (Tổng Burst Time / Tổng thời gian) * 100
// Đo lường hiệu suất sử dụng CPU
float CalculateCpuUtilization(Process* Processes, int ProcessCount, int TotalTime) {
    if (Processes == NULL || ProcessCount <= 0 || TotalTime <= 0) {
        return 0.0f;
    }

    int TotalBurstTime = 0;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalBurstTime += Processes[Index].BurstTime;
    }

    return ((float)TotalBurstTime / TotalTime) * 100. 0f;
}

// Tính Throughput
// Công thức: Throughput = Số process hoàn thành / Tổng thời gian
// Đo lường số lượng process được xử lý trong một đơn vị thời gian
float CalculateThroughput(int ProcessCount, int TotalTime) {
    if (ProcessCount <= 0 || TotalTime <= 0) {
        return 0.0f;
    }

    return (float)ProcessCount / TotalTime;
}

// In tất cả metrics
// Hiển thị đầy đủ thông tin metrics của từng process và metrics tổng thể
void DisplayAllMetrics(Process* Processes, int ProcessCount, int TotalTime) {
    if (Processes == NULL || ProcessCount <= 0) {
        printf("Khong co process de hien thi metrics.\n");
        return;
    }

    printf("\n========================================\n");
    printf("           METRICS REPORT\n");
    printf("========================================\n\n");

    // Header của bảng
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("------------------------------------------------------------\n");

    // Hiển thị metrics từng process
    for (int Index = 0; Index < ProcessCount; Index++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            Processes[Index].ProcessId,
            Processes[Index].ArrivalTime,
            Processes[Index].BurstTime,
            Processes[Index].CompletionTime,
            Processes[Index].TurnaroundTime,
            Processes[Index].WaitingTime,
            Processes[Index].ResponseTime);
    }

    printf("------------------------------------------------------------\n\n");

    // Hiển thị metrics trung bình
    printf("Average Waiting Time      : %.2f\n", CalculateAverageWaitingTime(Processes, ProcessCount));
    printf("Average Turnaround Time   : %.2f\n", CalculateAverageTurnaroundTime(Processes, ProcessCount));
    printf("Average Response Time     : %.2f\n", CalculateAverageResponseTime(Processes, ProcessCount));

    if (TotalTime > 0) {
        printf("CPU Utilization           : %.2f%%\n", CalculateCpuUtilization(Processes, ProcessCount, TotalTime));
        printf("Throughput                : %.4f processes/unit time\n", CalculateThroughput(ProcessCount, TotalTime));
    }

    printf("========================================\n\n");
}

// Kiểm tra tính hợp lệ của metrics
// Validate các giá trị metrics để đảm bảo tính chính xác
bool ValidateMetrics(Process* ProcessData) {
    if (ProcessData == NULL) {
        return false;
    }

    // Kiểm tra các giá trị không âm
    if (ProcessData->WaitingTime < 0 ||
        ProcessData->TurnaroundTime < 0 ||
        ProcessData->ResponseTime < 0) {
        return false;
    }

    // Kiểm tra công thức WT = TAT - BT
    if (ProcessData->WaitingTime != (ProcessData->TurnaroundTime - ProcessData->BurstTime)) {
        return false;
    }

    // Kiểm tra công thức TAT = CT - AT
    if (ProcessData->TurnaroundTime != (ProcessData->CompletionTime - ProcessData->ArrivalTime)) {
        return false;
    }

    // Kiểm tra Response Time không âm và không lớn hơn Waiting Time
    if (ProcessData->ResponseTime < 0 || ProcessData->ResponseTime > ProcessData->WaitingTime) {
        return false;
    }

    return true;
}