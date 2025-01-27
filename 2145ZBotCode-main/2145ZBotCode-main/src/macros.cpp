#include "devices.hpp"
#include "macros.hpp"

int selectedMacro = 0;

void doNothing() {}

void leftQualsBackToBar() {

}

void runSelectedMacro(Macro macros[], size_t macroCount) {
    if(selectedMacro >= 0 && selectedMacro < macroCount) {
        macros[selectedMacro].function();
    } else {
        // if we have no macros then do nothing
        doNothing();
    }
}
