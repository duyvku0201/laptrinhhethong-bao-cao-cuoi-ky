#pragma once
#ifndef PROCESS_H
#define PROCESS_H

// Cấu trúc dữ liệu mô tả một tiến trình (Process)
typedef struct {
    // THÔNG TIN ĐẦU VÀO 
    int pid;             // Mã tiến trình (Process ID)
    int arrival_time;    // Thời điểm đến hệ thống (Arrival Time)
    int burst_time;      // Thời gian cần CPU để chạy hết (Burst Time)
    int priority;        // Độ ưu tiên (Priority) - số càng nhỏ/càng lớn tùy quy ước
    int remaining_time;  // Thời gian CPU còn lại chưa chạy (dùng cho các giải thuật Preemptive Priority, SRTF, RR)

    // THÔNG TIN TÍNH TOÁN 
    int completion_time;   // Thời điểm tiến trình hoàn thành (Completion Time - CT)
    int waiting_time;      // Thời gian chờ (Waiting Time) = TAT - BT
    int turnaround_time;   // Thời gian hoàn thành vòng đời (Turnaround Time - TAT) = CT - AT
    int response_time;     // Thời gian đáp ứng (Response Time - RT) = thời điểm chạy lần đầu (Start Time) - AT
    int start_time;        // Thời điểm tiến trình được CPU chạy lần đầu tiên (nếu chưa chạy = -1)

    //TRẠNG THÁI
    int is_completed;      // Cờ đánh dấu tiến trình đã hoàn thành hay chưa (0 = chưa xong, 1 = đã xong)
} Process;

#endif // PROCESS_H
