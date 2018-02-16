
Thunderboard Sense Connected Motion

This example demonstrates how one can use a very simple radio protocol
to communicate between nodes where lost packets is of no concern. In
this demonstration, each node has a different color, in which it will
light up when it detects that it is in motion. The active node
transmits its state to nearby nodes, which also light up in the same
color. When all nodes are stationary, a  master  node coordinates a
green light fading from board to board.


Configuration

For the connectedMotion demo to work with more than one board, it
needs to be configured. If you hold both push buttons pressed while
resetting the device, it will enter a configuration mode. This is
indicated by three bright white blinks of the RGB LEDs. In this mode,
you can cycle through three colors using the right button: blue, pink
and turquoise. To select a color, press the left button. The selection
is confirmed by three blinks in the selected color.  The blue node is
the master which controls the fading green light, so one and only one
of the boards should be configured to be blue.

