package org.gleason.openbox;

public class JNIOpenBox {
	public native void draw();
	static{
		System.loadLibrary("openbox");
		System.loadLibrary("box2D");
	}
}
