Box2DvJBox2D
============

This is a tool to compair performance/speed of Box2D (native) and JBox2D (Java) on Android. Based on https://code.google.com/p/android-opengl-box2d-basics/


Use
===

./loadNewLibs.sh
android update project -p ./ -t <target>
ant debug
ant installd

ISSUES
======

JBox has been neglected, should change namespaces
