# -*- coding: utf-8 -*-

from __future__ import print_function
from __future__ import with_statement

known_text_ext = set([
    "c", "C", "cc", "cpp", "cxx",
    "h", "H", "hh", "hpp", "hxx",
    "cu", "cmakein",
    "sh", "py", "bash", "bashrc",
    "txt", "md",
    "json", "yml", "yaml"
    ])

known_text_filename = set([
    ".gitignore",
    "LICENSE",
    ])

known_binary_ext = set([
    "tar", "gz",
    ])

known_binary_filename = set([
    ])

known_executable_ext = set([
    "bash", "sh"
    ])

known_executable_filename = set([
    ])


import codecs
import io
import os
import stat
import sys


def check_executable_bit(filepath, filename, fileext, dofix):
    mode = os.stat(filepath)[stat.ST_MODE]
    expect_x = fileext in known_executable_ext or filename in known_binary_filename
    if expect_x:
        expect_mode = mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH
    else:
        expect_mode = mode & ~stat.S_IXUSR & ~stat.S_IXGRP & ~stat.S_IXOTH
    if mode != expect_mode:
        if dofix:
            print("%s: fix mode %s -> %s" % (filepath, oct(mode)[1:], oct(expect_mode)[1:]))
            os.chmod(filepath, expect_mode)
        else:
            if expect_x:
                print("%s: mode %s, expect executable %s" % (filepath, oct(mode)[1:], oct(expect_mode)[1:]))
            else:
                print("%s: mode %s, expect not executable %s" % (filepath, oct(mode)[1:], oct(expect_mode)[1:]))
            return False
    return True


def check_lines(filepath, filename, fileext, dofix):
    is_known_binary = fileext in known_binary_ext or filename in known_binary_filename
    if is_known_binary:
        return True

    is_known_text = fileext in known_text_ext or filename in known_text_filename
    if not is_known_text:
        print("%s: is this text or binary file? Update %s" % (filepath, __file__))
        return False

    with codecs.open(filepath, "r", encoding="ascii") as file:
        lines = file.readlines()
    success = True
    for ln in range(1, len(lines) + 1):
        line = lines[ln - 1]
        assert len(line) > 0

        if line[0] == '\t':
            print("%s: line %d: start with <TAB>" % (filepath, ln))
            success = False
        if (line[-1] != '\n'):
            if ln == len(lines):
                print("%s: line %d: last line without <LF>" % (filepath, ln))
            else:
                print("%s: line %d: newline charactor is not <LF>" % (filepath, ln))
            success = False
        else:  # line[-1] == '\n'
            if len(line) >= 2 and line[-2] == '\r':
                print("%s: line %d: newline charactor is <CR><LF>" % (filepath, ln))
                success = False
        line_no_nl = line
        while line_no_nl and line_no_nl[-1] in ('\r', '\n'):
            line_no_nl = line_no_nl[:-1]
        if line_no_nl and line_no_nl[-1] in (' ', '\t'):
            print("%s: line %d: contains tailing <SPACE> or <TAB>" % (filepath, ln))
            success = False
        #print("%.4d | %s" % (ln, line_no_nl))
    return success


def main():
    """
    args:
        <file> [--fix]
    NOTE:
        <file> must be the first argument!
    """
    assert len(sys.argv) in (2, 3)

    filepath = sys.argv[1]
    assert os.path.isfile(filepath)
    assert not os.path.islink(filepath)
    filename = os.path.basename(filepath)
    fileext = os.path.splitext(filepath)[1]
    fileext = fileext[1:] if fileext else fileext

    if len(sys.argv) == 3:
        assert(sys.argv[2] == "--fix")
        dofix = True
    else:
        dofix = False

    success = True

    # Check for executable bit
    success = check_executable_bit(filepath, filename, fileext, dofix) and success

    # Check newlines, tabs, tailing spaces...
    success = check_lines(filepath, filename, fileext, dofix) and success

    return 0 if success else 1


if __name__ == "__main__":
    sys.exit(int(main()))
