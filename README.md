# QML Desktop App Template
![Desktop Cross-Platform CI Build](https://github.com/Dingola/QMLDesktopAppTemplate/actions/workflows/builds_desktop_cross_platform.yml/badge.svg)

## [Description]
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
<br><br>

## [Table of Contents]
- [Configuration](#configuration)
  - [CMake Options](#cmake-options)
  - [Environment Variables](#environment-variables)
- [Supported Platforms](#supported-platforms)
- [How to Install and Run](#how-to-install-and-run)
  - [1) Prerequisites](#1-prerequisites)
  - [2) Setting up](#2-setting-up)
  - [3) Configuring and Building](#3-configuring-and-building)
  - [4) Run the project](#4-run-the-project)
  - [5) Deployment](#5-deployment)
- [Translations](#translations)
<br><br>

## [Configuration]

### CMake-Options
* **<PROJECT_NAME>_BUILD_TARGET_TYPE:** Specifies the type of build for the application. Possible values are:
  - `executable`
  - `dynamic_library`
  - `static_library`

* **<PROJECT_NAME>_BUILD_TEST_PROJECT:** Specifies whether the **TestProject** should also be built. Default is **Off**.

* **<PROJECT_NAME>_BUILD_DOC:** Specifies whether **documentation** should be created for the app and/or the test app. The generated documentation is located in the `doc` folder of the respective project under `Docs/Doxygen/`. The formatting specifications for the documentation can be adjusted centrally in the config file **Doxyfile.in**, which is located in the solution folder. Default is **Off**.

* **THIRD_PARTY_INCLUDE_DIR:** Specifies where the third-party libraries will be installed. The default path is:
  - **`$USERPROFILE/ThirdParty`** on Windows
  - **`$HOME/ThirdParty`** on Unix-based systems.

* **SANITIZER_TYPE:** Specifies the type of sanitizer to use for the build process. Supported values are:
  - `none`
  - `address`
  - `leak`
  - `memory`
  - `thread`
  - `address_and_leak`
  - `address_and_memory`
  - `memory_and_leak`
  - `address_memory_and_leak`
> [!NOTE]
> **Platform-specific notes:**
>  - MSVC supports: `none`, `address`
>  - UNIX supports: all of the above

---

### Environment Variables
* **QT_DIR:** Specifies the path to the Qt 6 installation.
<br><br><br>

## [Supported Platforms]
- Windows 10+
- Linux (tested on Ubuntu 24.04.1)
<br><br><br>

## [How To Install and Run]

### 1) Prerequisites
* CMake ( Minimum required version 3.19.0 ): [Download](https://cmake.org/download/ "CMake Downloads")
* A C++20 compatible compiler (e.g., GCC 10+, Clang 10+, MSVC 19.28+)
* Qt Installer (Qt 6.8): [Download](https://www.qt.io/download-qt-installer-oss)
* Optional: Doxygen (if documentation generation is enabled): [Download](https://www.doxygen.nl/download.html)
* Optional for Doxygen is LaTeX if enabled in `Doxygen.in`-File and installed.
* Optional: `zip` for creating ZIP archives (if `BUILD_ZIP_ARCHIVE` is set to `true` in `build_and_deploy.sh`)
* Optional: `NSIS` for creating installers (if `BUILD_NSIS_INSTALLER` is set to `true` in `build_and_deploy.sh`)
<br>

> [!TIP]
> The CMake GUI presents another alternative option to build the project.

> [!NOTE]
> All other dependencies are automatically installed by CMake or the respective script.

---

### 2) Setting up
```
git clone https://github.com/Dingola/QMLDesktopAppTemplate.git
cd QMLDesktopAppTemplate/
```

---

### 3) Configuring and Building
> [!IMPORTANT]
> Ensure that the `QT_DIR` environment variable is set, for example: `..\Qt\6.8.0\msvc2022_64`
```
cmake -B _build -S . -G "Visual Studio 17 2022" -A x64
cd _build
cmake --build . --config Release
```

---

### 4) Run the project
```
cd QMLDesktopAppTemplate/Release/
./QMLDesktopAppTemplate.exe
```

---

### 5) Deployment
The project includes scripts for building, testing and deploying the application. These scripts are located in the `Scripts` directory, organized by platform (e.g., `Win` for Windows, `Linux` for Linux).

- **build_release.sh:** Builds the project in release mode.
- **build_and_run_tests.sh:** Builds and runs the test project.
- **build_and_deploy.sh:** Builds and deploys the project. This script can also create a ZIP archive of the deployment directory and/or an NSIS installer using the `installer.nsi` script (Windows only).

To create a ZIP archive of the deployment directory, set `BUILD_ZIP_ARCHIVE` to `true` in `build_and_deploy.sh`.

To create an NSIS installer (Windows only), set `BUILD_NSIS_INSTALLER` to `true` in `build_and_deploy.sh`.
<br><br><br>

## [Translations]
The project includes custom targets for updating and compiling translation files. These targets are defined in the CMake file located in `QMLDesktopAppTemplate/QMLDesktopAppTemplate` and can be used to manage translation files located in the `QMLDesktopAppTemplate/QMLDesktopAppTemplate/resources/Translations` directory.

> [!NOTE]
> The translation files are specified in the CMake file. Initially, only `app_de.ts` and `app_en.ts` are included. To support additional languages, you will need to add the corresponding `.ts` files to the CMake configuration.

### Updating Translations
To update the translation files, use the following custom target:
```
_update_translations
```

---

### Compiling Translations
To compile the translation files, use the following custom target:
```
_update_translations
```
