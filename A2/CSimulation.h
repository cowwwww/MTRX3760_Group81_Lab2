//-----------------------------------------------------------------------------
// CSimulation.h
//
// Top-level owner for the A2 simulation containing both robot types.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CLineFollower.h"
#include "CRender.h"
#include "CWallFollower.h"
#include "CWallMap.h"

#include <vector>

class CSimulation
{
    public:
        CSimulation();
        void Run();

    private:
        void UpdateRobots();
        void Draw();
        bool AllRobotsStopped() const;
        void PrintSummary();

        CWallMap mWallMap;
        CRender mRender;
        CWallFollower mWallFollower;
        CLineFollower mLineFollower;
        std::vector<CRobot*> mRobots;
        bool mSummaryPrinted;
};

#endif
