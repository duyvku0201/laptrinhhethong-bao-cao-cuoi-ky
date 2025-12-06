/**
* @file fcfs.c
* @brief Thuật toán lập lịch FCFS (First-Come , First-Served)
* FCFS là thuật toán scheduling đơn giản nhất:
* - Non-preemptive: Process một khi bắt đầu sẽ chạy đến khi kết thúc.
* - FIFO: Process nào đến trước sẽ được phục vụ trước.
* - Không có starvation, starvation là tình trạng một process không bao giờ được cấp phát CPU vì các process khác liên tục đến và chiếm CPU.
* - Có thể bị ảnh hưởng bởi hiệu ứng convoy, khi một process dài chiếm CPU, các process ngắn hơn phải chờ đợi lâu hơn.
* Độ phức tạp thời gian: O(n log n) do sorting, do việc sắp xếp các process theo thời gian đến.
*/
#include "algorithms.h"
#include "utils.h"
#include "metrics.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Implement thuật toán FCFS
 * Các bước:
 * 1. Sắp xếp processes theo arrival time (ai đến trước phục vụ trước)
 * 2. Cho từng process chạy tuần tự, không preemption
 * 3. Tính completion time, start time cho mỗi process
 * 4. Tính các metrics (WT, TAT, RT)
 * @param processes Mảng processes
 * @param n Số lượng processes
 * Ví dụ minh họa:
 * Input: P1(AT=0,BT=5), P2(AT=1,BT=3), P3(AT=2,BT=8)
 * Execution:
 * Timeline: |--P1--|--P2--|----P3----|
 *           0     5     8          16
 * P1: Start=0, CT=5, TAT=5, WT=0, RT=0
 * P2: Start=5, CT=8, TAT=7, WT=4, RT=4
 * P3: Start=8, CT=16, TAT=14, WT=6, RT=6
 */
void fcfs(Process processes[], int n) {
	// BƯỚC 1: Sắp xếp theo arrival time (ai đến trước phục vụ trước)
	sort_by_arrival(processes, n);
	// BƯỚC 2: Khởi tạo current_time (thời gian hiện tại của CPU)
	int current_time = 0;
	// BƯỚC 3: Xử lý từng process theo thứ tự đã sắp xếp
	for (int i = 0; i < n; i++) {
		// BƯỚC 3.1: Kiểm tra CPU có idle không (nếu current_time < arrival_time của process hiện tại)
		// Nếu process chưa đến, CPU sẽ idle đến khi process đó đến. idle là thời gian CPU không làm gì. (arrival_time > current_time)
		// -> CPU phải chờ (idle) đến khi process đến. Cập nhật current_time = arrival_time của process hiện tại 
		if (current_time < processes[i].ArrivalTime) {
			current_time = processes[i].ArrivalTime;
		}
		// BƯỚC 3.2: Ghi nhận thời điểm process bắt đầu chạy. (start_time)
		// Start time là thời điểm process bắt đầu được CPU phục vụ lần đầu tiên.
		processes[i].StartTime = current_time;
		// BƯỚC 3.3: Process chạy đến hết burst time (non-preemptive)
		current_time += processes[i].BurstTime;
		// BƯỚC 3.4: Ghi nhận thời điểm process hoàn thành (completion_time)
		// Completion_time là thời điểm process hoàn thành việc chạy.
		processes[i].CompletionTime = current_time;
		// BƯỚC 3.5: Đánh dấu process đã hoàn thành
		processes[i].IsCompleted = 1;
	}
	// BƯỚC 4: Tính các metrics cho từng process (WT,TAT,RT)
	// Hàm này được implement bởi Thành viên 2
	calculate_times(processes, n);
}
/*
 * CHI TIẾT VÍ DỤ FCFS:
 *
 * Input:
 * P1: AT=0, BT=5
 * P2: AT=1, BT=3
 * P3: AT=2, BT=8
 *
 * Sau khi sort_by_arrival: P1, P2, P3 (đã đúng thứ tự)
 *
 * LOOP i=0 (Process P1):
 *   current_time = 0
 *   processes[0].arrival_time = 0
 *   → current_time < 0? NO
 *   → start_time = 0
 *   → current_time = 0 + 5 = 5
 *   → completion_time = 5
 *
 * LOOP i=1 (Process P2):
 *   current_time = 5
 *   processes[1].arrival_time = 1
 *   → current_time < 1? NO (5 > 1)
 *   → start_time = 5
 *   → current_time = 5 + 3 = 8
 *   → completion_time = 8
 *
 * LOOP i=2 (Process P3):
 *   current_time = 8
 *   processes[2].arrival_time = 2
 *   → current_time < 2? NO (8 > 2)
 *   → start_time = 8
 *   → current_time = 8 + 8 = 16
 *   → completion_time = 16
 *
 * Sau khi calculate_times():
 * P1: TAT = 5-0 = 5, WT = 5-5 = 0, RT = 0-0 = 0
 * P2: TAT = 8-1 = 7, WT = 7-3 = 4, RT = 5-1 = 4
 * P3: TAT = 16-2 = 14, WT = 14-8 = 6, RT = 8-2 = 6
 *
 * Average WT = (0+4+6)/3 = 3.33
 * Average TAT = (5+7+14)/3 = 8.67
 */