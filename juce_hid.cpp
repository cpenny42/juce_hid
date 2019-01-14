/*
  ==============================================================================
 
    juce_hid.cpp
    Created: 15 May 2018 1:39:06pm
    Author:  Chris Penny
 
  ==============================================================================
*/

#include "juce_hid.h"

#if JUCE_MAC
#include "hid/hidapi_mac.c"
#elif JUCE_WINDOWS
#include "hid/hidapi_windows.c"
#else
#error Trying to include the HID API on an unsupported platform!
#endif

#include "hid/juce_hid.cpp"
