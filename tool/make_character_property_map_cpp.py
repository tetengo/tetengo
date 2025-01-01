#! /usr/bin/env python
"""Makes character_property_map.txt for tetengo::text

    Copyright (C) 2019-2025 kaoru  https://www.tetengo.org/
"""

import sys
from pathlib import Path


def main(args: list[str]) -> None:
    """The main function.

    Args:
        args: Program arguments
    """
    if len(args) < 2:
        print(
            "Usage: ./make_character_property_map_cpp.py character_property_map.txt ../library/text/cpp/src/character_property_map.cpp",
            file=sys.stderr,
        )
        sys.exit(0)
    elements: list[str] = _load_file(Path(args[0]))
    content: str = _make_cpp_source(elements)
    _save_file(Path(args[1]), content)


def _load_file(path: Path) -> list[str]:
    elements: list[str] = []
    with path.open(mode="r") as stream:
        for line in stream:
            line = line.rstrip("\r\n")
            [code, east_asian_width, emoji, grapheme] = line.split("\t")
            elements.append(_make_element(code, east_asian_width, emoji, grapheme))
    return elements


def _make_element(code: str, east_asian_width: str, emoji: str, grapheme: str) -> str:
    return (
        "        { "
        + "0x{}, east_asian_width_class_type::{}, emoji_type::{}, grapheme_break_property_type::{}".format(
            code,
            _to_east_asian_width_class_type(east_asian_width),
            _to_emoji_type(emoji),
            _to_grapheme_break_property(grapheme),
        )
        + " },\n"
    )


def _to_east_asian_width_class_type(symbol: str) -> str:
    if symbol == "A":
        return "ambiguous"
    elif symbol == "F":
        return "fullwidth"
    elif symbol == "H":
        return "halfwidth"
    elif symbol == "Na":
        return "narrow"
    elif symbol == "W":
        return "wide"
    elif symbol == "N":
        return "neutral"
    else:
        raise RuntimeError("Unknown class: {}".format(symbol))


def _to_emoji_type(symbol: str) -> str:
    if symbol == "Emoji":
        return "emoji"
    else:
        return "normal"


def _to_grapheme_break_property(symbol: str) -> str:
    if symbol == "CR":
        return "cr"
    elif symbol == "LF":
        return "lf"
    elif symbol == "Control":
        return "control"
    elif symbol == "Extend":
        return "extend"
    elif symbol == "ZWJ":
        return "zwj"
    elif symbol == "Regional":
        return "regional"
    elif symbol == "Prepend":
        return "prepend"
    elif symbol == "SpacingMark":
        return "spacing_mark"
    elif symbol == "L":
        return "l"
    elif symbol == "V":
        return "v"
    elif symbol == "T":
        return "t"
    elif symbol == "LV":
        return "lv"
    elif symbol == "LVT":
        return "lvt"
    elif symbol == "Other":
        return "other"
    else:
        raise RuntimeError("Unknown grapheme: {}".format(symbol))


def _make_cpp_source(elements: list[str]) -> str:
    content: str = """/*! \\file
    \\brief A character property map.

    This file is generated by tool/make_character_property_map_cpp.py.

    Copyright (C) 2019-2025 kaoru  https://www.tetengo.org/
*/

#include <cstddef>

#include "tetengo.text.grapheme_splitting.character_property_map.hpp"


namespace tetengo::text::grapheme_splitting
{
"""
    content += "    const std::size_t character_property_map_size = {};\n\n".format(
        len(elements)
    )
    content += "    // clang-format off\n"
    content += (
        "    const character_property_map_element_type character_property_map[] = {\n"
    )
    for e in elements:
        content += e
    content += "    };\n"
    content += "    // clang-format on\n"
    content += """

}
"""
    return content


def _save_file(path: Path, content: str) -> None:
    with path.open(mode="w", newline="\r\n") as stream:
        stream.write(content)


if __name__ == "__main__":
    main(sys.argv[1:])
