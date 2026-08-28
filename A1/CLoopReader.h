//-----------------------------------------------------------------------------
// CLoopReader.h
//
// Reads one closed loop from a .map file. The file format is the same as the
// supplied Lab 2 example: loop, startpose, and vertex instructions.
//-----------------------------------------------------------------------------

#ifndef CLOOPREADER_H
#define CLOOPREADER_H

#include "CRender.h"

#include <string>
#include <vector>

struct CPose
{
    Vec2D mPosition;
    float mHeading;
};

class CLoopReader
{
    public:
        CLoopReader();

        bool ReadFile( const std::string& arFilename );

        const std::string& GetName() const;
        const CPose& GetStartPose() const;
        const std::vector<Vec2D>& GetVertices() const;

    private:
        std::string mName;
        CPose mStartPose;
        std::vector<Vec2D> mVertices;
};

#endif
