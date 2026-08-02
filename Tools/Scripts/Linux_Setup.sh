#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/Builds/conan"

BUILD_TYPE="${1:-d}"

case "${BUILD_TYPE}" in
    d)
        CONAN_BUILD_TYPE="Debug"
        ;;
    r)
        CONAN_BUILD_TYPE="Release"
        ;;
    *)
        echo "Error: invalid build type '${BUILD_TYPE}'."
        echo "Usage: $0 [d|r] where d - debug, r - release"
        exit 1
        ;;
esac

echo "[CLI-Task-Manager] Project root: ${PROJECT_ROOT}"
echo "[CLI-Task-Manager] Conan directory: ${BUILD_DIR}"
echo "[CLI-Task-Manager] Build type: ${CONAN_BUILD_TYPE}"

mkdir -p "${BUILD_DIR}"

echo "[CLI-Task-Manager] Detecting Conan profile..."
conan profile detect --force

echo "[CLI-Task-Manager] Installing dependencies..."

echo conan install "${PROJECT_ROOT}" \
    --output-folder="${BUILD_DIR}" \
    --build=missing \
    -s build_type="${CONAN_BUILD_TYPE}"

echo "[CLI-Task-Manager] Dependencies successfully installed."