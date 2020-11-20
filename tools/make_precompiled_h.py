#! /usr/bin/env python3
# Makes precompiled.h
# Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/

from pathlib import Path
import re

import list_sources


def main():
    (libc_includes, libcpp_includes, boost_includes) = list_includes()
    precompiled_h = \
        make_precompiled_h(libc_includes, libcpp_includes, boost_includes)
    
    save_to_file(precompiled_h, precompiled_h_path())

def list_includes():
    libc_includes = set()
    libcpp_includes = set()
    boost_includes = set()
    
    for path in list_sources.list():
        (
            libc_includes_per_file,
            libcpp_includes_per_file,
            boost_includes_per_file
        ) = list_includes_per_file(path)
        libc_includes |= libc_includes_per_file
        libcpp_includes |= libcpp_includes_per_file
        boost_includes |= boost_includes_per_file
    
    return (libc_includes, libcpp_includes, boost_includes)

def list_includes_per_file(path):
    libc_includes = set()
    libcpp_includes = set()
    boost_includes = set()
    
    with path.open() as stream:
        for line in stream:
            line = line.rstrip('\r\n')
            
            libc_match = re.search('^#\s*include\s+<([46a-z]+\.h)>', line)
            if libc_match:
                libc_includes.add(libc_match.group(1))
                continue
            
            libcpp_match = re.search('^#\s*include\s+<([a-z_/]+)>', line)
            if libcpp_match:
                libcpp_includes.add(libcpp_match.group(1))
                continue
            
            boost_match = re.search('^#\s*include\s+<(boost\/[^>]+)>', line)
            if \
                boost_match and \
                not re.match('^#\s*include\s+<boost\/test\/', line):
                boost_includes.add(boost_match.group(1))
                continue
    
    return (libc_includes, libcpp_includes, boost_includes)

def make_precompiled_h(libc_includes, libcpp_includes, boost_includes):
    result = ''
    
    result += '''
/*! \\file
    \\brief The precompiled header.

    This file is generated by tools/make_precompiled_h.py.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H
'''.strip() + '\n\n\n'
    
    result += '/* C Standard Library */\n'
    for h in sorted(libc_includes):
        result += '#include <' + h + '>\n'
    result += '\n'
    
    result += '#if defined(__cplusplus)\n\n'
    
    result += '// C++ Standard Library\n'
    for h in sorted(libcpp_includes):
        result += '#include <' + h + '>\n'
    result += '\n'
    
    result += '// Boost\n'
    for h in sorted(boost_includes):
        result += '#include <' + h + '>\n'
    result += '\n'
    
    result += '#endif\n'
    
    result += '\n\n' + '''
#endif
'''.strip() + '\n'

    return result

def precompiled_h_path():
    root_path= Path(__file__).parent.parent
    return root_path / 'precompiled' / 'precompiled.h'

def save_to_file(content, path):
    with path.open(mode='w', newline='\r\n') as stream:
        stream.write(content)

main()
