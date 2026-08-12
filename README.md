# CLI Task Manager (C Language)

A lightweight, robust command-line task management application written in C. It allows users to create, track, filter, complete, and delete tasks dynamically using structured data and clean terminal output.

## ✨ Features

- **Batch Task Creation:** Add multiple tasks with titles, priority levels (*High, Medium, Low*), and due dates.
- **Formated Table Display:** View all recorded tasks aligned cleanly using formatted field width flags (`%-25s`).
- **Filtered Views:** Instantly view pending tasks to track remaining work without clutter.
- **Task Status Management:** Search tasks by title and mark them as completed (`Done`).
- **Dynamic Deletion:** Search and delete specific tasks by shifting array elements cleanly in memory.
- **Robust Input Handling:** Features a custom input flush mechanism (`clearBuffer`) and combined `fgets`/`strcspn` parsing to prevent string truncation and buffer pollution errors.

## 🧠 Data Structure

Tasks are managed in memory using an array of structures:

```c
struct Task {
    char title[100];
    int priority;    // 1: High, 2: Medium, 3: Low
    int status;      // 0: Pending, 1: Done
    char dueDate[12];
};
