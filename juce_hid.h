/*
  ==============================================================================
 
    juce_hid.h
    Created: 15 May 2018 1:39:06pm
    Author:  Chris Penny
 
  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.
 
 
 BEGIN_JUCE_MODULE_DECLARATION
 
 ID:               juce_hid
 vendor:           open
 version:          1.0.0
 name:             JUCE HIDAPI Wrapper
 description:      Wrapper for the hidapi library
 website:          
 
 dependencies:     juce_core, juce_events
 
 END_JUCE_MODULE_DECLARATION
 
 *******************************************************************************/


#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include "hid/hidapi.h"
#include "hid/juce_hid.h"
