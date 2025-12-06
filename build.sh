

BUILD_DIR="new_build"

rm -rf "${SCRIPT_DIR}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

cmake "${SCRIPT_DIR}"

cmake --build . --target long_number_lib long_number_tests

./long_number_tests
