#pragma once
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define ZeroMemory(target, size) memset(target, 0, size)

#include "commmands.h"
#include "CONFIG.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <pwd.h>