// string utility functions

#pragma once

//local headers

//third party headers

//standard headers
#include <string>


/// maximum size of conversion buffer
static const int CONVERSION_BUFFER_LENGTH = 128;

/// build formatted string
/// adapted from Urho3D
std::string format_string(const char* str, ...);

/// build formatted string with va args
/// adapted from Urho3D
std::string format_string_with_args(const char* str, va_list args);
