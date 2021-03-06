/*
 * JNIBox2DBody.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: klm
 */

#include "jni/JNIBody.h"

#include "box2d.h"
#include "JNIBox2DWorld.h"
#include "android-log.h"

#include <jni.h>

#include <stdio.h>
//#include <iostream>
//using namespace std;

#undef JNIEXPORT
#define JNIEXPORT extern "C"


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    updateData
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nUpdateData
  (JNIEnv * env, jobject caller, jint id) {


	return;

	if(bodyList[id] ==NULL){
		return ;
	}

	jclass bodyClass = env->GetObjectClass(caller);
        LOGD("Calling the callback");
	jmethodID setValuesId = env->GetMethodID(bodyClass, "callbackSetData", "(FFFFFFF)V");

	b2Body *body = bodyList[id];
	float x = body->GetWorldCenter().x,
			y = body->GetWorldCenter().y,
			vx = body->GetLinearVelocity().x,
			vy = body->GetLinearVelocity().y,
			angle = body->GetAngle(),
			avel = body->GetAngularVelocity(),
			inertiaInv = 1.0f / body->GetInertia();

	env->CallVoidMethod(caller, setValuesId, x, y, vx, vy, angle, avel, inertiaInv);

}

JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nCreateShapeNo
  (JNIEnv *, jobject, jint ID, jfloat x, jfloat y, jfloat density) {
	LOGD("Starting Shape");
	if(bodyList[ID] == 0)
		return -1;

	b2Vec2 center;
	center.Set(x, y);
	b2Vec2 vertices[8];
	vertices[0].Set(0.0f, 4.0f);
	vertices[1].Set(1.0f, 4.0f);
	vertices[2].Set(1.5f, 5.0f);
	vertices[3].Set(1.0f, 6.0f);
	vertices[4].Set(0.0f, 6.0f);
	vertices[5].Set(-1.0f, 6.0f);
	vertices[6].Set(-1.5f, 5.0f);
	vertices[7].Set(-1.0f, 4.0f);
	int32 count = 8;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);
    LOGD("Count is %d", polygon.m_count);

	//pd.SetAsBox(width, height, center, angle);
	/*pd.filter.categoryBits = categoryBits;
	pd.filter.maskBits = mask;
	pd.filter.groupIndex = groupIndex;*/

//	cout << "NATIVE: Creating shape for body #" << ID << "\n" << flush;


	// find free shapelist spot and return id
	LOGD("Doing Fixture Checks");
	for(int i = 0 ; i < MAX_SHAPES ; i++) {
		if(shapeList[i] == 0) {
			LOGD("Creating Fixture");
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &polygon;
			fixtureDef.density = density;
			fixtureDef.friction = 0.3f;
			shapeList[i] = bodyList[ID]->CreateFixture(&fixtureDef);
			return i;
		}
	}
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nCreateBox
 * Signature: (FFFFFIII)I
 *
 *
 * 	native int nCreateBox(float width, float height, float x, float y,
			float density, int categoryBits, int maskBits, int groupIndex);
 *
 *
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nCreateBox
  (JNIEnv *, jobject, jint ID, jfloat width, jfloat height, jfloat x, jfloat y, jfloat density, jfloat angle) {
	LOGD("Starting Method");
	if(bodyList[ID] == 0)
		return -1;

	b2PolygonShape pd;

	b2Vec2 center;
	center.Set(x, y);

	pd.SetAsBox(width, height, center, angle);
	/*pd.filter.categoryBits = categoryBits;
	pd.filter.maskBits = mask;
	pd.filter.groupIndex = groupIndex;*/

//	cout << "NATIVE: Creating shape for body #" << ID << "\n" << flush;


	// find free shapelist spot and return id
	LOGD("Doing Fixture Checks");
	for(int i = 0 ; i < MAX_SHAPES ; i++) {
		if(shapeList[i] == 0) {
			LOGD("Creating Fixture");
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &pd;
			fixtureDef.density = density;
			fixtureDef.friction = 0.3f;
			shapeList[i] = bodyList[ID]->CreateFixture(&fixtureDef);
			return i;
		}
	}
}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nCreateShape
 * Signature: (I[F)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nCreateShape
  (JNIEnv * env, jobject caller, jint bodyID, jfloat density, jfloatArray jVList) {

	if(bodyList[bodyID] == 0)
		return -1;

//	cout << "HELLO FROM NATIVE\n" << flush;

	int len = env->GetArrayLength(jVList);
	float* vl = env->GetFloatArrayElements(jVList, false);


//	cout << "NATIVE: array of length " << len << "\n" << flush;

	b2PolygonShape pd;
        int lenV = len / 3;
        b2Vec2 vertices[lenV];
	// pd.vertexCount = len / 3;

	for(int i = 0 ; i < len/3 ; i++)
	{
		vertices[i].Set(vl[i * 3 + 0], vl[i * 3 + 1]);
	}
        pd.Set(&vertices[0],lenV);


	// release buffer but don't copy back
	env->ReleaseFloatArrayElements(jVList, vl, JNI_ABORT);


	b2Fixture* shape = bodyList[bodyID]->CreateFixture(&pd, density);

	for(int i = 0 ; i < MAX_SHAPES ; i++) {
		if(shapeList[i] == 0) {
			shapeList[i] = shape;
			return i;
		}

	}


	char txt[100];
	sprintf(txt, "Max number shapes of %d reached (JNIBox2DBody)", MAX_SHAPES);
	throwExc(env, txt);
	return -1;
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nAssociateJNIObject
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nAssociateJNIObject
  (JNIEnv * env, jobject caller, jint id) {

	if(id < 0 || id >= MAX_BODIES)
		return;

	if(bodyList[id] == 0)
		return;

	jobject gref = MakeGlobalRef(env, caller);
	// gref is now JNIBOx2DBody object
	bodyList[id]->SetUserData(gref);

}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nApplyForce
 * Signature: (IFFFF)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nApplyForce
  (JNIEnv * env, jobject caller, jint ID, jfloat fx, jfloat fy, jfloat wx, jfloat wy) {

	if(ID < 0 || ID >= MAX_BODIES) {
		throwExc(env, "ID #%d out of bounds");
		return;
	}

	// make sure body isn't dead
	if(bodyList[ID] == 0)
		return;

	b2Vec2 force, point;
	force.Set(fx, fy);
	point.Set(wx, wy);
	bodyList[ID]->ApplyForce(force, point, false);

}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nApplyTorque
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nApplyTorque
  (JNIEnv * env, jobject, jint ID, jfloat torque) {

	if(ID < 0 || ID >= MAX_BODIES) {
		throwExc(env, "ID #%d out of bounds");
		return;
	}
	if(bodyList[ID] == 0)
		return;

	bodyList[ID]->ApplyTorque(torque, false);

	if(torque == 0.5f)
	{
//		cout << " body mass: " << bodyList[ID]->GetMass() << " ... body torque .. " << bodyList[ID]->GetAngularVelocity() << "\n" << flush;
	}
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nSetMassFromShapes
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nSetMassFromShapes
  (JNIEnv * env, jobject, jint ID) {

	if(ID < 0 || ID >= MAX_BODIES) {
		throwExc(env, "ID #%d out of bounds");
		return;
	}
	if(bodyList[ID] == 0)
		return;

	bodyList[ID]->ResetMassData();
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nSetDamping
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nSetDamping
  (JNIEnv * env, jobject, jint ID, jfloat liDa, jfloat anDa) {
	if(ID < 0 || ID >= MAX_BODIES) {
		throwExc(env, "ID #%d out of bounds");
		return;
	}
	if(bodyList[ID] == 0)
		return;

	bodyList[ID]->SetLinearDamping(liDa);
	bodyList[ID]->SetAngularDamping(anDa);
}



/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nRefilter
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nRefilter
  (JNIEnv *, jobject, jint ID, jint catergory, jint mask, jint group) {

	if(bodyList[ID] == 0)
		return;

	b2Fixture* s = bodyList[ID]->GetFixtureList();

	b2Filter filter;
	filter.categoryBits = catergory;
	filter.maskBits = mask;
	filter.groupIndex = group;

	s->SetFilterData(filter);
	s->Refilter();

}


/*
 *
 *
 * we are taking a FiterData object as parameter, which will
 * be filled with data from the filterdata of the corresponding shape.
 *
 *
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nGetFilterData
 * Signature: (Lorg/jbox2d/collision/FilterData;)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nGetFilterData
  (JNIEnv * env, jobject, jint bodyID, jobject fd) {

	if(bodyList[bodyID] == 0)
		return;
	/*
	 * public int categoryBits;
	public int maskBits;
	public int groupIndex;

	jclass bodyClass = env->GetObjectClass(caller);
	jmethodID setValuesId = env->GetMethodID(bodyClass, "setData", "(FFFFFFF)V");
	env->CallVoidMethod(caller, setValuesId, x, y, vx, vy, angle, avel, inertiaInv);
	*/

	b2Filter shapeFD = bodyList[bodyID]->GetFixtureList()->GetFilterData();

	jclass fdClass = env->GetObjectClass(fd);
	jfieldID catField = env->GetFieldID(fdClass, "categoryBits", "I");
	jfieldID maskField = env->GetFieldID(fdClass, "maskBits", "I");
	jfieldID groupField = env->GetFieldID(fdClass, "groupIndex", "I");

	env->SetIntField(fd, catField, shapeFD.categoryBits);
	env->SetIntField(fd, maskField, shapeFD.maskBits);
	env->SetIntField(fd, groupField, shapeFD.groupIndex);

}


/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nDestroyShape
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nDestroyShape
  (JNIEnv * env, jobject caller, jint bodyID, jint shapeID) {

	if(bodyID < 0 || bodyID >= MAX_BODIES - 1) {
		throwExc(env, "detroying shape: body ID invalid");
		return;
	}
	if(shapeID < 0 || shapeID >= MAX_SHAPES - 1) {
		throwExc(env, "detroying shape: shape ID invalid");
		return;
	}

	if(shapeList[shapeID] == 0)
		return;
	if(bodyList[bodyID] == 0)
		return;

	// the JNIBox2dShape object is stored in userdata as global ref.
	DeleteGlobalRef(env, (jobject)shapeList[shapeID]->GetUserData());

	bodyList[bodyID]->DestroyFixture(shapeList[shapeID]);

	// free shape spot
	shapeList[shapeID] = 0;
}


/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody
 * Method:    nSetPosition
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DBody_nSetPosition
  (JNIEnv *, jobject, jint id, jfloat x, jfloat y) {

	if(bodyList[id] == 0)
		return;

	b2Vec2 pos;
	pos.Set(x, y);
	bodyList[id]->SetTransform(pos, bodyList[id]->GetAngle());



}

