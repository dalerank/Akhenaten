#!/bin/bash

CURRENT_DIR="$(pwd)"

# --- Configuration ---
if [ -f "$CURRENT_DIR"/buildnumber.txt ]; then
    SERVER_BUILD_URL="https://www.slsoft.de/extern/software/akhenaten/buildnumber.txt"
    LOCAL_BUILD_FILE="buildnumber.txt"
    if [[ "$OSTYPE" == "darwin"* ]]; then
        SERVER_ZIP_URL="https://www.slsoft.de/extern/software/akhenaten/macos_build.zip"
    else
        SERVER_ZIP_URL="https://www.slsoft.de/extern/software/akhenaten/linux_build.zip"
    fi
else
    SERVER_BUILD_URL="https://www.slsoft.de/extern/software/akhenaten/buildnumber_nightly.txt"
    LOCAL_BUILD_FILE="buildnumber_nightly.txt"
    if [[ "$OSTYPE" == "darwin"* ]]; then
        SERVER_ZIP_URL="https://www.slsoft.de/extern/software/akhenaten/macos_build_nightly.zip"
    else
        SERVER_ZIP_URL="https://www.slsoft.de/extern/software/akhenaten/linux_build_nightly.zip"
    fi
fi

# --- Temp-Folder OS related ---
if [[ "$OSTYPE" == "darwin"* ]]; then
    TEMP_DIR="/private/tmp/akhenaten_update"
else
    TEMP_DIR="/tmp/akhenaten_update"
fi

mkdir -p "$TEMP_DIR"

echo "Checking Buildnumber on Server ..."

# --- Get server buildnumber ---
SERVER_BUILD=$(curl -s "$SERVER_BUILD_URL")
if [[ -z "$SERVER_BUILD" ]]; then
    echo "Error: Can't fetch buildnumber from server."
    exit 1
fi
echo "Server Buildnummer: $SERVER_BUILD"

# --- Get local buildnumber ---
if [[ -f "$LOCAL_BUILD_FILE" ]]; then
    LOCAL_BUILD=$(cat "$LOCAL_BUILD_FILE")
else
    LOCAL_BUILD=0
fi
echo "Local Buildnummer: $LOCAL_BUILD"


# --- Compare ---
if (( SERVER_BUILD > LOCAL_BUILD )); then
    echo "New version available. Downloading..."

    ZIP_PATH="$TEMP_DIR/akhenaten.zip"

    # --- Download Zip ---
    curl -sS -L -o "$ZIP_PATH" "$SERVER_ZIP_URL"
    if [[ $? -ne 0 ]]; then
        echo "Error on download archive."
        exit 1
    fi

    echo "Update downloaded to $ZIP_PATH"

    # --- Extract ---
    echo "Extract Update to $CURRENT_DIR..."
    
    if [[ "$OSTYPE" == "darwin"* ]]; then
    	cd "$CURRENT_DIR"/../../../
    	tar -xf "$ZIP_PATH"
		else
			cd "$CURRENT_DIR"
    	tar -xf "$ZIP_PATH"
		fi

    if [[ $? -ne 0 ]]; then
        echo "Error on extracting!"
        exit 1
    fi

    echo "Update succesfully installed."

    # --- Clean up ---
    rm -rf "$TEMP_DIR"
else
    echo "No new version available. You have the latest version already."
fi