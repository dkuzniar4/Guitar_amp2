/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   minus_OFF_png;
    const int            minus_OFF_pngSize = 810;

    extern const char*   minus_ON_png;
    const int            minus_ON_pngSize = 786;

    extern const char*   plus_OFF_png;
    const int            plus_OFF_pngSize = 922;

    extern const char*   plus_ON_png;
    const int            plus_ON_pngSize = 905;

    extern const char*   background_png;
    const int            background_pngSize = 53784;

    extern const char*   cab_OFF_png;
    const int            cab_OFF_pngSize = 2405;

    extern const char*   cab_ON_png;
    const int            cab_ON_pngSize = 2210;

    extern const char*   power_OFF_png;
    const int            power_OFF_pngSize = 1335;

    extern const char*   power_ON_png;
    const int            power_ON_pngSize = 2612;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
