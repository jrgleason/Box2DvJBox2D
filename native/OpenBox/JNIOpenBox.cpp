#include "JNIOpenBox.h"

#undef JNIEXPORT
#define JNIEXPORT extern "C"

JNIEXPORT void JNICALL Java_org_gleason_openbox_JNIOpenBox_draw
    (JNIEnv *, jobject){
	LOGD("Inside draw");
	b2GLPolygonShape* es = new b2GLPolygonShape();
	es->Draw();
}
