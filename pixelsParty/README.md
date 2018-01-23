Pixel PArty
================

OpenFrameworks app (see http://openframeworks.cc/download/) 

Dependencies :
------------
   * ofxGui
   * ofxOsc
   * ofxSyphon / ofxSpout (on windows)

App
---
The app load images located in data/images/ 
Each picture is "divided" in 4 groups of pixels. When the app get an OSC message corresponding to one of those, pixels are "sprayed" gradually to display the entire image 
Output has been designed to publish a Syphon texture (to be mapped on a ceiling). For a window version, Spout will be used instead.
