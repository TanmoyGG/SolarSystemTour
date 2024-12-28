# Solar System Tour

## Overview
This project is a C++ project called SolarSystemTour. It uses OpenGL, GLUT, GLU, GLEW, and glm libraries. This guide will help you set up the development environment on macOS, Windows, and Linux using CLion, Xcode, Visual Studio, and VSCode.
 
---

## Prerequisites
- **CMake 3.16 or higher** - [CMake Releases](https://cmake.org/download/) 🛠️
- **vcpkg** (for managing dependencies) 📦
- **Git** - [Git Downloads](https://git-scm.com/downloads) 🧰
- **Compilers**
   - MinGW or MSVC (Windows) 🖥️
   - GCC (Linux) 🐧
   - Clang (macOS) 🍎
   - [Setup Guide](https://code.visualstudio.com/docs/languages/cpp#_set-up-your-c-environment)
- **Ninja Build tools** (for VSCode) - [Ninja Releases](https://github.com/ninja-build/ninja/releases) ⚙️

---

## Installing Ninja Build Tools (for VSCode on Windows)  🏗️

1. **Download Ninja Build Tools:**
   - Go to the official Ninja releases page: [Ninja Releases](https://github.com/ninja-build/ninja/releases)
   - Download the latest `ninja-win.zip` file.

2. **Extract the Zip File:**
   - Extract the contents of the `ninja-win.zip` file to a directory, e.g., `C:\ninja`.

3. **Add Ninja to the System PATH:**
   - Open the Start Menu and search for "Environment Variables".
   - Click on "Edit the system environment variables".
   - In the System Properties window, click on the "Environment Variables" button.
   - Edit the "Path" variable and add `C:\ninja`.

4. **Verify Installation:**
   ```sh
   ninja --version
   ```
---

## Cloning the Repository 🌐
1. Open a terminal or command prompt.
2. Clone the repository recursively:
    ```sh
    git clone --recurse-submodules https://github.com/EhsanulHaqueSiam/MarioMultiverseAdventures.git
    cd MarioMultiverseAdventures
    ```
   **OR (SSH)**
    ```sh
    git clone --recurse-submodules git@github.com:EhsanulHaqueSiam/MarioMultiverseAdventures.git
    cd MarioMultiverseAdventures
    ```

---

## Setting Up vcpkg 📦
1. **Setup vcpkg (Linux or macOS):**
    ```sh
    cd external/vcpkg
    ./bootstrap-vcpkg.sh
    ```

   **Setup vcpkg (Windows):**
    ```sh
    cd external/vcpkg
    ./bootstrap-vcpkg.bat
    ```

2. **Add vcpkg to PATH:**
   - Temporary:
    ```sh
    export VCPKG_ROOT=$(pwd)
    export PATH=$VCPKG_ROOT:$PATH
    ```
   - Permanent:
     Add `VCPKG_ROOT` to environment variables.

3. **Install Dependencies:**
    ```sh
    cd ../..
    vcpkg install
    ```

---

## IDE Setup 💻

### **CLion Setup** 🧑‍💻

To set up CLion for the project with **vcpkg** integration, follow these steps:

#### 1\. **Verify vcpkg Installation** 🔍

Make sure **vcpkg** is installed and the `VCPKG_ROOT` environment variable is set. To verify, run:

```sh
echo $VCPKG_ROOT
```

#### 2\. **Open the Project in CLion** 📂

*   Launch **CLion** and select `Open` to open the project directory.

#### 3\. **Set CMake Options** ⚙️

*   Go to **File** > **Settings** > **Build, Execution, Deployment** > **CMake**.
*   Set the **CMake options** field to:

    ```sh
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
    ```

    This configures **vcpkg** as the package manager for the project.

#### 4\. **Apply and Reload** 🔄

*   Click **Apply** and then **OK**.
*   CLion will reload the project with the updated CMake options.

---

### **CLion Setup with vcpkg (Alternative Method)** 🔧

If you prefer a more integrated approach, you can use **CLion's Vcpkg tool window** to add and manage **vcpkg**.

#### 1\. **Open the Vcpkg Tool Window** 🪟

*   Go to **Main Menu** > **View** > **Tool Windows** > **Vcpkg**.

#### 2\. **Add the Vcpkg Repository** ➕

*   Click the **+** button to add a new **vcpkg** repository.
*   A window named **Add Vcpkg Repository** will pop up.
*   Set the **Name** to `vcpkg`.
*   The **URL** should auto-fill as `https://github.com/microsoft/vcpkg`.
*   Set the **Directory** to `$HOME/.vcpkg-clion/vcpkg`.
*   **Add vcpkg integration to existing CMake profiles** box should be checked.
*   **Debug** should be checked under **Add vcpkg integration to existing CMake profiles**.

#### 3\. **Confirm the Setup** ✅

*   Click **OK** to finish adding the repository. CLion will automatically sync with **vcpkg** and install any required dependencies.


---

### **Xcode Setup (macOS)** 🍎
1. Run script:
    ```sh
    ./scripts/generate_mac.sh
    ```
2. Open the project:
    ```sh
    open build/MarioMultiverseAdventures.xcodeproj
    ```
3. Build and run.

---

### **Visual Studio Setup (Windows)** 🖥️
1. Run script:
    ```bat
    scripts\generate_windows.bat
    ```
2. Open the solution:
    ```sh
    start build\MarioMultiverseAdventures.sln
    ```
3. Build and run.

---

### **VSCode Setup** 🖋️
1. Ensure `.vscode` has:
   - `settings.json`
   - `tasks.json`
   - `launch.json`
   - `CMakePresets.json`
2. Configure CMake:
    ```sh
    Ctrl+Shift+P -> CMake: Configure
    ```
3. Build:
    ```sh
    CMake: Build
    ```
4. Debug:
    ```sh
    Debug -> Start Debugging
    ```

---

## Platform-Specific Build Steps ⚙️

### **Linux Setup** 🐧
```sh
./scripts/generate_linux.sh
cmake --build build
./build/MarioMultiverseAdventures
```

### **macOS Setup** 🍎
```sh
./scripts/generate_mac.sh
cmake --build build
./build/MarioMultiverseAdventures
```

### **Windows Setup** 🖥️
```sh
scripts\generate_windows.bat
cmake --build build
build\MarioMultiverseAdventures.exe
```

---

## Contributing 🤝
1. Fork the repository.
2. Create a new branch:
    ```sh
    git checkout -b feature-branch
    ```
3. Commit changes:
    ```sh
    git add .
    git commit -m "Description of changes"
    ```
4. Push changes:
    ```sh
    git push origin feature-branch
    ```
5. Submit a pull request.

---

Follow these steps to set up and start developing the MarioMultiverseAdventures project on your preferred platform and IDE. 🚀
