/**
* @file priority_np.c
* @brief Thuật toán Priority Scheduling (Non-Preemptive)
* Priority Scheduling (Non-Preemptive):
* - Chọn process có priority cao nhất (số priority nhỏ nhất) để thực thi tiếp theo
* - Non-preemptive: Một khi một process bắt đầu thực thi, nó sẽ chạy đến khi hoàn thành
* - Nếu priority bằng nhau -> dùng FCFS để chọn process tiếp theo
* - Thích hợp cho các hệ thống mà các process có mức độ ưu tiên khác nhau rõ ràng
* - Có thể dẫn đến hiện tượng "starvation" cho các process có priority thấp
* Priority: 1 > 2 > 3 > ... (số nhỏ = ưu tiên cao)
*/

#include "algorithms.h"
#include "utils.h"
#include "metrics.h"
#include <stdio.h>>
/**
* @brief Hàm thực hiện thuật toán Priority Scheduling (Non-Preemptive) algorithm
* THUẬT TOÁN:
* 1. Tại mỗi thời điểm scheduling, chọn process có priority cao nhất (số priority nhỏ nhất) trong số các process đã sẵn sàng
*  - Tìm process có priority cao nhất (số priority nhỏ nhất) trong danh sách đã đến và chưa hoàn thành
*  - Nếu có nhiều process có cùng priority, chọn process đến trước (FCFS)
* 2. Process được chọn chạy đến khi hoàn thành
* 3. Lặp lại cho đến khi tất cả các process hòan thành
* @param processes Mảng các processes
* @param n Số lượng processes
* VÍ DỤ:
* Giả sử có 3 process:
* P1: AT=0, BT=5, Priority=2
* P2: AT=1, BT=3, Priority=1 (priority cao nhất)
* P3: AT=2, BT=8, Priority=3
* Kết quả thực thi:
* Tại t=0: Chỉ P1 có mặt, chạy P1
* Tại t=1: P2 đến, có priority cao hơn P1, nhưng P1 đang chạy (non-preemptive), tiếp tục chạy P1
* Tại t=5: P1 hoàn thành, chọn P2 (priority cao nhất)
* Tại t=8: P2 hoàn thành, chọn P3
* Tại t=16: P3 hoàn thành, tất cả process hoàn thành
* Timeline: |----P1----|---P2---|--------P3--------|
*           0          5        8                  16
*/
void priority_non_preemptive(Process processes[], int n) {
	//BƯỚC 1: Khởi tạo biến
	int current_time = 0; // Thời gian hiện tại
	int completed = 0;    // Số processes đã xong
	int is_completed[100] = { 0 }; // Mảng đánh dấu process đã hoàn thành
	//BƯỚC 2: Lặp cho đến khi tất cả process hoàn thành
	while (completed < n) {
		//BƯỚC 2.1: Tìm process có priority cao nhất (số priority nhỏ nhất) trong số các process đã đến và chưa hoàn thành
		int idx = -1; // Chỉ số process được chọn. Index = -1 nghĩa là chưa tìm thấy process nào
		int highest_priority = 9999; // Khởi tạo priority cao nhất (số nhỏ nhất)
		//BƯỚC 3: Duyệt qua tất cả process để tìm process có priority cao nhất đã đến và chưa hoàn thành
		for (int i = 0; i < n; i++) {
			// Kiểm tra process đã đến và chưa hoàn thành
			if (processes[i].ArrivalTime <= current_time && !is_completed[i]) {
				// So sánh priority (số nhỏ hơn = ưu tiên cao hơn)
				if (processes[i].Priority < highest_priority) {
					highest_priority = processes[i].Priority;
					idx = i;
				}
				// Nếu priority bằng nhau, chọn process đến trước (FCFS) (chọn AT nhỏ hơn)
				else if (processes[i].Priority == highest_priority) {
					if (processes[i].ArrivalTime < processes[idx].ArrivalTime) {
						idx = i;
					}
				}
			}
		}
		//BƯỚC 4: Kiểm tra nếu tìm thấy process để chạy. Xử lý process được chọn . Nếu không có process nào sẵn sàng, tăng thời gian hiện tại
		if (idx != -1) {
			// Tìm được process
			// Ghi nhận start time
			processes[idx].StartTime = current_time;
			// Process chạy hết burst time
			current_time += processes[idx].BurstTime;
			// Ghi nhận completion time
			processes[idx].CompletionTime = current_time;
			// Đánh dấu process đã hoàn thành
			processes[idx].IsCompleted = 1;
			is_completed[idx] = 1;
			completed++;
		}
		else {
			//CPU idle (Không có process nào sẵn sàng), tăng thời gian hiện tại
			current_time++;
		}
	}
	// BƯỚC 5: Tính metrics. Tính toán các chỉ số hiệu năng sau khi tất cả process hoàn thành 
	calculate_times(processes, n);
}
/*
 * CHI TIẾT VÍ DỤ: 
 *
 * Input:
 * P1: AT=0, BT=5, Priority=2 
 * P2: AT=1, BT=3, Priority=1
 * P3: AT=2, BT=8, Priority=3
 * P4: AT=3, BT=6, Priority=2
 *
 * VÒNG LẶP 1 (current_time=0):
 *   Tìm process:
 *     i=0: P1, AT=0<=0? YES, completed? NO
 *          Priority=2 < 9999? YES → highest=2, idx=0
 *     i=1: P2, AT=1<=0? NO (skip)
 *     i=2,3: (skip)
 *   → Chọn P1 (idx=0)
 *
 *   Thực thi:
 *     start_time[0] = 0
 *     current_time = 0 + 5 = 5
 *     completion_time[0] = 5
 *     completed = 1
 *
 * VÒNG LẶP 2 (current_time=5):
 *   Tìm process:
 *     i=0: completed (skip)
 *     i=1: P2, AT=1<=5? YES, completed? NO
 *          Priority=1 < 9999? YES → highest=1, idx=1
 *     i=2: P3, AT=2<=5? YES
 *          Priority=3 < 1? NO (skip)
 *     i=3: P4, AT=3<=5? YES
 *          Priority=2 < 1? NO (skip)
 *   → Chọn P2 (idx=1, Priority=1 cao nhất)
 *
 *   Thực thi:
 *     start_time[1] = 5
 *     current_time = 5 + 3 = 8
 *     completion_time[1] = 8
 *     completed = 2
 *
 * VÒNG LẶP 3 (current_time=8):
 *   Tìm process:
 *     i=0,1: completed (skip)
 *     i=2: P3, Priority=3, idx=2
 *     i=3: P4, Priority=2 < 3? YES → highest=2, idx=3
 *   → Chọn P4 (idx=3, Priority=2 < Priority=3)
 *
 *   Thực thi:
 *     start_time[3] = 8
 *     current_time = 8 + 6 = 14
 *     completion_time[3] = 14
 *     completed = 3
 *
 * VÒNG LẶP 4 (current_time=14):
 *   Chọn P3 (còn lại)
 *   start_time[2] = 14
 *   current_time = 14 + 8 = 22
 *   completion_time[2] = 22
 *   completed = 4
 *
 * KẾT QUẢ:
 * P1: Start=0, CT=5, TAT=5, WT=0, RT=0
 * P2: Start=5, CT=8, TAT=7, WT=4, RT=4
 * P4: Start=8, CT=14, TAT=11, WT=5, RT=5
 * P3: Start=14, CT=22, TAT=20, WT=12, RT=12
 *
 * Avg WT = (0+4+5+12)/4 = 5.25
 */