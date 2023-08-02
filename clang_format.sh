#!/usr/bin/env bash

find ./src/ -iname *.h -o -iname *.cpp -o -iname *.hpp | xargs clang-format-15 -i
