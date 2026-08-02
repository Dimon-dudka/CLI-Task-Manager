# CLI-Task-Manager

## 1. Main Information

### 1.1 Project name

**CLI Task Manager**

### 1.2 Purpose

A console application for managing a task list needs to be developed.

The application must allow the user to:

* create tasks;
* view tasks;
* edit tasks;
* delete tasks;
* change task status;
* assign priority;
* set a deadline;
* add tags;
* search and filter tasks;
* sort tasks;
* view statistics;
* save data between application launches.

All interaction with the application takes place through the CLI.

## 2. Build

### 2.1 IDE

All project dependencies are installed using Conan.

Initialize the Conan profile:

```bash
mkdir -p ./Builds/conan
conan profile detect --force
```

Install dependencies for the required build type:

```bash
conan install . \
    --output-folder="./Builds/conan" \
    --build=missing \
    -s build_type=<BUILD_TYPE>
```

where `<BUILD_TYPE>` is one of:

* `Debug`
* `Release`

The corresponding Conan generator directory will be:

```text
./Builds/conan/build/<BUILD_TYPE>/generators/
```

When configuring the project in an IDE, use the appropriate build directory:

```text
./Builds/cmake-build-debug
./Builds/cmake-build-release
```

### 2.2 Linux build

From the repository root, create the build directory:

```bash
mkdir -p Builds
```

Run the setup script with the required build type:

```bash
./Tools/Scripts/Linux_Setup.sh <BUILD_TYPE>
```

where:

* `d` — Debug
* `r` — Release

The setup script installs the Conan dependencies for the selected configuration.

Configure the project with CMake:

```bash
cmake -G "Unix Makefiles" \
    -S . \
    -B ./Builds/cmake-build-<BUILD_TYPE> \
    -DCMAKE_TOOLCHAIN_FILE=./Builds/conan/build/<ConanBuildType>/generators/conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=<CMakeBuildType>
```

Build type mapping:

| Configuration | Script argument | CMake build type | Conan build type | Build directory              |
|---------------|-----------------|------------------|------------------|------------------------------|
| Debug         | `d`             | `Debug`          | `Debug`          | `Builds/cmake-build-debug`   |
| Release       | `r`             | `Release`        | `Release`        | `Builds/cmake-build-release` |

Compile the project:

```bash
cmake --build ./Builds/cmake-build-<BUILD_TYPE> -- -j
```

Run the application:

```bash
./Builds/cmake-build-<BUILD_TYPE>/Source/CLI-Task-Manager
```

### 2.3 Windows build

TODO: may be added in the future.

## 3. Additional Info

### 3.1 Tech stack

* C++ 20
* Git
* CMake
* Conan
* Python
* GTest

### 3.2 Git info

Commit message format:

```text
[DP-S*-xxxx]
```

where:

* `DP` — standard commit message abbreviation;
* `S` — study project suffix;
* `*` - project number;
* `xxxx` — commit message version.

