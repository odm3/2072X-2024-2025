#pragma once

struct Macro {
    const char* name;
    void (*function)();
};

void leftQualsBackToBar();
void doNothing();
void runSelectedMacro(Macro macros[], size_t macroCount);
