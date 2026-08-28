//-----------------------------------------------------------------------------
// CRangeSensor.cpp
//-----------------------------------------------------------------------------

#include "CRangeSensor.h"
#include "CWallMap.h"

#include <cmath>

// Set up the sensor.
CRangeSensor::CRangeSensor( float aRelativeAngleDegrees,
                            float aMaximumRange )
    : mRelativeAngle( 0.0f ),
      mMaximumRange( aMaximumRange )
{
    const float pi = 3.14159265f;

    // Change degrees to radians.
    mRelativeAngle = aRelativeAngleDegrees * pi / 180.0f;
}

// Read the distance to a wall.
float CRangeSensor::Read( const CWallMap& arWallMap,
                          const CPose& arRobotPose,
                          int aRobotRadius ) const
{
    float sensorHeading =
        arRobotPose.mHeading + mRelativeAngle;

    Vec2D sensorPosition =
    {
        arRobotPose.mPosition.x +
            aRobotRadius * std::cos( sensorHeading ),

        arRobotPose.mPosition.y +
            aRobotRadius * std::sin( sensorHeading )
    };

    return arWallMap.MeasureWallRange( sensorPosition,
                                     sensorHeading,
                                     mMaximumRange );
}