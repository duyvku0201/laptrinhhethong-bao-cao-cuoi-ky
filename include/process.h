#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_PROCESS_ID_LENGTH 20

// ==============================
// Cấu trúc lưu thông tin process
// ==============================
typedef struct
{
    char ProcessId[MAX_PROCESS_ID_LENGTH]; // ID tiến trình dạng chuỗi
    int ArrivalTime;                       // Thời điểm đến
    int BurstTime;                         // Thời gian xử lý
    int Priority;                          // Mức độ ưu tiên
    int RemainingTime;                     // Thời gian còn lại
    int WaitingTime;                       // Thời gian chờ
    int TurnaroundTime;                    // Thời gian hoàn thành vòng đời
    int ResponseTime;                      // Thời gian phản hồi
    int CompletionTime;                    // Thời điểm hoàn thành
    bool IsCompleted;                      // Trạng thái hoàn thành (true/false)

    int pid;            // Mã tiến trình (Process ID - dạng số)
    int arrival_time;   // Thời điểm đến hệ thống
    int burst_time;     // Thời gian cần CPU
    int priority;       // Độ ưu tiên (Priority)
    int remaining_time; // Thời gian còn lại để chạy

    // Thông tin tính toán
    int completion_time; // Thời điểm hoàn thành (CT)
    int waiting_time;    // Thời gian chờ (WT = TAT - BT)
    int turnaround_time; // Thời gian hoàn thành vòng đời (TAT = CT - AT)
    int response_time;   // Thời gian đáp ứng (RT = Start - AT)
    int start_time;      // Thời điểm bắt đầu chạy
    int is_completed;    // 0 = chưa xong, 1 = đã hoàn thành
} Process;

#endif // PROCESS_H
