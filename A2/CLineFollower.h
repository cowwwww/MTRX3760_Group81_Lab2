//-----------------------------------------------------------------------------
// CLineFollower.h
//
// A robot that follows the floor line using exactly two binary line sensors.
//-----------------------------------------------------------------------------

#ifndef CLINEFOLLOWER_H
#define CLINEFOLLOWER_H

#include "CLineSensor.h"
#include "CRobot.h"

class CWallMap;

class CLineFollower : public CRobot
{
    public:
        CLineFollower( CWallMap& arWallMap );

    protected:
        void Control();

    private:
        CLineSensor mLineSensor;
        CLineSensor mSideSensor;
};

#endif
