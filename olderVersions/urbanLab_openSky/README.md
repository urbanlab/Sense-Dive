Open Sky
========

OpenFrameworks app (see http://openframeworks.cc/download/) 

Dependencies :
------------
   * ofxGui
   * ofxBox2D
   * ofxHapPlayer (libavformat branch)
   * ofxOsc
   * ofxSyphon / ofxSpout (on windows)

App
---
The app consists in a small physic simulation. 
Elements are loaded at startup (/data/mediasX/). When an OSC input is received, an attraction force is generated at the corresponding position.

Keys
----
space : display GUI and debug infos
'R'   : load another set of data
