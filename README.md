# CLI-Task-Manager

## 1 Main Information

### 1.1 Project name

**CLI Task Manager**

### 1.2 Purpose

A console application for managing a task list needs to be developed.

The application must allow the user to:

- create tasks;
- view issues;
- change tasks;
- delete tasks;
- change the status of tasks;
- assign priority;
- set a deadline;
- add tags;
- search and filter issues;
- sort tasks;
- view statistics;
- save data between app launches.

All interaction with the application takes place through the CLI.

## 2 Build

### 2.1 IDE

To run via IDE you should specify builds directory. For debug version:

```
./Builds/cmake-build-debug
```

For release version:

```
./Builds/cmake-build-release
```

### 2.2 Linux build

In repo root:

```
mkdir Builds
```

Building a project:

- For debug version:

    ```
    cmake -G "Unix Makefiles" -S . -B ./Builds/cmake-build-debug
    ```

- For release version:

    ```
    cmake -G "Unix Makefiles" -S . -B ./Builds/cmake-build-release
    ```

Compile:

```
cmake --build ./Builds/cmake-build-xxxx -- -j
```

where "xxxx" - build type

Run:

```
./Builds/cmake-build-xxxx/Source/CLI-Task-Manager
```

### 2.3 Windows build

TODO may be in future

## 3 Additional Info

### 3.1 Tech stack

- C++ 20
- Git
- CMake

### 3.2 Git info

Commit message - "[DP-S-001]", where:

- DP - Standard commit message abbreviation
- S - Study project suffix
- 001 - Commit message version