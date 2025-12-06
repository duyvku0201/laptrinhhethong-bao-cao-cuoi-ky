#include "algorithms.h"
#include "process.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>


void sjf(Process Processes[], int ProcessCount) {
    int CurrentTime = 0;
    int CompletedCount = 0;
    int MinBurstTime;
    int ShortestIndex = -1;
    bool HasProcess;

    // Khởi tạo các giá trị ban đầu cho từng tiến trình
    for (int i = 0; i < ProcessCount; i++) {
        Processes[i].RemainingTime = Processes[i].BurstTime;
        Processes[i].IsCompleted = false;
        Processes[i].StartTime = -1;
        Processes[i].WaitingTime = 0;
        Processes[i].TurnaroundTime = 0;
        Processes[i].ResponseTime = -1;
        Processes[i].CompletionTime = 0;
    }

    // Vòng lặp chính: tiếp tục cho đến khi tất cả tiến trình hoàn thành
    while (CompletedCount != ProcessCount) {
        MinBurstTime = INT_MAX;
        ShortestIndex = -1;
        HasProcess = false;

        // Tìm tiến trình có Burst Time nhỏ nhất trong các tiến trình đã đến và chưa hoàn thành
        for (int i = 0; i < ProcessCount; i++) {
            if (Processes[i].ArrivalTime <= CurrentTime &&
                !Processes[i].IsCompleted) {

                // Nếu tìm thấy tiến trình có Burst Time nhỏ hơn
                if (Processes[i].BurstTime < MinBurstTime) {
                    MinBurstTime = Processes[i].BurstTime;
                    ShortestIndex = i;
                    HasProcess = true;
                }
                // Nếu Burst Time bằng nhau, chọn tiến trình đến trước (FCFS)
                else if (Processes[i].BurstTime == MinBurstTime) {
                    if (ShortestIndex == -1 ||
                        Processes[i].ArrivalTime < Processes[ShortestIndex].ArrivalTime) {
                        ShortestIndex = i;
                        HasProcess = true;
                    }
                }
            }
        }

        // Nếu không có tiến trình nào sẵn sàng, nhảy đến thời điểm tiến trình tiếp theo đến
        if (!HasProcess) {
            CurrentTime++;
            continue;
        }

        // Ghi nhận thời điểm bắt đầu (Start Time) và tính Response Time
        Processes[ShortestIndex].StartTime = CurrentTime;
        Processes[ShortestIndex].ResponseTime = CurrentTime - Processes[ShortestIndex].ArrivalTime;

        // Thực thi tiến trình hoàn toàn (non-preemptive - không ngắt)
        CurrentTime += Processes[ShortestIndex].BurstTime;

        // Đánh dấu tiến trình đã hoàn thành
        Processes[ShortestIndex].CompletionTime = CurrentTime;
        Processes[ShortestIndex].IsCompleted = true;
        Processes[ShortestIndex].RemainingTime = 0;

        // Tính toán Turnaround Time và Waiting Time
        Processes[ShortestIndex].TurnaroundTime =
            Processes[ShortestIndex].CompletionTime - Processes[ShortestIndex].ArrivalTime;
        Processes[ShortestIndex].WaitingTime =
            Processes[ShortestIndex].TurnaroundTime - Processes[ShortestIndex].BurstTime;

        // Tăng số lượng tiến trình đã hoàn thành
        CompletedCount++;
    }

    // Hàm chỉ tính toán, không hiển thị
    // Kết quả được lưu trong mảng Processes và sẽ được hiển thị bởi output.c
}