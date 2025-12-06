/**
* @ file validation.c
* @ brief Các hàm kiểm tra và xác thực xử lý dữ liệu đầu vào.
* File này chứa các hàm để:
* - Validation: Kiểm tra tính hợp lệ của dữ liệu đầu vào.
* - Initialization: Khởi tạo các cấu trúc dữ liệu cần thiết processes
* - Reset: Reset các biến và cấu trúc dữ liệu processes về trạng thái ban đầu để chạy lại thuật toán 
* - Copy: Sao chép dữ liệu giữa các cấu trúc dữ liệu processes
* - Find: Tìm kiếm các phần tử trong cấu trúc dữ liệu processes
*/
#include "process.h"
#include "utils.h"
#include <stdio.h>
/**
* @ brief Kiểm tra tính hợp lệ của một số nguyên dương input.
* Các điều kiện kiểm tra:
* 1. Số processes phải từ 1 đến MAX_PROCESSES (1000).
* 2. PID phải là số nguyên dương > 0.
* 3. Arrival time phải >= 0.
* 4. Burst time phải > 0.
* 5. Priority phải >= 0.
* 6. Không có PID trùng lặp trong danh sách processes.
* @ param processes Mảng các cấu trúc Processes cần kiểm tra.
* @ param n Số lượng processes trong mảng.
* @ return Trả về 1 nếu tất cả các processes hợp lệ, ngược lại trả về 0.
*/
int validate_input(Process processes[], int n) {
	// Kiểm tra số lượng processes
	if (n <= 0 || n > MAX_PROCESSES) {
		printf("Lỗi: Số lượng processes phải từ 1 đến %d.\n", MAX_PROCESSES);
		return 0; // Không hợp lệ
	}
	// Kiểm tra từng process
	for (int i = 0; i < n; i++) {
		// Kiểm tra PID (phải là số nguyên dương)
		if (processes[i].ProcessId <= 0) {
			printf("Lỗi: PID của process thứ %d phải là số nguyên dương.\n", i + 1);
			return 0; // Không hợp lệ
		}
		// Kiểm tra Arrival Time (không được âm)
		if (processes[i].ArrivalTime < 0) {
			printf("Lỗi: Arrival time của process P thứ %d không được âm.\n", processes[i].ProcessId);
			return 0; // Không hợp lệ
		}
		// Kiểm tra Burst Time (phải dương > 0)
		if (processes[i].BurstTime <= 0) {
			printf("Lỗi: Burst time của process P thứ %d phải là số dương.\n", processes[i].ProcessId);
			return 0; // Không hợp lệ
		}
		// Kiểm tra Priority (Không được âm)
		if (processes[i].Priority < 0) {
			printf("Lỗi: Priority của process P thứ %d không được âm.\n", processes[i].ProcessId);
			return 0; // Không hợp lệ
		}
	}
	// Kiểm tra PID trùng lặp
	if (check_duplicate_pids(processes, n)) {
		printf("Lỗi: Có PID trùng lặp trong danh sách processes.\n");
		return 0; // Không hợp lệ
	}
	return 1; // Tất cả đều hợp lệ
}
/**
* @ brief Kiểm tra xem có PID trùng lặp trong mảng processes hay không.
* Thuật toán: So sánh từng cặp processes với nhau để tìm PID trùng lặp.
* Độ phức tạp: O(n^2)
* @ param processes Mảng các cấu trúc Processes cần kiểm tra.
* @ param n Số lượng processes trong mảng.
* @ return Trả về 1 nếu có PID trùng lặp, 0 nếu không trùng lặp.
*/
int check_duplicate_pids(Process processes[], int n) {
	// Vòng lặp ngoài: duyệt từng process để chọn process i làm chuẩn so sánh
	for (int i = 0; i < n - 1; i++) {
		// Vòng lặp trong: so sánh process i với các process j phía sau nó
		for (int j = i + 1; j < n; j++) {
			// Nếu PID của hai process trùng/giống nhau, trả về 1 (có trùng lặp)
			if (processes[i].ProcessId == processes[j].ProcessId) {
				printf("Lỗi: PID trùng lặp %d giữa process thứ %d và process thứ %d.\n", processes[i].ProcessId);
				return 1; // Có PID trùng lặp
			}
		}
	}
	return 0; // Không có PID trùng
}
/**
* @ brief Kiểm tra time quantum hợp lệ cho thuật toán Round Robin.
* @ param time_quantum Giá trị time quantum cần kiểm tra.
* @ return 1 nếu hợp lệ, 0 nếu không hợp lệ.
* Lưu ý:
* - Time quantum TQ <= 0 là không hợp lệ.
* - Time quantum TQ = 1 là hợp lệ nhưng không hiệu quả. Cảnh báo ( context switching cao)
* - Time quantum TQ > 100: 0 là hợp lệ nhưng không hiệu quả. Cảnh báo (giống FCFS).
*/
int validate_time_quantum(int time_quantum) {
	// TQ phải dương
	if (time_quantum <= 0) {
		printf("Lỗi: Time quantum phải là số dương lớn hơn 0.\n");
		return 0; // Không hợp lệ
	}
	// Cảnh báo nếu TQ quá lớn
	if (time_quantum > 100) {
		printf("Cảnh báo: Time quantum lớn hơn 100 có thể làm giảm hiệu quả của thuật toán Round Robin.\n");
		printf("Điều này có thể gây cho Thuật toán Round Robin gần giống FCFS\n");
	}
	// Cảnh báo nếu TQ = 1
	if (time_quantum == 1) {
		printf("Cảnh báo: Time quantum = 1 có thể gây ra chi phí chuyển đổi ngữ cảnh cao");

	}
	return 1; // Hơp lệ 
}
/**
* @brief Sao chép mảng processes từ source sang destination.
* Dùng khi cần giữ nguyên mảng gốc và chạy thuật toán trên bản copy
* @param dest Mảng đích (destination)
* @param src Mảng nguồn (source)
* @param n Số lượng processes
* Ví dụ:
* Process original[5]; // Mảng gốc
* Process copy[5]; // Mảng copy
* copy_processes(copy, original, 5); // Copy từ original sang copy
* fcfs(copy, 5); //Chạy thuật toán trên copy, original không đổi
*/
void copy_processes(Process dest[], Process src[], int n) {
	for (int i = 0; i < n; i++) {
		dest[i] = src[i]; //Copy từng process

	}
}
/**
* @brief Khởi tạo một process với các giá trị mặc định.
* @param p Con trỏ đến process cần khởi tạo.
* Các giá trị được khởi tạo:
* - remaining_time = burst_time (ban đầu chưa chạy)
* - start_time = -1 (chưa có thời gian bắt đầu)
* - is_completed = 0 (chưa hoàn thành)
* - Các metrics = 0
*/
void init_process(Process* p) {
	p->RemainingTime = p->BurstTime; // Thời gian còn lại ban đầu bằng burst time (Thời gian còn lại = thời gian cần chạy)
	p->StartTime = -1; // -1 nghĩa là chưa bắt đầu chạy
	p->IsCompleted = 0; // 0 = chưa hoàn thành, 1 = đã hoàn thành
	p->CompletionTime = 0;
	p->WaitingTime = 0;
	p->TurnaroundTime = 0;
	p->ResponseTime = 0;
}

/**
* @ brief Khởi tạo mảng processes.
* @param processes Mảng processes.
* @param n Số lượng processes trong mảng.
*/
void init_processes(Process processes[], int n) {
	for (int i = 0; i < n; i++) {
		init_process(&processes[i]); // Gọi hàm khởi tạo cho từng process. & là lấy địa chỉ của phần tử processes[i]
	}
}
/**
* @brief Reset một process để chạy lại thuật toán từ đầu.
* Giữ nguyên: PID, arrival_time, burst_time, priority
* Reset các giá trị thay đổi trong quá trình chạy thuật toán.
* Reset: remaining_time, start_time, completion_time, is_completed, các metrics
* @param p Con trỏ đến process cần reset.
*/
void reset_process(Process* p) {
	// *p là dereference con trỏ p để truy cập vào cấu trúc Process mà p trỏ tới
	p->RemainingTime = p->BurstTime; // Reset thời gian còn lại về burst_time (Chưa chạy)
	p->StartTime = -1; // Chưa bắt đầu chạy
	p->IsCompleted = 0; // Chưa hoàn thành
	p->CompletionTime = 0; // Reset completion time
	p->WaitingTime = 0; // Reset waiting time
	p->TurnaroundTime = 0; // Reset turnaround time
	p->ResponseTime = 0; // Reset response time
}
/**
* @brief Reset mảng processes để chạy lại thuật toán từ đầu.
*/
void reset_processes(Process processes[], int n) {
	for (int i = 0; i < n; i++) {
		reset_process(&processes[i]); // Gọi hàm reset cho từng process
	}
}
/**
* @brief Tìm chỉ số của process theo PID.
* @param processes Mảng các processes.
* @param n Số lượng processes trong mảng.
* @param pid PID cần tìm.
* @return Chỉ số index của process có PID tương ứng, hoặc -1 nếu không tìm thấy.
* Ví dụ:
* int idx = find_process_by_pid(processes, 5, 3); // Tìm process có PID = 3
* if (idx != -1) {
* //Tìm thấy process, xử lý tiếp
* printf("Found P%d at index %d\n", processes[idx].pid, idx);
* }
*/
int find_process_by_pid(Process processes[], int n, int pid) {
	for (int i = 0; i < n; i++) {
		if (processes[i].ProcessId == pid) {
			return i; // Trả về chỉ số index nếu tìm thấy PID
		}
	}
	return -1; // Trả về -1 nếu không tìm thấy
}
/**
* @brief Tìm giá trị nhỏ hơn của 2 số nguyên.
* @param a Số nguyên thứ nhất.
* @param b Số thứ 2.
* @return Số nhỏ hơn trong 2 số a và b.
* Ví dụ: min(5, 3) = 3
*/
int min(int a, int b) {
	return (a < b) ? a : b; //Nếu a<b thì trả về a, ngược lại trả về b
	// Giải thích: (a < b) ? a : b là toán tử điều kiện (ternary operator)
	// Nếu a < b -> true --> trả về a
	// Ngược lại -> trả về b
}
/**
* @brief Tìm giá trị lớn hơn của 2 số nguyên.
* @param a Số nguyên thứ nhất.
* @param b Số thứ hai.
* @return Số lớn hơn.
* Ví dụ: max (5,3) = 5
*/
int max(int a, int b) {
	return (a > b) ? a : b; //Nếu a>b thì trả về a, ngược lại trả về b
	// Giải thích: (a > b) ? a : b là toán tử điều kiện (ternary operator)
	// Nếu a > b -> true --> trả về a
	// Ngược lại -> trả về b
}