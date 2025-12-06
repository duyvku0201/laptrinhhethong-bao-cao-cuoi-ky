/**
 * @file process.c
 * @brief Quản lý tiến trình (Process Management)
 * @author Team CPU Scheduling
 */

#include "process.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * Khởi tạo một tiến trình với giá trị mặc định
  * @param ProcessData Con trỏ tới tiến trình cần khởi tạo
  */
void InitProcess(Process* ProcessData) {
    if (!ProcessData) return;

    ProcessData->ProcessId = 0;
    ProcessData->ArrivalTime = 0;
    ProcessData->BurstTime = 0;
    ProcessData->Priority = 0;
    ProcessData->RemainingTime = 0;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;  // -1 nghĩa là chưa bắt đầu
    ProcessData->CompletionTime = 0;
    ProcessData->StartTime = -1;     // -1 nghĩa là chưa bắt đầu
    ProcessData->IsCompleted = false;
}

/**
 * Tạo tiến trình mới với các tham số cho trước
 * @param Id ID của tiến trình
 * @param Arrival Thời điểm tiến trình đến hệ thống
 * @param Burst Thời gian CPU cần để hoàn thành
 * @param Priority Mức độ ưu tiên
 * @return Tiến trình đã được khởi tạo
 */
Process CreateProcess(int Id, int Arrival, int Burst, int Priority) {
    Process NewProcess;
    NewProcess.ProcessId = Id;
    NewProcess.ArrivalTime = Arrival;
    NewProcess.BurstTime = Burst;
    NewProcess.Priority = Priority;
    NewProcess.RemainingTime = Burst;
    NewProcess.WaitingTime = 0;
    NewProcess.TurnaroundTime = 0;
    NewProcess.ResponseTime = -1;
    NewProcess.CompletionTime = 0;
    NewProcess.StartTime = -1;
    NewProcess.IsCompleted = false;

    return NewProcess;
}

/**
 * Đặt lại tiến trình về trạng thái ban đầu (giữ nguyên thông tin cơ bản)
 * @param ProcessData Con trỏ tới tiến trình cần reset
 */
void ResetProcess(Process* ProcessData) {
    if (!ProcessData) return;

    ProcessData->RemainingTime = ProcessData->BurstTime;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;
    ProcessData->CompletionTime = 0;
    ProcessData->StartTime = -1;
    ProcessData->IsCompleted = false;
}

/**
 * Kiểm tra tiến trình đã hoàn thành chưa
 * @param ProcessData Con trỏ tới tiến trình
 * @return true nếu đã hoàn thành, false nếu chưa
 */
bool IsProcessCompleted(const Process* ProcessData) {
    if (!ProcessData) return true;
    return ProcessData->IsCompleted || ProcessData->RemainingTime <= 0;
}

/**
 * Kiểm tra tiến trình đã bắt đầu thực thi chưa
 * @param ProcessData Con trỏ tới tiến trình
 * @return true nếu đã bắt đầu, false nếu chưa
 */
bool HasProcessStarted(const Process* ProcessData) {
    if (!ProcessData) return false;
    return ProcessData->StartTime >= 0;
}

/**
 * Đánh dấu tiến trình bắt đầu thực thi tại thời điểm hiện tại
 * @param ProcessData Con trỏ tới tiến trình
 * @param CurrentTime Thời điểm bắt đầu thực thi
 */
void StartProcess(Process* ProcessData, int CurrentTime) {
    if (!ProcessData) return;

    // Chỉ ghi nhận thời điểm bắt đầu lần đầu tiên
    if (ProcessData->StartTime < 0) {
        ProcessData->StartTime = CurrentTime;
        ProcessData->ResponseTime = CurrentTime - ProcessData->ArrivalTime;
    }
}

/**
 * Thực thi tiến trình trong một khoảng thời gian
 * @param ProcessData Con trỏ tới tiến trình
 * @param TimeUnits Số đơn vị thời gian cần thực thi
 * @return Số đơn vị thời gian thực sự đã thực thi
 */
int ExecuteProcess(Process* ProcessData, int TimeUnits) {
    if (!ProcessData || ProcessData->IsCompleted || ProcessData->RemainingTime <= 0) {
        return 0;
    }

    int ExecutedTime = min_int(TimeUnits, ProcessData->RemainingTime);
    ProcessData->RemainingTime -= ExecutedTime;

    if (ProcessData->RemainingTime <= 0) {
        ProcessData->RemainingTime = 0;
        ProcessData->IsCompleted = true;
    }

    return ExecutedTime;
}

/**
 * Đánh dấu tiến trình hoàn thành và tính toán các metrics
 * @param ProcessData Con trỏ tới tiến trình
 * @param CurrentTime Thời điểm hoàn thành
 */
void CompleteProcess(Process* ProcessData, int CurrentTime) {
    if (!ProcessData) return;

    ProcessData->IsCompleted = true;
    ProcessData->RemainingTime = 0;
    ProcessData->CompletionTime = CurrentTime;
    ProcessData->TurnaroundTime = ProcessData->CompletionTime - ProcessData->ArrivalTime;
    ProcessData->WaitingTime = ProcessData->TurnaroundTime - ProcessData->BurstTime;

    // Đảm bảo thời gian chờ không âm
    if (ProcessData->WaitingTime < 0) {
        ProcessData->WaitingTime = 0;
    }
}

/**
 * Sao chép thông tin từ tiến trình nguồn sang tiến trình đích
 * @param Destination Con trỏ tới tiến trình đích
 * @param Source Con trỏ tới tiến trình nguồn
 */
void CopyProcess(Process* Destination, const Process* Source) {
    if (!Destination || !Source) return;

    *Destination = *Source;
}

/**
 * So sánh hai tiến trình theo thời điểm đến (Arrival Time)
 * Dùng cho thuật toán FCFS và các thuật toán khác cần sắp xếp theo AT
 * @param First Con trỏ tới tiến trình thứ nhất
 * @param Second Con trỏ tới tiến trình thứ hai
 * @return Âm nếu First < Second, 0 nếu bằng, Dương nếu First > Second
 */
int CompareProcessByArrival(const void* First, const void* Second) {
    const Process* Process1 = (const Process*)First;
    const Process* Process2 = (const Process*)Second;

    if (Process1->ArrivalTime != Process2->ArrivalTime) {
        return Process1->ArrivalTime - Process2->ArrivalTime;
    }
    // Nếu cùng thời điểm đến, ưu tiên theo ID
    return Process1->ProcessId - Process2->ProcessId;
}

/**
 * So sánh hai tiến trình theo thời gian CPU (Burst Time)
 * Dùng cho thuật toán SJF (Shortest Job First)
 * @param First Con trỏ tới tiến trình thứ nhất
 * @param Second Con trỏ tới tiến trình thứ hai
 * @return Âm nếu First < Second, 0 nếu bằng, Dương nếu First > Second
 */
int CompareProcessByBurst(const void* First, const void* Second) {
    const Process* Process1 = (const Process*)First;
    const Process* Process2 = (const Process*)Second;

    if (Process1->BurstTime != Process2->BurstTime) {
        return Process1->BurstTime - Process2->BurstTime;
    }
    // Nếu cùng burst time, ưu tiên theo thời điểm đến
    return Process1->ArrivalTime - Process2->ArrivalTime;
}

/**
 * So sánh hai tiến trình theo thời gian còn lại (Remaining Time)
 * Dùng cho thuật toán SRTF (Shortest Remaining Time First)
 * @param First Con trỏ tới tiến trình thứ nhất
 * @param Second Con trỏ tới tiến trình thứ hai
 * @return Âm nếu First < Second, 0 nếu bằng, Dương nếu First > Second
 */
int CompareProcessByRemaining(const void* First, const void* Second) {
    const Process* Process1 = (const Process*)First;
    const Process* Process2 = (const Process*)Second;

    if (Process1->RemainingTime != Process2->RemainingTime) {
        return Process1->RemainingTime - Process2->RemainingTime;
    }
    // Nếu cùng remaining time, ưu tiên theo thời điểm đến
    return Process1->ArrivalTime - Process2->ArrivalTime;
}

/**
 * So sánh hai tiến trình theo mức độ ưu tiên (Priority)
 * Dùng cho thuật toán Priority Scheduling (số nhỏ = ưu tiên cao)
 * @param First Con trỏ tới tiến trình thứ nhất
 * @param Second Con trỏ tới tiến trình thứ hai
 * @return Âm nếu First có priority cao hơn, 0 nếu bằng, Dương nếu thấp hơn
 */
int CompareProcessByPriority(const void* First, const void* Second) {
    const Process* Process1 = (const Process*)First;
    const Process* Process2 = (const Process*)Second;

    if (Process1->Priority != Process2->Priority) {
        return Process1->Priority - Process2->Priority;  // Số nhỏ = ưu tiên cao
    }
    // Nếu cùng priority, ưu tiên theo thời điểm đến
    return Process1->ArrivalTime - Process2->ArrivalTime;
}

/**
 * So sánh hai tiến trình theo ID
 * Dùng để sắp xếp lại danh sách theo thứ tự ban đầu
 * @param First Con trỏ tới tiến trình thứ nhất
 * @param Second Con trỏ tới tiến trình thứ hai
 * @return Âm nếu First < Second, 0 nếu bằng, Dương nếu First > Second
 */
int CompareProcessById(const void* First, const void* Second) {
    const Process* Process1 = (const Process*)First;
    const Process* Process2 = (const Process*)Second;

    return Process1->ProcessId - Process2->ProcessId;
}

/**
 * Kiểm tra tính hợp lệ của thông tin tiến trình
 * @param ProcessData Con trỏ tới tiến trình cần kiểm tra
 * @return true nếu hợp lệ, false nếu không hợp lệ
 */
bool ValidateProcess(const Process* ProcessData) {
    if (!ProcessData) return false;

    // Kiểm tra các giá trị cơ bản
    if (ProcessData->ProcessId < 0) return false;
    if (ProcessData->ArrivalTime < 0) return false;
    if (ProcessData->BurstTime <= 0) return false;
    if (ProcessData->RemainingTime < 0) return false;
    if (ProcessData->RemainingTime > ProcessData->BurstTime) return false;

    return true;
}

/**
 * Hiển thị thông tin chi tiết của tiến trình
 * @param ProcessData Con trỏ tới tiến trình
 */
void PrintProcess(const Process* ProcessData) {
    if (!ProcessData) {
        printf("NULL process\n");
        return;
    }

    printf("Process P%d:\n", ProcessData->ProcessId);
    printf("  Arrival Time: %d\n", ProcessData->ArrivalTime);
    printf("  Burst Time: %d\n", ProcessData->BurstTime);
    printf("  Priority: %d\n", ProcessData->Priority);
    printf("  Remaining Time: %d\n", ProcessData->RemainingTime);
    printf("  Start Time: %d\n", ProcessData->StartTime);
    printf("  Completion Time: %d\n", ProcessData->CompletionTime);
    printf("  Waiting Time: %d\n", ProcessData->WaitingTime);
    printf("  Turnaround Time: %d\n", ProcessData->TurnaroundTime);
    printf("  Response Time: %d\n", ProcessData->ResponseTime);
    printf("  Status: %s\n", ProcessData->IsCompleted ? "Completed" : "Incomplete");
}

/**
 * Hiển thị thông tin ngắn gọn của tiến trình (một dòng)
 * @param ProcessData Con trỏ tới tiến trình
 */
void PrintProcessShort(const Process* ProcessData) {
    if (!ProcessData) {
        printf("NULL\n");
        return;
    }

    printf("P%d [AT:%d BT:%d RT:%d Pri:%d %s]\n",
        ProcessData->ProcessId,
        ProcessData->ArrivalTime,
        ProcessData->BurstTime,
        ProcessData->RemainingTime,
        ProcessData->Priority,
        ProcessData->IsCompleted ? "✓" : "○");
}