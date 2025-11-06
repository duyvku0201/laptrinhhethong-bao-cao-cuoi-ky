#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

/**
 * Thuật toán lập lịch FCFS (First Come First Serve) - Đến trước phục vụ trước
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * Giải thích: Tiến trình nào đến trước (Arrival Time nhỏ hơn) thì được CPU xử lý trước, không có sự ngắt giữa chừng.
 */
void fcfs(Process processes[], int n);
/**
 * Thuật toán lập lịch SJF không ưu tiên (Non-preemptive Shortest Job First)
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * Giải thích: Trong các tiến trình đang chờ, tiến trình có thời gian chạy ngắn nhất (Burst Time nhỏ nhất) sẽ được chọn chạy trước. Không có ngắt giữa chừng.
 */
void sjf(Process processes[], int n);
/**
 * Thuật toán lập lịch SRTF (Shortest Remaining Time First)- phiên bản có ưu tiên ngắt của SJF
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * Giải thích: Tại mỗi thời điểm, CPU sẽ chọn tiến trình có thời gian còn lại nhỏ nhất để chạy. Nếu có tiến trình mới đến với thời gian nhỏ hơn, tiến trình đang chạy sẽ bị ngắt.
 */
void srtf(Process processes[], int n);
/**
 * Thuật toán lập lịch Priority không ưu tiên (Non-preemptive Priority)
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * Giải thích: Trong các tiến trình đang chờ, tiến trình nào có độ ưu tiên cao hơn (tùy theo quy tắc: số nhỏ hơn hoặc lớn hơn là ưu tiên) sẽ được xử lý trước. Không có ngắt giữa chừng.
 */
void priority_non_preemptive(Process processes[], int n);
/**
 * Thuật toán lập lịch Priority có ưu tiên (Preemptive Priority)
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * Giải thích: CPU luôn chọn tiến trình có độ ưu tiên cao nhất để chạy. Nếu có tiến trình mới đến với độ ưu tiên cao hơn, tiến trình đang chạy sẽ bị ngắt.
 */
void priority_preemptive(Process processes[], int n);
/**
 * Thuật toán lập lịch Round Robin (RR)
 * @param processes Mảng chứa danh sách các tiến trình
 * @param n Số lượng tiến trình
 * @param time_quantum Khoảng thời gian CPU cấp cho mỗi tiến trình trong 1 lượt (Time Quantum)
 * Giải thích: Mỗi tiến trình được cấp CPU trong một khoảng thời gian cố định (time quantum). Nếu chưa chạy xong sau khi hết quantum, tiến trình bị đưa về cuối hàng đợi để đợi lượt tiếp theo. Đây là thuật toán công bằng, thường dùng trong hệ điều hành đa nhiệm.
 */
void round_robin(Process processes[], int n, int time_quantum);

#endif // ALGORITHMS_H
