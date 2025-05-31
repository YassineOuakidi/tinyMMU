# 🧠 Two-Level Paging Simulator with Bitmap-based Physical Memory Manager

This project simulates a simplified two-level paging system along with a bitmap-based physical memory manager in C. It is intended for educational purposes to understand how virtual memory translation and memory allocation work in modern operating systems.

---

## 🗂️ Project Structure

```
.
├── inc
│   ├── bitmap.h
│   └── mapping.h
├── Makefile
├── src
│   ├── bitmap.c
│   ├── bitmap_pmm.c
│   ├── frame_allocator.c
│   ├── map.c
│   ├── translate.c
│   └── unmap.c
├── test
│   ├── main.c
│   └── main.o
```


---

## 🛠️ Features

- ✅ Two-level paging simulation (Page Directory + Page Table)
- ✅ Virtual to physical address translation
- ✅ Bitmap-based physical frame allocation and deallocation
- ✅ Page mapping, unmapping, and remapping
- ✅ Detection of unmapped address translations
- ✅ Full test suite with coverage for:
  - Mapping and translating addresses
  - Frame exhaustion and reuse
  - Unmapping and remapping behavior

---

## 🧮 Address Breakdown (16-bit Virtual Address)

- **Bits 15–13**: Page Directory Index (PDI)
- **Bits 12–10**: Page Table Index (PTI)
- **Bits 9–0**: Page Offset (PO)

Each page is 1KB in size.

---

## 🚀 Getting Started

### ✅ Prerequisites

- GCC or any standard C compiler
- Make

### 🧪 Run the Simulation

```bash
make
./test_paging
```

## 🧪 Sample Output

```text
translate(0x0000) -> 0x0000  
translate(0x1ABC) -> 0x0EBC  
translate(0x7FFF) -> ERROR: unmapped  
```

## 📚 Learning Objectives

This project is ideal for understanding:

- 🧩 Memory abstraction via paging
- 🛠️ Low-level memory address manipulation
- 🧮 Efficient memory tracking using bitmaps
- 🖥️ OS-level resource management principles

## 💡 Future Work

- 🔐 Add support for page protection flags (read-only, read-write)
- ⚡ Simulate TLB caching
- 🚨 Introduce page fault handler
- 🧵 Support multiple page directories (multi-process simulation)

## 🧑‍💻 Author

Yassine Ouakidi  
Low-level systems enthusiast.  
[GitHub](https://github.com/YassineOuakidi)

