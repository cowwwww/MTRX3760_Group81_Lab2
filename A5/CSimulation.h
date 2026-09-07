//-----------------------------------------------------------------------------
// CSimulation.h
//
// Main simulation class for A5.
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
        CSimulation( const CSimulation& ) = delete;
        CSimulation& operator=( const CSimulation& ) = delete;

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
