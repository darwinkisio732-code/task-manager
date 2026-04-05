```markdown
# Task Manager

A terminal-based task manager to track tasks by priority and status.

## Features

- Add multiple tasks at once
- View all tasks with priority and status labels
- View pending tasks only
- Mark tasks as done
- Delete tasks by title
- Maximum 100 tasks

## How to Compile and Run

```bash
gcc task_manager.c -o task_manager
./task_manager
```

## Menu Options

1. **ADD TASK** – Add one or more tasks
2. **VIEW ALL** – Display all tasks
3. **VIEW PENDING** – Show only pending tasks
4. **MARK DONE** – Mark a task as completed by title
5. **DELETE** – Delete a task by title
6. **EXIT** – Close the program

## Example

```
Title: Finish C pointers
Priority: 1 (High)
Due Date: 15/04/2026

===============AVAILABLE TASKS===============
Title                Priority   Status     Due Date
-----------------------------------------------------
Finish C pointers    High       Pending    15/04/2026
```

## Requirements

- GCC compiler
- Windows / Linux / macOS
```
