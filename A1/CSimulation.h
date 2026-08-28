//-----------------------------------------------------------------------------
// CSimulation.h
//
// Top-level owner for the A1 simulation.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CRender.h"
#include "CWallFollower.h"
#include "CWallMap.h"


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
        bool mSummaryPrinted;
};

#endif
