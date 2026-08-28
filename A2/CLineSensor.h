//-----------------------------------------------------------------------------
// CLineSensor.h
//
// A binary floor sensor mounted at a fixed position on the robot.
//-----------------------------------------------------------------------------

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CLoopReader.h"

class CWallMap;

class CLineSensor
{
    public:
        CLineSensor( float aForwardOffset, float aRightOffset );

        bool Read( const CWallMap& arWallMap, const CPose& arRobotPose ) const;

    private:
        float mForwardOffset;
        float mRightOffset;
};

#endif
