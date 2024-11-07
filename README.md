# QML Desktop App Template

## Description
This project is a template for creating QML-based desktop applications. The solution 
is divided into two parts: the main project and a test project. By default, only the 
main project is built. The test project can be built if desired, controlled by a CMake 
boolean variable `<PROJECT_NAME>_BUILD_TEST_PROJECT`. Additionally, the CMake variable 
`<PROJECT_NAME>_BUILD_TARGET_TYPE` must be set to `static_library` for the test project 
to be executed.

The template includes various classes, models, and services to load and display settings 
or translations. Additionally, it is possible to generate documentation for the project 
using Doxygen. The template also includes GitHub workflows (CI builds) for both Linux 
and Windows.
***

## Table of Contents
- [Configuration](#configuration)
- [Supported Platforms](#supported-platforms)
- [How to Install and Run](#how-to-install-and-run)
***

## Configuration

### - CMake-Options
* **<PROJECT_NAME>_BUILD_TARGET_TYPE:** Specifies the type of build for the application. Possible values are:
  - `executable`
  - `dynamic_library`
  - `static_library`

* **<PROJECT_NAME>_BUILD_TEST_PROJECT:** Specifies whether the **TestProject** should also be built. Default is **Off**.

* **<PROJECT_NAME>_BUILD_DOC:** Specifies whether **documentation** should be created for the app and/or the test app. The generated documentation is located in the `doc` folder of the respective project under `Docs/Doxygen/`. The formatting specifications for the documentation can be adjusted centrally in the config file **Doxyfile.in**, which is located in the solution folder. Default is **Off**.

* **THIRD_PARTY_INCLUDE_DIR:** Specifies where the third-party libraries will be installed. The default path is:
  - **`$USERPROFILE/ThirdParty`** on Windows
  - **`$HOME/ThirdParty`** on Unix-based systems.

### - Environment Variables
* **QT6_PATH:** Specifies the path to the Qt 6 installation.
***

## Supported Platforms
- Windows 10+
- Linux (tested on Ubuntu 24.04.1)
***

## How To Install and Run

### - Prerequisites
* CMake ( Minimum required version 3.19.0 ): [Download](https://cmake.org/download/ "CMake Downloads")
* A C++20 compatible compiler (e.g., GCC 10+, Clang 10+, MSVC 19.28+)
* Qt Installer (Qt 6.8): [Download](https://www.qt.io/download-qt-installer-oss)
* Doxygen: [Download](https://www.doxygen.nl/download.html)
* Optional for Doxygen is LaTeX if enabled in `Doxygen.in`-File and installed.
> All other dependencies are automatically installed by CMake.

### - Setting up
```
git clone https://github.com/Dingola/QMLDesktopAppTemplate.git
cd QMLDesktopAppTemplate/
```

### - Environment Variables

Ensure that the `QT6_PATH` environment variable is set, for example: `..\Qt\6.8.0\msvc2022_64`

### - Configuring and Building
```
cmake -B _build -S . -G "Visual Studio 17 2022" -A x64
cd _build
cmake --build . --config Release
```

### - Run the project
```
cd QMLDesktopAppTemplate/Release/
./QMLDesktopAppTemplate.exe
```

> The CMake GUI presents another alternative option to build the project.
