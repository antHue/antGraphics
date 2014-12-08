//
//  antMidi.h
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antMidi__
#define __ant_graphics__antMidi__



#include <iostream>
#include <memory>
#include <cstdlib>
#include <signal.h>

#include <chrono>
#include <thread>

#include "RtMidi.h"

class antMidi;
typedef std::shared_ptr<antMidi> antMidiShPtr;
typedef std::weak_ptr<antMidi> antMidiWkPtr;

class antMidi
{
    public :
    
    bool get( int * k_byte, float * value_byte );

    static antMidiShPtr create();
    ~antMidi();

    private :
    
    RtMidiIn * m_midi_in;
    static bool m_done;
    static void finish( int ignore );

    antMidi();
    antMidiWkPtr m_weak_ptr;
};


#endif /* defined(__ant_graphics__antMidi__) */
