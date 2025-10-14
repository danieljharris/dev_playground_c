#!/usr/bin/env sh

set -eu

if ! command -v cmake >/dev/null 2>&1; then
	printf '%s\n' "Error: cmake is not installed or not on PATH." >&2
	exit 1
fi

if ! command -v git >/dev/null 2>&1; then
	printf '%s\n' "Error: git is not installed or not on PATH." >&2
	exit 1
fi

for dep in curl zip unzip tar pkg-config; do
	if ! command -v "$dep" >/dev/null 2>&1; then
		printf '%s\n' "Error: $dep is required for vcpkg. Install it via your package manager and rerun." >&2
		exit 1
	fi
done

# Resolve repository root regardless of invocation path
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
BUILD_DIR="$SCRIPT_DIR/build"
VCPKG_ROOT_DEFAULT="$SCRIPT_DIR/vcpkg"
VCPKG_ROOT=${VCPKG_ROOT:-$VCPKG_ROOT_DEFAULT}
VCPKG_TRIPLET=${VCPKG_TRIPLET:-x64-linux}

if [ ! -d "$VCPKG_ROOT" ]; then
	printf '%s\n' "Cloning vcpkg into $VCPKG_ROOT"
	git clone https://github.com/microsoft/vcpkg "$VCPKG_ROOT"
fi

if [ ! -f "$VCPKG_ROOT/vcpkg" ] && [ ! -f "$VCPKG_ROOT/vcpkg.exe" ]; then
	if ! command -v curl >/dev/null 2>&1; then
		printf '%s\n' "Error: curl is required to bootstrap vcpkg. Install curl (and zip unzip tar) and rerun." >&2
		exit 1
	fi
	printf '%s\n' "Bootstrapping vcpkg"
	sh "$VCPKG_ROOT/bootstrap-vcpkg.sh" -disableMetrics
fi

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

"$VCPKG_ROOT/vcpkg" install --triplet "$VCPKG_TRIPLET" --clean-after-build

cmake -S "$SCRIPT_DIR" \
	-B "$BUILD_DIR" \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
	-DVCPKG_TARGET_TRIPLET="$VCPKG_TRIPLET" \
	-DVCPKG_MANIFEST_DIR="$SCRIPT_DIR"
cmake --build "$BUILD_DIR" --target playground
