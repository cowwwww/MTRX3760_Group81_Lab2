//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"

#include "CLineFollower.h"
#include "CWallFollower.h"

#include <cstdlib>
#include <iostream>

CSimulation::CSimulation()
    : mWallMap( "SimpleWalls.map", "SimpleLine.map" ),
      mRender(),
      mSummaryPrinted( false )
{
    const unsigned int randomSeed = 3760;
    std::srand( randomSeed );
    CreateRobots();
}

CSimulation::~CSimulation()
{
    for( unsigned int i = 0; i < mRobots.size(); ++i )
    {
        delete mRobots[i];
    }
}

void CSimulation::Run()
{
    if( !mWallMap.IsReady() )
    {
        std::cout << "Simulation could not load the maps." << std::endl;
    }
    else
    {
        while( !mRender.WindowShouldClose() )
        {
            if( !AllRobotsStopped() )
            {
                UpdateRobots();
            }
            else if( !mSummaryPrinted )
            {
                PrintSummary();
            }

            Draw();
        }
    }

    mRender.CloseWindow();
}

void CSimulation::CreateRobots()
{
    const int robotsPerType = 20;

    for( int i = 0; i < robotsPerType; ++i )
    {
        mRobots.push_back( new CWallFollower( mWallMap ) );
        mRobots.push_back( new CLineFollower( mWallMap ) );
    }
}

void CSimulation::UpdateRobots()
{
    const int updatesPerFrame = 8;
    const int maximumUpdates = 2200;

    for( int step = 0; step < updatesPerFrame; ++step )
    {
        for( unsigned int i = 0; i < mRobots.size(); ++i )
        {
            if( !mRobots[i]->HasCompletedLap()
                && mRobots[i]->GetUpdateCount() < maximumUpdates )
            {
                mRobots[i]->Update();
            }
        }
    }
}

void CSimulation::Draw()
{
    mRender.BeginDrawing();
    mWallMap.Draw( mRender );

    for( unsigned int i = 0; i < mRobots.size(); ++i )
    {
        mRobots[i]->Draw( mRender );
    }

    mRender.EndDrawing();
}

bool CSimulation::AllRobotsStopped() const
{
    const int maximumUpdates = 2200;
    bool allStopped = true;

    for( unsigned int i = 0; i < mRobots.size() && allStopped; ++i )
    {
        bool stopped = mRobots[i]->HasCompletedLap()
                    || mRobots[i]->GetUpdateCount() >= maximumUpdates;
        if( !stopped )
        {
            allStopped = false;
        }
    }

    return allStopped;
}

void CSimulation::PrintSummary()
{
    int completed = 0;
    for( unsigned int i = 0; i < mRobots.size(); ++i )
    {
        if( mRobots[i]->HasCompletedLap() )
        {
            ++completed;
        }
    }

    std::cout << std::endl
              << "A5 noise simulation: " << completed
              << " of " << mRobots.size() << " robots completed a lap."
              << std::endl
              << "Close the window after taking the final screenshot."
              << std::endl;

    mSummaryPrinted = true;
}
