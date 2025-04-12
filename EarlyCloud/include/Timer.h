#pragma once

#ifndef _Timer_h_
#define _Timer_h_

#include "main.h"

//declares the timer class
class Timer {
    public:
        Timer();
        double getElapsedTimeMS();
        void reset();
    
    private:
        double start;
        
};

#endif