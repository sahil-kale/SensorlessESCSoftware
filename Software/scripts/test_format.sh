#!/bin/bash

clang-format -style=file -Werror --dry-run -i Core/Src/bldc.c Core/Src/pwm.c Core/Inc/bldc.h Core/Inc/pwm.h
