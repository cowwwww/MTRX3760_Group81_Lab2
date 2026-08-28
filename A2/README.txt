A2 - Wall Follower + Line Follower

With raylib installed by apt:
  g++ -std=c++11 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
      main.cpp CSimulation.cpp CWallFollower.cpp CLineFollower.cpp CRobot.cpp \
      CRangeSensor.cpp CLineSensor.cpp CWallMap.cpp CLoopReader.cpp CRender.cpp \
      -lraylib -o robot_simulator
  ./robot_simulator

On a lab machine with raylib in $HOME/raylib, add:
  -I$HOME/raylib/include -L$HOME/raylib/lib

Both robots update in the same program and leave permanent trails. The final
view stays open after both robots finish so the required screenshot can be taken.
