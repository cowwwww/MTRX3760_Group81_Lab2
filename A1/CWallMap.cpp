//-----------------------------------------------------------------------------
// CWallMap.cpp
//-----------------------------------------------------------------------------

#include "CWallMap.h"

#include <cmath>
#include <vector>

CWallMap::CWallMap( const std::string& arWallFilename )
    : mReady( false )
{
    mReady = mWalls.ReadFile( arWallFilename );
}

bool CWallMap::IsReady() const
{
    return mReady;
}

const CPose& CWallMap::GetWallStartPose() const
{
    return mWalls.GetStartPose();
}

void CWallMap::Draw( CRender& arRender ) const
{
    const float wallThickness = 3.0f;
    const std::vector<Vec2D>& vertices = mWalls.GetVertices();

    if( !vertices.empty() )
    {
        Vec2D previous = vertices.back();
        for( unsigned int i = 0; i < vertices.size(); ++i )
        {
            arRender.DrawLine( previous, vertices[i], wallThickness, CRender::WALL );
            previous = vertices[i];
        }
    }
}

float CWallMap::MeasureWallRange( const Vec2D& arOrigin,
                                float aHeading,
                                float aMaximumRange ) const
{
    Vec2D direction = { std::cos( aHeading ), std::sin( aHeading ) };
    float closestDistance = aMaximumRange;
    const std::vector<Vec2D>& vertices = mWalls.GetVertices();

    if( !vertices.empty() )
    {
        Vec2D previous = vertices.back();
        for( unsigned int i = 0; i < vertices.size(); ++i )
        {
            float distance = 0.0f;
            bool hit = RaySegmentIntersection( arOrigin, direction,
                                               previous, vertices[i], distance );
            if( hit && distance < closestDistance )
            {
                closestDistance = distance;
            }
            previous = vertices[i];
        }
    }

    return closestDistance;
}

bool CWallMap::CollidesWithWall( const Vec2D& arPosition, float aRadius ) const
{
    bool collision = false;
    const std::vector<Vec2D>& vertices = mWalls.GetVertices();

    if( !vertices.empty() )
    {
        Vec2D previous = vertices.back();
        for( unsigned int i = 0; i < vertices.size() && !collision; ++i )
        {
            float distance = DistancePointToSegment( arPosition, previous, vertices[i] );
            if( distance < aRadius )
            {
                collision = true;
            }
            previous = vertices[i];
        }
    }

    return collision;
}

bool CWallMap::RaySegmentIntersection( const Vec2D& arOrigin,
                                     const Vec2D& arDirection,
                                     const Vec2D& arA,
                                     const Vec2D& arB,
                                     float& arDistance ) const
{
    bool hit = false;

    Vec2D segment = { arB.x - arA.x, arB.y - arA.y };
    float cross = arDirection.x * segment.y - arDirection.y * segment.x;

    if( std::fabs( cross ) > 0.00001f )
    {
        Vec2D offset = { arA.x - arOrigin.x, arA.y - arOrigin.y };

        float rayDistance = ( offset.x * segment.y - offset.y * segment.x ) / cross;
        float segmentPosition = ( offset.x * arDirection.y - offset.y * arDirection.x ) / cross;

        if( rayDistance >= 0.0f && segmentPosition >= 0.0f && segmentPosition <= 1.0f )
        {
            arDistance = rayDistance;
            hit = true;
        }
    }

    return hit;
}

float CWallMap::DistancePointToSegment( const Vec2D& arPoint,
                                      const Vec2D& arA,
                                      const Vec2D& arB ) const
{
    float segmentX = arB.x - arA.x;
    float segmentY = arB.y - arA.y;
    float segmentLengthSquared = segmentX * segmentX + segmentY * segmentY;
    float position = 0.0f;

    if( segmentLengthSquared > 0.0f )
    {
        position = ( ( arPoint.x - arA.x ) * segmentX
                   + ( arPoint.y - arA.y ) * segmentY ) / segmentLengthSquared;
    }

    if( position < 0.0f )
    {
        position = 0.0f;
    }
    else if( position > 1.0f )
    {
        position = 1.0f;
    }

    float closestX = arA.x + position * segmentX;
    float closestY = arA.y + position * segmentY;
    float differenceX = arPoint.x - closestX;
    float differenceY = arPoint.y - closestY;

    return std::sqrt( differenceX * differenceX + differenceY * differenceY );
}
