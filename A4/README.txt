A4 - ROS 2 Jazzy Pluginlib extension

Do the official ROS 2 Jazzy C++ tutorials first. In the Pluginlib tutorial:

1. Replace polygon_plugins/src/polygon_plugins.cpp with this folder's
   polygon_plugins.cpp.
2. Add the House class entry from plugins.xml to the tutorial plugins.xml.
3. For the required test, use the supplied area_node.cpp or add equivalent
   House loading to your tutorial area_node.cpp.
4. Build and source the workspace, then run area_node.

For side_length = 10.0, expected areas are approximately:
  Square area:   100.00
  Triangle area: 43.30
  House area:    143.30

The Lab 2 handout specifically requires polygon_plugins.cpp in the final code
submission. The XML and test node are included here to make the test reproducible.
