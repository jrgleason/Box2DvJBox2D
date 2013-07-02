/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld */

#ifndef _Included_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
#define _Included_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nTestLib
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nTestLib
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nCreateWorld
 * Signature: (FFFFFFZ)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateWorld
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jboolean);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nShapeQuery
 * Signature: (FFFFI[Ljava/lang/Object;)I
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nShapeQuery
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jint, jobjectArray);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    step
 * Signature: (FI)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_step
  (JNIEnv *, jobject, jfloat, jint);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroy
  (JNIEnv *, jobject);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nCreateBody
 * Signature: (FF)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateBody
  (JNIEnv *, jobject, jfloat, jfloat);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroyBody
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroyBody
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nCreateRevoluteJoint
 * Signature: (IIFF)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateRevoluteJoint
  (JNIEnv *, jobject, jint, jint, jfloat, jfloat);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroyJoint
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroyJoint
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nRaycastOne
 * Signature: (FFFFLorg/jbox2d/common/RaycastResult;ZLjava/lang/Object;)Lcom/kristianlm/robotanks/box2dbridge/jnibox2d/JNIBox2DShape;
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nRaycastOne
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jobject, jboolean, jobject);

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nUpdateAllPositions
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nUpdateAllPositions
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif