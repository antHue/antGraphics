//
//  antMidi.cpp
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antMidi.h"

bool antMidi::m_done;

antMidiShPtr antMidi::create()
{
    antMidiShPtr midi_sh_ptr( new antMidi() );
    midi_sh_ptr->m_weak_ptr = midi_sh_ptr;
    return midi_sh_ptr;
}

antMidi::antMidi()
{
    // RtMidiIn constructor
    try {
        m_midi_in = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
        std::cout << "Midi In ERROR" << std::endl;
        exit( EXIT_FAILURE );
    }
    
    // Check available ports.
    unsigned int nPorts = m_midi_in->getPortCount();
    
    std::cout << "Port count : " << nPorts << std::endl;
    
    if ( nPorts == 0 )
    {
        std::cout << "No ports available!\n";
    }
    
    m_midi_in->openPort( 0 );
    
    // Don't ignore sysex, timing, or active sensing messages.
    m_midi_in->ignoreTypes( false, false, false );
    
    // Install an interrupt handler function.
    antMidi::m_done = false;
    
    (void) signal(SIGINT, finish);

}

bool antMidi::get( int * k_byte, float * value_byte )
{
    std::vector<unsigned char> message;

    int nBytes, i;
    double stamp;
    
    // Periodically check input queue.
    //std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
    //while ( !antMidi::m_done )
    {
        stamp = m_midi_in->getMessage( &message );
        nBytes = message.size();
        
//        for ( i=0; i<nBytes; i++ )
//        {
//            std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
//            //mpc->parseByte( i, atoi( message[i]) );
//        }

        if ( nBytes > 0 )
        {
//            std::cout << "stamp = " << stamp << std::endl;
            *k_byte = (int)message[1];
            *value_byte = (float)message[2];
            std::cout << *k_byte << std::endl;

            return true;
        }
        
        return false;
        //mpc->parseStamp( stamp );
        
        // Sleep for 10 milliseconds ... platform-dependent.
        //std::this_thread::sleep_for( std::chrono::milliseconds(10) );
        //usleep( 10 );
    }
}

void antMidi::finish( int ignore ) { antMidi::m_done = true; }

antMidi::~antMidi()
{
    delete m_midi_in;
    m_weak_ptr.reset();
}