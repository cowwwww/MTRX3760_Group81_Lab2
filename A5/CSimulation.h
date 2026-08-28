//-----------------------------------------------------------------------------
// CSimulation.h
//
// A5 simulation: 20 wall followers and 20 line followers with random noise.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CRender.h"
#include "CRobot.h"
#include "CWallMap.h"

#include <vector>

class CSimulation
{
    public:
        CSimulation();
        ~CSimulation();

        void Run();

    private:
        void CreateRobots();
        void UpdateRobots();
        void Draw();
        bool AllRobotsStopped() const;
        void PrintSummary();

        CWallMap mWallMap;
        CRender mRender;
        std::vector<CRobot*> mRobots;
        bool mSummaryPrinted;
};

#endif
