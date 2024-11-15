#!/bin/bash

source Helpers/utils.sh

# Function to install or update Python
setup_python() {
    local REQUIRED_PYTHON_VERSION=${1:-"3.14.0"}
    local REQUIRED_PYTHON_VERSION_SUFFIX=${2:-"a1"}
    PYTHON_INSTALLER_URL="https://www.python.org/ftp/python/$REQUIRED_PYTHON_VERSION/python-${REQUIRED_PYTHON_VERSION}${REQUIRED_PYTHON_VERSION_SUFFIX}-amd64.exe"
    PYTHON_INSTALLER="$(pwd -W)/python-installer.exe"  # Use Windows path for the installer
    REQUIRED_SPACE_MB=250  # Required space in MB

    # Function to clean up the installer file
    cleanup() {
        if [ -f "$PYTHON_INSTALLER" ]; then
            rm -f "$PYTHON_INSTALLER"
            echo "Installer file $PYTHON_INSTALLER has been removed."
        fi
    }

    # Check if Python is installed
    if command -v py &> /dev/null
    then
        PYTHON_VERSION=$(py --version 2>&1 | awk '{print $2}')
        echo "Found Python version: $PYTHON_VERSION"
        if version_greater_equal $PYTHON_VERSION $REQUIRED_PYTHON_VERSION
        then
            echo "Python version is sufficient: $PYTHON_VERSION"
        else
            echo "Python version is older than $REQUIRED_PYTHON_VERSION."
            read -p "Do you want to update Python to $REQUIRED_PYTHON_VERSION? (y/n): " choice
            case "$choice" in
              y|Y )
                read -p "Enter the directory where Python should be installed (default is C:\\\Python, press Enter to use default): " PYTHON_DIR
                PYTHON_DIR=${PYTHON_DIR:-C:\\Python}
                check_disk_space "$PYTHON_DIR" $REQUIRED_SPACE_MB || return 1
                echo "Downloading and installing Python $REQUIRED_PYTHON_VERSION to $PYTHON_DIR from $PYTHON_INSTALLER_URL..."
                curl -o $PYTHON_INSTALLER $PYTHON_INSTALLER_URL || { cleanup; return 1; }
                echo "Installer downloaded to $PYTHON_INSTALLER"
                ls -l $PYTHON_INSTALLER  # List the installer file details
                INSTALL_CMD="Start-Process -FilePath \"$PYTHON_INSTALLER\" -ArgumentList \"/quiet InstallAllUsers=1 TargetDir=$PYTHON_DIR PrependPath=1 Include_test=0\" -NoNewWindow -Wait"
                echo "Executing: powershell.exe -Command \"$INSTALL_CMD\""
                powershell.exe -Command "$INSTALL_CMD"
                if [ $? -ne 0 ]; then
                    echo "Python update failed. Please install Python manually and try again."
                    cleanup
                    return 1
                fi
                if command -v py &> /dev/null
                then
                    PYTHON_VERSION=$(py --version 2>&1 | awk '{print $2}')
                    if version_greater_equal $PYTHON_VERSION $REQUIRED_PYTHON_VERSION
                    then
                        echo "Python updated successfully: $PYTHON_VERSION"
                    else
                        echo "Python update failed. Please install Python manually and try again."
                        cleanup
                        return 1
                    fi
                else
                    echo "Python update failed. Please install Python manually and try again."
                    cleanup
                    return 1
                fi
                cleanup
                ;;
              n|N ) echo "Python update aborted."; return 1;;
              * ) echo "Invalid choice. Python update aborted."; return 1;;
            esac
        fi
    else
        echo "Python could not be found."
        read -p "Do you want to install Python $REQUIRED_PYTHON_VERSION? (y/n): " choice
        case "$choice" in
          y|Y )
            read -p "Enter the directory where Python should be installed (default is C:\\\Python, press Enter to use default): " PYTHON_DIR
            PYTHON_DIR=${PYTHON_DIR:-C:\\Python}
            check_disk_space "$PYTHON_DIR" $REQUIRED_SPACE_MB || return 1
            echo "Downloading and installing Python $REQUIRED_PYTHON_VERSION to $PYTHON_DIR from $PYTHON_INSTALLER_URL..."
            curl -o $PYTHON_INSTALLER $PYTHON_INSTALLER_URL || { cleanup; return 1; }
            echo "Installer downloaded to $PYTHON_INSTALLER"
            ls -l $PYTHON_INSTALLER  # List the installer file details
            INSTALL_CMD="Start-Process -FilePath \"$PYTHON_INSTALLER\" -ArgumentList \"/quiet InstallAllUsers=1 TargetDir=$PYTHON_DIR PrependPath=1 Include_test=0\" -NoNewWindow -Wait"
            echo "Executing: powershell.exe -Command \"$INSTALL_CMD\""
            powershell.exe -Command "$INSTALL_CMD"
            if [ $? -ne 0 ]; then
                echo "Python installation failed. Please install Python manually and try again."
                cleanup
                return 1
            fi
            if command -v py &> /dev/null
            then
                PYTHON_VERSION=$(py --version 2>&1 | awk '{print $2}')
                if version_greater_equal $PYTHON_VERSION $REQUIRED_PYTHON_VERSION
                then
                    echo "Python installed successfully: $PYTHON_VERSION"
                else
                    echo "Python installation failed. Please install Python manually and try again."
                    cleanup
                    return 1
                fi
            else
                echo "Python installation failed. Please install Python manually and try again."
                cleanup
                return 1
            fi
            cleanup
            ;;
          n|N ) echo "Python installation aborted."; return 1;;
          * ) echo "Invalid choice. Python installation aborted."; return 1;;
        esac
    fi
}
