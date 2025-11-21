#include "../../include/algorithms.h"
#include "../../include/process.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/**
 * Thuật toán SRTF (Shortest Remaining Time First) - SJF có ưu tiên ngắt
 *
 * Giải thích:
 * - Tại mỗi đơn vị thời gian, CPU chọn tiến trình có thời gian còn lại nhỏ nhất
 * - Khi có tiến trình mới đến với thời gian còn lại nhỏ hơn, CPU ngắt tiến trình hiện tại
 * - Đây là phiên bản preemptive (có ưu tiên ngắt) của thuật toán SJF
 *
 * @param Processes Mảng chứa danh sách các tiến trình cần lập lịch
 * @param ProcessCount Số lượng tiến trình trong mảng
 */
void srtf(Process Processes[], int ProcessCount) {
    int CurrentTime = 0;
    int CompletedCount = 0;
    int MinRemainingTime;
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
        MinRemainingTime = INT_MAX;
        ShortestIndex = -1;
        HasProcess = false;

        // Tìm tiến trình có thời gian còn lại nhỏ nhất trong các tiến trình đã đến
        for (int i = 0; i < ProcessCount; i++) {
            if (Processes[i].ArrivalTime <= CurrentTime &&
                !Processes[i].IsCompleted &&
                Processes[i].RemainingTime < MinRemainingTime) {
                MinRemainingTime = Processes[i].RemainingTime;
                ShortestIndex = i;
                HasProcess = true;
            }
        }

        // Nếu không có tiến trình nào sẵn sàng, nhảy đến thời điểm tiến trình tiếp theo đến
        if (!HasProcess) {
            CurrentTime++;
            continue;
        }

        // Ghi nhận thời điểm bắt đầu lần đầu tiên (để tính Response Time)
        if (Processes[ShortestIndex].StartTime == -1) {
            Processes[ShortestIndex].StartTime = CurrentTime;
            Processes[ShortestIndex].ResponseTime = CurrentTime - Processes[ShortestIndex].ArrivalTime;
        }

        // Thực thi tiến trình trong 1 đơn vị thời gian
        Processes[ShortestIndex].RemainingTime--;
        CurrentTime++;

        // Kiểm tra xem tiến trình có hoàn thành không
        if (Processes[ShortestIndex].RemainingTime == 0) {
            CompletedCount++;
            Processes[ShortestIndex].IsCompleted = true;
            Processes[ShortestIndex].CompletionTime = CurrentTime;

            // Tính toán Turnaround Time và Waiting Time
            Processes[ShortestIndex].TurnaroundTime =
                Processes[ShortestIndex].CompletionTime - Processes[ShortestIndex].ArrivalTime;
            Processes[ShortestIndex].WaitingTime =
                Processes[ShortestIndex].TurnaroundTime - Processes[ShortestIndex].BurstTime;
        }
    }

    // Hàm chỉ tính toán, không hiển thị
    // Kết quả được lưu trong mảng Processes và sẽ được hiển thị bởi output.c
}