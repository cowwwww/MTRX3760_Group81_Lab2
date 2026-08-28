//-----------------------------------------------------------------------------
// CLineFollower.cpp
//-----------------------------------------------------------------------------

#include "CLineFollower.h"
#include "CWallMap.h"

CLineFollower::CLineFollower( CWallMap& arWallMap )
    : CRobot( arWallMap,
              "Line follower",
              arWallMap.GetLineStartPose(),
              CRender::LINE_ROBOT,
              CRender::LINE_TRAIL ),
      mLineSensor( 12.0f, 0.0f ),
      mSideSensor( 12.0f, 6.0f )
{
}

void CLineFollower::Control()
{
    // The first sensor normally sits over the line. The second is to its right.
    // This gives three useful cases: centred, line to the right, or line lost
    // to the left. The controller turns according to those sensor states.
    const float forwardSpeed = 30.0f;
    const float turnAmount = 30.0f;

    bool lineDetected = mLineSensor.Read( GetWallMap(), GetPose() );
    bool sideDetected = mSideSensor.Read( GetWallMap(), GetPose() );

    if( lineDetected && !sideDetected )
    {
        SetWheelSpeeds( forwardSpeed, forwardSpeed );
    }
    else if( sideDetected )
    {
        SetWheelSpeeds( forwardSpeed + turnAmount, forwardSpeed - turnAmount );
    }
    else
    {
        SetWheelSpeeds( forwardSpeed - turnAmount, forwardSpeed + turnAmount );
    }
}
