#!/usr/bin/env bash

set -e

# Redirect stdout to stderr
exec 1>&2


cd "$(dirname "$(readlink -f "$0")")/../.."

# Untracked (new) files: git status --short --untracked-files | grep '^?' | cut "-d " -f2-
# Tracked files: git ls-files
# All files: git status --short --untracked-files | grep '^?' | cut "-d " -f2- && git ls-files
files="$(git ls-files | sort -u)"
#files="$(git status --short --untracked-files | grep '^?' | cut "-d " -f2- && git ls-files)"


# Find python
if hash python; then
    PYTHON=python
elif hash python2; then
    PYTHON=python2
elif hash python3; then
    PYTHON=python3
else
    echo "python/python2/python3 not found"
    exit 1
fi

success="yes"
for file in $files; do
    if [ -L "$file" ]; then
        continue  # ignore all symlinks
    elif [ ! -f "$file" ]; then
        continue  # ignore all non-files
    fi

    # ignore all files in 3rdparty/xxx/
    if [[ "$file" =~ ^3rdparty/[^/]+/ ]]; then
        continue
    fi

    #echo "Check: $file"
    if ! "$PYTHON" lint/pre-commit/checkone.py "$file" "$@"; then
        success="no"
    fi
done

if [ "$success" = "yes" ]; then
    exit 0
else
    echo "Linting failed. Abort."
    exit 1
fi
