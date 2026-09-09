#!/usr/bin/env bash

_builddir="$PWD/build"
_proj_name="lis"
_binary="$_builddir/$_proj_name"
_checksum_file="$_builddir/source_files.sha256"

run_target() {
    exec "$_binary"
}

verify_checksum() {
    if [ ! -f "$_checksum_file" ]; then
        return 1
    fi

    sha256sum --status -c "$_checksum_file" 2>/dev/null
    return $?
}

update_checksum() {
    echo "Updating source code checksums..."
    find . -maxdepth 5 \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "CMakeLists.txt" \) \
    -not -path "*/build/*" -exec sha256sum {} + > "$_checksum_file"
}

do_build() {
    echo "Source code changed or binary missing. Building project..."
    cmake -S . -B "$_builddir"
    _build_st=$?

    if [ "$_build_st" -eq 0 ]; then
        cmake --build "$_builddir"
        _build_st=$?
        
        if [ "$_build_st" -eq 0 ]; then
            update_checksum
            run_target
        fi
    fi
}

if [ -e "$_binary" ] && verify_checksum; then
    echo "No changes detected. Running target..."
    run_target
else
    do_build
fi
