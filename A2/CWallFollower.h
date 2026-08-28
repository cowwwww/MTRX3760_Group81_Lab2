//-----------------------------------------------------------------------------
// CWallFollower.h
//
// A robot that follows the wall on its right using exactly two range sensors.
//-----------------------------------------------------------------------------

#ifndef CWALLFOLLOWER_H
#define CWALLFOLLOWER_H

#include "CRangeSensor.h"
#include "CRobot.h"

class CWallMap;

class CWallFollower : public CRobot
{
    public:
        CWallFollower( CWallMap& arWallMap );

    protected:
        void Control();

    private:
        CRangeSensor mRightSensor;
        CRangeSensor mFrontRightSensor;
};

#endif
