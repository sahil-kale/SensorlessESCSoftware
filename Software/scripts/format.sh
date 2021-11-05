#!/bin/bash

echo "Running clang-format"

clang-format --version

clang-format -style=file -i Core/Src/bldc.c Core/Src/pwm.c Core/Inc/bldc.h Core/Inc/pwm.h
