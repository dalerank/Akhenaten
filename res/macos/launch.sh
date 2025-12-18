#!/bin/bash

SCRIPT_SOURCE="${BASH_SOURCE[0]}"
SCRIPT_DIR="$(cd "$(dirname "$SCRIPT_SOURCE")" >/dev/null 2>&1 && pwd)"

cd "$SCRIPT_DIR"

./updater.sh

./akhenaten &
