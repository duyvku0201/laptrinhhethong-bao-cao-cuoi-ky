/**
* @ file sort.c
* @ brief Các hàm sắp xếp processes
* File này chứa các hàm để sắp xếp mảng processes theo các tiêu chí khác nhau:
* - Sắp xếp theo thời gian đến (ArrivalTime)
* - Sắp xếp theo thời gian thực thi (BurstTime)
* - Sắp xếp theo thời gian hoàn thành (CompletionTime)
* - Sắp xếp theo độ ưu tiên (Priority)
* - Sắp xếp theo PID (ProcessId)
*/
#include "process.h"
#include "utils.h"
#include <stdio.h>
/**
* @ brief Hàm sắp xếp mảng processes theo thời gian đến tăng dần (arrival time)
* Thuật toán: Bubble Sort
* Độ phức tạp: O(n^2)
* @param processes Mảng các process cần sắp xếp
* @param n Số lượng process trong mảng
* @return không trả về giá trị 
* Ví dụ:
* Input: P1(AT=3), P2(AT=1), P3(AT=2)
* Output: P2(AT=1), P3(AT=2), P1(AT=3)
*/
void sort_by_arrival(Process processes[], int n) {
	// Vòng lặp ngoài: chạy từ 0 đến n-1
	for (int i = 0; i < n - 1; i++) {
		// Vòng lặp trong: so sánh và đẩy phần tử lớn nhất về cuối
		// Mỗi lần lặp, phần tử lớn nhất "nổi" lên cuối mảng chưa sắp xếp
		for (int j = 0; j < n - i - 1; j++) {
			// So sánh arrival_time của 2 processes liền kề
			if (processes[j].ArrivalTime > processes[j + 1].ArrivalTime) {
				// Hoán đổi nếu không đúng thứ tự ( Nếu process j đến sau process j+1 -> Swap
				Process temp = processes[j]; // Lưu process j vào biến tạm
				processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
				processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1


			}
		}
	}
}
/**
 *@brief Sắp xếp processes theo burst time (tăng dần)
 * Dùng cho thuật toán SJF (Shortest Job First)
 * Nếu burst time bằng nhau → sắp xếp theo arrival time (FCFS)
 * @param processes Mảng processes
 * @param n Số lượng processes
 * Ví dụ:
 * Input:  P1(BT=5, AT=0), P2(BT=3, AT=1), P3(BT=3, AT=2)
 * Output: P2(BT=3, AT=1), P3(BT=3, AT=2), P1(BT=5, AT=0)
 *         P2 trước P3 vì AT nhỏ hơn (cùng BT=3)
*/
void sort_by_burst(Process processes[], int n) {
	  // Vòng lặp ngoài: chạy từ 0 đến n-1
	for (int i = 0; i < n - 1; i++) {
		//Vòng lặp trong: so sánh và đẩy phần tử lớn nhất về cuối
		for (int j = 0; j < n - i - 1; j++) {
			// Điều kiện 1: So sánh burst_time của 2 processes liền kề
			if (processes[j].BurstTime > processes[j + 1].BurstTime) {
				// Hoán đổi nếu không đúng thứ tự. Process j có burst_time lớn hơn process j+1 -> Swap
				Process temp = processes[j]; // Lưu process j vào biến tạm
				processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
				processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1

			}

			// Điều kiện 2: Nếu burst_time bằng nhau, so sánh arrival_time
			else if (processes[j].BurstTime == processes[j + 1].BurstTime) {
				// Sắp xếp theo arrival_time (FCFS - First Come First Serve)
				if (processes[j].ArrivalTime > processes[j + 1].ArrivalTime) {
					Process temp = processes[j]; //Lưu process j vào biến tạm
					processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
					processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1

				}
			}
		}
	  }
}
/**
* @ brief Hàm sắp xếp mảng processes theo priority (tăng dần)
* Lưu ý: Priority số nhỏ hơn có độ ưu tiên cao hơn
* Priority 1 > Priority 2 > Priority 3
* Nếu priority bằng nhau -> dùng arrival time để sắp xếp (FCFS)
* @param processes Mảng các processes cần sắp xếp
* @param n Số lượng processes trong mảng
* Ví dụ:
* Input: P1(Pri=2), P2(Pri=1), P3(Pri=3)
* Output: P2(Pri=1), P1(Pri=2), P3(Pri=3)
*/
void sort_by_priority(Process processes[], int n) {
	// Vòng lặp ngoài: chạy từ 0 đến n-1
	for (int i = 0; i < n - 1; i++) {
		//Vòng lặp trong: so sánh và đẩy phần tử lớn nhất về cuối
		for (int j = 0; j < n - i - 1; j++) {
			// So sánh priority (số nhỏ = ưu tiên cao)
			if (processes[j].Priority > processes[j + 1].Priority) {
				// Hoán đổi nếu không đúng thứ tự. Process j có priority lớn hơn process j+1 -> Swap
				Process temp = processes[j]; //Lưu process j vào biến tạm
				processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
				processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1
			}
			// Nếu priority bằng nhau, sắp xếp theo arrival_time (FCFS)
			else if (processes[j].Priority == processes[j + 1].Priority) {
				if (processes[j].ArrivalTime > processes[j + 1].ArrivalTime) {
					Process temp = processes[j]; //Lưu process j vào biến tạm
					processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
					processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1
				}
			}
		}
	}
}
/**
* @brief Hàm sắp xếp mảng processes theo Completion time (tăng dần)
* Dùng để hiển thị processes theo thứ tự hoàn thành
* * @param processes Mảng các processes cần sắp xếp
* @param n Số lượng processes trong mảng
*/
void sort_by_completion(Process processes[], int n) {
	// Vòng lặp ngoài: chạy từ 0 đến n-1
	for (int i = 0; i < n - 1; i++) {
		//Vòng lặp trong: so sánh và đẩy phần tử lớn nhất về cuối
		//So sánh completion time của 2 processes liền kề 
		for (int j = 0; j < n - i - 1; j++) {
			if (processes[j].CompletionTime > processes[j + 1].CompletionTime) {
				// Hoán đổi nếu không đúng thứ tự. Process j có completion_time lớn hơn process j+1 -> Swap
				Process temp = processes[j]; //Lưu process j vào biến tạm
				processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
				processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1
			}
		}
	}
}
/**
* @ brief Hàm sắp xếp mảng processes theo PID (tăng dần)
* * Dùng để trả lại thứ tự ban đầu của các processes
* @ param processes Mảng các processes cần sắp xếp
* @ param n Số lượng processes trong mảng
* Ví dụ:
* Input: P3,P1,P2
* Output: P1,P2,P3
*/
void sort_by_pid(Process processes[], int n) {
	//Vòng lặp ngoài: chạy từ 0 đến n-1
	for (int i = 0; i < n - 1; i++) {
		//Vòng lặp trong: so sánh và đẩy phần tử lớn nhất về cuối
		for (int j = 0; j < n - i - 1; j++) {
		 // So sánh PID của 2 processes liền kề
			if (processes[j].ProcessId > processes[j + 1].ProcessId) {
				// Hoán đổi nếu không đúng thứ tự ( Process j có PID lớn hơn process j+1 -> Swap)
				Process temp = processes[j]; //Lưu process j vào biến tạm
				processes[j] = processes[j + 1]; // Gán process j+1 vào vị trí j
				processes[j + 1] = temp; // Gán biến tạm (process j) (đã lưu) vào vị trí j+1

			}
		}
	}
}
/**
* @ brief Hoán đổi 2 processes trong mảng
* 
* @param p1 Con trỏ đến process thứ nhất
* @param p2 Con trỏ đến process thứ hai
* Cách hoạt động:
* 1. Lưu giá trị *p1 vào biến tạm temp
* 2. Gán giá trị *p2 vào *p1
* 3. Gán giá trị temp (giá trị cũ của *p1) vào *p2
*/
void swap_processes(Process* p1, Process* p2) {
	Process temp = *p1; // Lưu giá trị của process 1 vào biến tạm
	*p1 = *p2;         // Gán giá trị của process 2 cho process 1
	*p2 = temp;       // Gán giá trị tạm (giá trị cũ của process 1) cho process 2
}
