//-----------------------------------------------------------------------------
// CWallFollower.cpp
//-----------------------------------------------------------------------------

#include "CWallFollower.h"
#include "CWallMap.h"

// Set up the wall follower.
CWallFollower::CWallFollower( CWallMap& arWallMap )
    : CRobot( arWallMap,
              "Wall follower",
              arWallMap.GetWallStartPose(),
              CRender::WALL_ROBOT,
              CRender::WALL_TRAIL ),
      mRightSensor( 90.0f, 300.0f ),
      mFrontRightSensor( 45.0f, 300.0f )
{
}

// Control the robot using the two sensors.
void CWallFollower::Control()
{
    const float forwardSpeed = 45.0f;
    const float gentleTurn = 8.0f;
    const float strongTurn = 25.0f;

    const float desiredDistance = 30.0f;
    const float distanceTolerance = 5.0f;
    const float frontCornerDistance = 70.0f;
    const float lostWallDistance = 180.0f;

    // Read both sensors.
    float rightDistance =
        mRightSensor.Read( GetWallMap(), GetPose(), GetRadius() );

    float frontRightDistance =
        mFrontRightSensor.Read( GetWallMap(), GetPose(), GetRadius() );

    // Turn left if a wall is in front.
    if( frontRightDistance < frontCornerDistance )
    {
        SetWheelSpeeds( forwardSpeed - strongTurn,
                        forwardSpeed + strongTurn );
    }

    // Turn right to find the wall again.
    else if( rightDistance > lostWallDistance )
    {
        SetWheelSpeeds( forwardSpeed + strongTurn,
                        forwardSpeed - strongTurn );
    }

    // Move closer to the wall.
    else if( rightDistance > desiredDistance + distanceTolerance )
    {
        SetWheelSpeeds( forwardSpeed + gentleTurn,
                        forwardSpeed - gentleTurn );
    }

    // Move away from the wall.
    else if( rightDistance < desiredDistance - distanceTolerance )
    {
        SetWheelSpeeds( forwardSpeed - gentleTurn,
                        forwardSpeed + gentleTurn );
    }

    // Move straight.
    else
    {
        SetWheelSpeeds( forwardSpeed, forwardSpeed );
    }
}