# RubiksClock

<!-- markdownlint-disable MD013 --><!-- Badges cannot be split up over lines, hence will break 80 characters per line -->

[![Check build](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_build.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_build.yaml)
[![check_links](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_links.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_links.yaml)
[![Check Markdown](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_markdown.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_markdown.yaml)
[![Check spelling](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_spelling.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/check_spelling.yaml)
[![codecov](https://codecov.io/gh/richelbilderbeek/RubiksClock/branch/main/graph/badge.svg)](https://codecov.io/gh/richelbilderbeek/RubiksClock)
[![Create Zensical website](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/create_zensical_website.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/RubiksClock/actions/workflows/create_zensical_website.yaml)

<!-- markdownlint-enable MD013 -->

[Go to the nicely rendered website](https://richelbilderbeek.github.io/RubiksClock/),
where you can also play the game in your browser.

Rubik's Clock is a simulation of the Rubik's Clock puzzle,
programmed in C++ using Qt.

![Rubik's Clock](docs/rubiksclock.png)

## Build

Rubik's Clock needs Qt 6:

```bash
qmake RubiksClock.pro
make
```

To build the WebAssembly version, do the same with the `qmake` of
Qt for WebAssembly and the matching version of Emscripten.
[build_game.yaml](.github/workflows/build_game.yaml)
shows which versions are used and builds the Linux, Windows and WebAssembly versions.
[create_zensical_website.yaml](.github/workflows/create_zensical_website.yaml)
puts the WebAssembly and Windows versions on the website.

## I want to contribute

Awesome!

You can collaborate by

* add a GitHub issue: this can be a question, suggestion, or whatever
* fork this repository, make the changes, and submit a pull request.

## External links

* [Richel Bilderbeek's games](https://github.com/richelbilderbeek/Games)
