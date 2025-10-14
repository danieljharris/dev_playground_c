#!/usr/bin/env sh

set -eu

# Resolve repository root regardless of invocation path
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
BUILD_DIR="$SCRIPT_DIR/build"
VCPKG_ROOT_DEFAULT="$SCRIPT_DIR/vcpkg"
VCPKG_ROOT=${VCPKG_ROOT:-$VCPKG_ROOT_DEFAULT}
VCPKG_TRIPLET=${VCPKG_TRIPLET:-x64-linux}

# Prefer gcc-14/g++-14 if installed to get C++23 std::expected support
if command -v g++-14 >/dev/null 2>&1 && command -v gcc-14 >/dev/null 2>&1; then
	export CC=$(command -v gcc-14)
	export CXX=$(command -v g++-14)
	printf '%s\n' "Using compiler: $CXX"
else
	printf '%s\n' "g++-14/gcc-14 not found; using system default compiler: $(command -v ${CXX:-c++})"
fi

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
