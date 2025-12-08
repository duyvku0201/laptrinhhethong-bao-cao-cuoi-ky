# Hướng Dẫn Build Dự Án CPU Scheduling Simulator

## Giới Thiệu
Dự án này sử dụng **CMake** để tạo build system đa nền tảng, hỗ trợ:
- ✅ **Windows** (Visual Studio, MinGW, MSYS2)
- ✅ **Ubuntu/Linux** (GCC, Clang)
- ✅ **NetBSD** (GCC)

---

## Yêu Cầu Hệ Thống

### Chung cho tất cả hệ điều hành:
- **CMake** phiên bản 3.10 trở lên
- **C Compiler** hỗ trợ C99

### Windows:
- **Option 1:** Visual Studio 2017 trở lên (Community Edition miễn phí)
- **Option 2:** MinGW-w64 hoặc MSYS2 với GCC
- **CMake:** Download từ https://cmake.org/download/

### Ubuntu/Linux:
```bash
sudo apt update
sudo apt install build-essential cmake
```

### NetBSD:
```bash
pkgin update
pkgin install cmake gcc
```

---

## Hướng Dẫn Build

### 1️⃣ **Ubuntu/Linux**

#### Bước 1: Cài đặt dependencies
```bash
sudo apt update
sudo apt install build-essential cmake git
```

#### Bước 2: Clone và build
```bash
# Di chuyển vào thư mục dự án
cd /path/to/laptrinhhethong-bao-cao-cuoi-ky

# Tạo thư mục build
mkdir build
cd build

# Generate Makefile bằng CMake
cmake ..

# Build dự án
make

# Hoặc build với nhiều threads (nhanh hơn)
make -j$(nproc)
```

#### Bước 3: Chạy chương trình
```bash
# Từ thư mục build
./scheduler

# Hoặc từ thư mục gốc
./build/scheduler
```

#### Build với Debug mode:
```bash
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

#### Build với Release mode (tối ưu hóa):
```bash
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

---

### 2️⃣ **Windows**

#### **Option A: Visual Studio (Recommended)**

##### Bước 1: Cài đặt
1. Cài đặt **Visual Studio 2019/2022** (Community Edition)
   - Chọn "Desktop development with C++"
2. Cài đặt **CMake**:
   - Download từ: https://cmake.org/download/
   - Hoặc cài qua Visual Studio Installer

##### Bước 2: Build qua Visual Studio
```powershell
# Mở PowerShell hoặc Command Prompt
cd C:\path\to\laptrinhhethong-bao-cao-cuoi-ky

# Tạo thư mục build
mkdir build
cd build

# Generate Visual Studio project
cmake .. -G "Visual Studio 17 2022"
# Hoặc Visual Studio 16 2019:
# cmake .. -G "Visual Studio 16 2019"

# Build
cmake --build . --config Release
```

##### Bước 3: Chạy
```powershell
# Từ thư mục build
.\Release\scheduler.exe

# Hoặc
.\Debug\scheduler.exe
```

#### **Option B: MinGW / MSYS2**

##### Bước 1: Cài đặt MSYS2
1. Download MSYS2: https://www.msys2.org/
2. Cài đặt packages:
```bash
# Mở MSYS2 terminal
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make
```

##### Bước 2: Build
```bash
cd /c/path/to/laptrinhhethong-bao-cao-cuoi-ky

mkdir build
cd build

# Generate Makefile
cmake .. -G "MinGW Makefiles"

# Build
mingw32-make
# Hoặc
make
```

##### Bước 3: Chạy
```bash
./scheduler.exe
```

#### **Option C: CMake GUI (Windows)**

1. Mở **CMake GUI**
2. **Where is the source code:** Chọn thư mục dự án
3. **Where to build the binaries:** Chọn thư mục `build`
4. Click **Configure** → Chọn compiler (Visual Studio hoặc MinGW)
5. Click **Generate**
6. Click **Open Project** (nếu dùng Visual Studio) hoặc build bằng command line

---

### 3️⃣ **NetBSD**

#### Bước 1: Cài đặt dependencies
```bash
# Với quyền root hoặc sudo
pkgin update
pkgin install cmake gcc gmake git
```

#### Bước 2: Build
```bash
cd /path/to/laptrinhhethong-bao-cao-cuoi-ky

mkdir build
cd build

# Generate Makefile
cmake ..

# Build với gmake (GNU Make)
gmake

# Hoặc với make truyền thống
make
```

#### Bước 3: Chạy
```bash
./scheduler
```

---

## Các Lệnh CMake Hữu Ích

### Clean build
```bash
# Xóa thư mục build và build lại
rm -rf build
mkdir build
cd build
cmake ..
make
```

### Build với verbose output
```bash
make VERBOSE=1
# Hoặc
cmake --build . --verbose
```

### Chỉ build (không link)
```bash
make scheduler.o
```

### Clean objects
```bash
make clean
```

### Xem các targets có sẵn
```bash
make help
```

### Install (optional)
```bash
# Install vào hệ thống (cần quyền root/admin)
sudo make install
# Mặc định: /usr/local/bin/scheduler
```

---

## Cấu Trúc Thư Mục Sau Khi Build

```
laptrinhhethong-bao-cao-cuoi-ky/
├── build/                          # Thư mục build
│   ├── scheduler                   # Executable (Linux/NetBSD)
│   ├── scheduler.exe               # Executable (Windows MinGW)
│   ├── Release/scheduler.exe       # Executable (Windows Visual Studio)
│   ├── CMakeFiles/                 # CMake metadata
│   ├── CMakeCache.txt             # CMake cache
│   └── Makefile                    # Generated Makefile
├── CMakeLists.txt                  # CMake configuration
├── src/                            # Source code
├── include/                        # Header files
└── ...
```

---

## Troubleshooting

### Lỗi: CMake không tìm thấy compiler

**Ubuntu/Linux:**
```bash
sudo apt install build-essential
export CC=gcc
export CXX=g++
cmake ..
```

**Windows:**
```powershell
# Đảm bảo Visual Studio hoặc MinGW đã được cài đặt
# Thêm vào PATH nếu cần
```

**NetBSD:**
```bash
export CC=/usr/pkg/bin/gcc
export CXX=/usr/pkg/bin/g++
cmake ..
```

### Lỗi: Permission denied khi chạy

**Linux/NetBSD:**
```bash
chmod +x ./scheduler
./scheduler
```

### Lỗi: Missing libraries

**Tất cả hệ điều hành:**
- Dự án này chỉ sử dụng standard C library, không cần thêm dependencies
- Kiểm tra lại CMake version: `cmake --version`

### Build lại từ đầu
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

---

## So Sánh với Makefile Truyền Thống

| Tính năng | Makefile | CMake |
|-----------|----------|-------|
| Đa nền tảng | ❌ Cần viết riêng | ✅ Tự động |
| IDE Support | ❌ Limited | ✅ Visual Studio, CLion, etc. |
| Dependency tracking | ⚠️ Manual | ✅ Automatic |
| Cross-compilation | ❌ Complex | ✅ Built-in |
| Out-of-source build | ⚠️ Manual | ✅ Default |

---

## Các Tùy Chọn CMake Nâng Cao

### Build type
```bash
# Debug (with symbols)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Release with debug info
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
```

### Chỉ định compiler
```bash
# GCC
cmake -DCMAKE_C_COMPILER=gcc ..

# Clang
cmake -DCMAKE_C_COMPILER=clang ..

# Visual Studio 2022
cmake -G "Visual Studio 17 2022" ..
```

### Install prefix
```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make install
```

---

## Chạy Chương Trình

### Với file input
```bash
./scheduler
# Chọn option 1 (Read from file)
# Nhập: samples/sample_input.txt
```

### Test nhanh
```bash
echo "1
samples/sample_input.txt
1
8" | ./scheduler
```

---

## Liên Hệ & Support

- **Repository:** https://github.com/duyvku0201/laptrinhhethong-bao-cao-cuoi-ky
- **Issues:** Tạo issue trên GitHub nếu gặp vấn đề

---

## Ghi Chú Quan Trọng

1. ✅ **CMakeLists.txt** đã được tối ưu cho C99 standard
2. ✅ Hỗ trợ **out-of-source builds** (build riêng biệt khỏi source)
3. ✅ Tự động detect platform và compiler
4. ✅ Tương thích với cả **Makefile cũ** (có thể dùng song song)
5. ✅ ANSI colors hoạt động tốt trên tất cả platform

---

**Chúc bạn build thành công! 🚀**
