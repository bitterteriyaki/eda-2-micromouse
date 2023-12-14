#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  CMD="gcc"
elif [[ "$OSTYPE" == "darwin"* ]]; then
  CMD="gcc-13"
fi

$CMD src/main.c -E -D DEBUG > output.c
