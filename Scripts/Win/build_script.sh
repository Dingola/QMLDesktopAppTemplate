#!/bin/bash

source Helpers/utils.sh
source Helpers/setup_python.sh

REQUIRED_PYTHON_VERSION="3.14.0"
REQUIRED_PYTHON_VERSION_SUFFIX="a1"

# Ensure the script is running as admin
check_admin

# Call the function to install or update Python
setup_python $REQUIRED_PYTHON_VERSION $REQUIRED_PYTHON_VERSION_SUFFIX
if [ $? -ne 0 ]; then
    echo "An error occurred during the setup of Python."
fi

read -p "Press enter to continue"
