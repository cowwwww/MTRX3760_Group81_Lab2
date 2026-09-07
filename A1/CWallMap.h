//-----------------------------------------------------------------------------
// CWallMap.h
//
// Stores the wall map.
// Also checks distance and collision.
//-----------------------------------------------------------------------------

#ifndef CWALLMAP_H
#define CWALLMAP_H

#include "CLoopReader.h"
#include "CRender.h"

#include <string>

class CWallMap
{
    public:
        CWallMap( const std::string& arWallFilename );

        bool IsReady() const;
        const CPose& GetWallStartPose() const;

        void Draw( CRender& arRender ) const;

        float MeasureWallRange( const Vec2D& arOrigin,
                                float aHeading,
                                float aMaximumRange ) const;

        bool CollidesWithWall( const Vec2D& arPosition, float aRadius ) const;

    private:
        bool RaySegmentIntersection( const Vec2D& arOrigin,
                                     const Vec2D& arDirection,
                                     const Vec2D& arA,
                                     const Vec2D& arB,
                                     float& arDistance ) const;

        float DistancePointToSegment( const Vec2D& arPoint,
                                      const Vec2D& arA,
                                      const Vec2D& arB ) const;

        CLoopReader mWalls;
        bool mReady;
};

#endif
