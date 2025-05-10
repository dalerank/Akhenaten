#!/bin/bash

# Set the URL for your GitHub repository
APP_NAME=$(basename "$1")
APP_PATH=$(dirname "$1")
APP_PATH_COMPLETE=$APP_PATH"/"$APP_NAME

echo "basename: [$APP_NAME]"
echo "dirname : [$APP_PATH]"
echo "dirname : [$APP_PATH_COMPLETE]"

REPO_URL="https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac/master/macos_build.zip"

# Get the latest version number from your GitHub repository
echo Downloading from $REPO_URL

curl -# -L -o "/tmp/macos_build.zip" "$REPO_URL"

rm -rf "$APP_PATH_COMPLETE"
# Extract the downloaded file and copy it over any existing installation of your application
unzip "/tmp/macos_build.zip" -d "$APP_PATH"
rm "/tmp/macos_build.zip"

echo Done.