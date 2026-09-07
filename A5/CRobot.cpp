//-----------------------------------------------------------------------------
// CRobot.cpp
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CWallMap.h"

#include <cmath>
#include <cstdlib>

CRobot::CRobot( CWallMap& arWallMap,
                const std::string& arName,
                const CPose& arStartPose,
                CRender::EStyle aRobotStyle,
                CRender::EStyle aTrailStyle )
    : mrWallMap( arWallMap ),
      mName( arName ),
      mStartPose( arStartPose ),
      mPose( arStartPose ),
      mRadius( 15 ),
      mWheelSeparation( 30.0f ),
      mTimeStep( 0.04f ),
      mMaximumWheelSpeed( 80.0f ),
      mStartPositionNoise( 2.0f ),
      mStartHeadingNoise( 0.03f ),
      mWheelDistanceNoise( 0.06f ),
      mLeftWheelSpeed( 0.0f ),
      mRightWheelSpeed( 0.0f ),
      mRobotStyle( aRobotStyle ),
      mTrailStyle( aTrailStyle ),
      mUpdateCount( 0 ),
      mHasLeftStart( false ),
      mCompletedLap( false )
{
    ApplyStartingNoise();
    mTrail.push_back( mPose.mPosition );
}

CRobot::~CRobot()
{
}

void CRobot::Update()
{
    if( !mCompletedLap )
    {
        ++mUpdateCount;
        Control();
        Move();
        CheckLapCompletion();
        mTrail.push_back( mPose.mPosition );
    }
}

void CRobot::Draw( CRender& arRender ) const
{
    const float trailThickness = 1.0f;
    const float headingThickness = 2.0f;

    for( unsigned int i = 1; i < mTrail.size(); ++i )
    {
        arRender.DrawLine( mTrail[i - 1], mTrail[i], trailThickness, mTrailStyle );
    }

    arRender.DrawCircle( mPose.mPosition, mRadius, mRobotStyle );

    Vec2D headingEnd =
    {
        mPose.mPosition.x + float( mRadius ) * std::cos( mPose.mHeading ),
        mPose.mPosition.y + float( mRadius ) * std::sin( mPose.mHeading )
    };
    arRender.DrawLine( mPose.mPosition, headingEnd, headingThickness, CRender::SENSOR );
}

bool CRobot::HasCompletedLap() const
{
    return mCompletedLap;
}

int CRobot::GetUpdateCount() const
{
    return mUpdateCount;
}

const std::string& CRobot::GetName() const
{
    return mName;
}

const CPose& CRobot::GetPose() const
{
    return mPose;
}

CWallMap& CRobot::GetWallMap()
{
    return mrWallMap;
}

int CRobot::GetRadius() const
{
    return mRadius;
}

void CRobot::SetWheelSpeeds( float aLeftSpeed, float aRightSpeed )
{
    if( aLeftSpeed > mMaximumWheelSpeed )
    {
        aLeftSpeed = mMaximumWheelSpeed;
    }
    else if( aLeftSpeed < -mMaximumWheelSpeed )
    {
        aLeftSpeed = -mMaximumWheelSpeed;
    }

    if( aRightSpeed > mMaximumWheelSpeed )
    {
        aRightSpeed = mMaximumWheelSpeed;
    }
    else if( aRightSpeed < -mMaximumWheelSpeed )
    {
        aRightSpeed = -mMaximumWheelSpeed;
    }

    mLeftWheelSpeed = aLeftSpeed;
    mRightWheelSpeed = aRightSpeed;
}

void CRobot::ApplyStartingNoise()
{
    mPose.mPosition.x += RandomOffset( mStartPositionNoise );
    mPose.mPosition.y += RandomOffset( mStartPositionNoise );
    mPose.mHeading += RandomOffset( mStartHeadingNoise );
    mStartPose = mPose;
}

float CRobot::RandomOffset( float aMagnitude ) const
{
    float unitValue = float( std::rand() ) / float( RAND_MAX );
    return ( 2.0f * unitValue - 1.0f ) * aMagnitude;
}

void CRobot::Move()
{
    // Add noise to wheel travel.
    float leftDistance = mLeftWheelSpeed * mTimeStep + RandomOffset( mWheelDistanceNoise );
    float rightDistance = mRightWheelSpeed * mTimeStep + RandomOffset( mWheelDistanceNoise );

    float linearDistance = ( leftDistance + rightDistance ) / 2.0f;
    float headingChange = ( leftDistance - rightDistance ) / mWheelSeparation;

    CPose nextPose = mPose;
    nextPose.mHeading += headingChange;
    nextPose.mPosition.x += linearDistance * std::cos( nextPose.mHeading );
    nextPose.mPosition.y += linearDistance * std::sin( nextPose.mHeading );

    if( mrWallMap.CollidesWithWall( nextPose.mPosition, float( mRadius ) ) )
    {
        // Collisions are not counted for A5, but the wall still remains solid.
        mPose.mHeading = nextPose.mHeading;
    }
    else
    {
        mPose = nextPose;
    }
}

void CRobot::CheckLapCompletion()
{
    const float leaveStartDistance = 80.0f;
    const float finishDistance = 25.0f;
    const int minimumUpdates = 300;

    float distance = DistanceFromStart();
    if( distance > leaveStartDistance )
    {
        mHasLeftStart = true;
    }

    if( mHasLeftStart && distance < finishDistance && mUpdateCount > minimumUpdates )
    {
        mCompletedLap = true;
    }
}

float CRobot::DistanceFromStart() const
{
    float differenceX = mPose.mPosition.x - mStartPose.mPosition.x;
    float differenceY = mPose.mPosition.y - mStartPose.mPosition.y;
    return std::sqrt( differenceX * differenceX + differenceY * differenceY );
}
