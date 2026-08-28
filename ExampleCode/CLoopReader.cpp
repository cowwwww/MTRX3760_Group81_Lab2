//-----------------------------------------------------------------------------
// CLoopReader.cpp
//
// Reads a loop file into a single loop. The file format is described at the top
// of CLoopReader.h. ReadFile ignores blank lines and '#' comments, and stops
// with a clear message naming the line if it meets something it cannot parse.
//-----------------------------------------------------------------------------

#include "CLoopReader.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

//---Degrees in the file are converted to radians for use in the program.------
static const float kDegreesToRadians = float( M_PI ) / 180.0f;


//-----------------------------------------------------------------------------
CLoopReader::CLoopReader()
    :
        mStartPose( { { 0.0f, 0.0f }, 0.0f } )
{
}


//-----------------------------------------------------------------------------
const std::string& CLoopReader::GetName() const
{
    return mName;
}


//-----------------------------------------------------------------------------
const CPose& CLoopReader::GetStartPose() const
{
    return mStartPose;
}


//-----------------------------------------------------------------------------
const std::vector<Vec2D>& CLoopReader::GetVertices() const
{
    return mVertices;
}


//-----------------------------------------------------------------------------
bool CLoopReader::ReadFile( const std::string& arFilename )
{
    bool Okay = true;

    std::ifstream File( arFilename );
    if( !File )
    {
        std::cout << "CLoopReader: could not open file '" << arFilename << "'" << std::endl;
        Okay = false;
    }

    std::string Line;
    int LineNumber = 0;
    bool HaveLoop = false;

    while( Okay && std::getline( File, Line ) )
    {
        ++LineNumber;

        // Strip any comment: everything from a '#' to the end of the line.
        std::string::size_type Hash = Line.find( '#' );
        if( Hash != std::string::npos )
        {
            Line = Line.substr( 0, Hash );
        }

        // Split the remaining line into whitespace-separated words. A line with
        // no words (blank, or comment-only) has no keyword and is skipped.
        std::istringstream Words( Line );
        std::string Keyword;
        if( Words >> Keyword )
        {
            if( Keyword == "loop" )
            {
                if( HaveLoop )
                {
                    std::cout << "CLoopReader: a second 'loop' on line " << LineNumber
                              << " (a file describes one loop)" << std::endl;
                    Okay = false;
                }
                else if( !(Words >> mName) )
                {
                    std::cout << "CLoopReader: 'loop' needs a name on line "
                              << LineNumber << std::endl;
                    Okay = false;
                }
                else
                {
                    HaveLoop = true;
                }
            }
            else if( Keyword == "startpose" )
            {
                float X = 0.0f;
                float Y = 0.0f;
                float HeadingDegrees = 0.0f;
                if( !(Words >> X >> Y >> HeadingDegrees) )
                {
                    std::cout << "CLoopReader: 'startpose' needs x, y and heading on line "
                              << LineNumber << std::endl;
                    Okay = false;
                }
                else if( !HaveLoop )
                {
                    std::cout << "CLoopReader: 'startpose' before any 'loop' on line "
                              << LineNumber << std::endl;
                    Okay = false;
                }
                else
                {
                    mStartPose = CPose{ { X, Y }, HeadingDegrees * kDegreesToRadians };
                }
            }
            else if( Keyword == "vertex" )
            {
                float X = 0.0f;
                float Y = 0.0f;
                if( !(Words >> X >> Y) )
                {
                    std::cout << "CLoopReader: 'vertex' needs x and y on line "
                              << LineNumber << std::endl;
                    Okay = false;
                }
                else if( !HaveLoop )
                {
                    std::cout << "CLoopReader: 'vertex' before any 'loop' on line "
                              << LineNumber << std::endl;
                    Okay = false;
                }
                else
                {
                    mVertices.push_back( { X, Y } );
                }
            }
            else
            {
                std::cout << "CLoopReader: unknown keyword '" << Keyword << "' on line "
                          << LineNumber << std::endl;
                Okay = false;
            }
        }
    }
    
    return Okay;
}
