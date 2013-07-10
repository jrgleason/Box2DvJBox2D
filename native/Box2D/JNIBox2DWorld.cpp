

/*
 *
 * JNI Box2D binder For RoboTanks
 * Kristian Lein-Mathisen 2009
 *
 */

#include "jni/JNIWorld.h"
#include "JNIBox2DWorld.h"
#include "box2d.h"
#include "JNIRefs.h"
#include <jni.h>
#include "android-log.h"

//#include <iostream>
//using namespace std;

// we may be missing something here ... but JNIEXPORT is empty so this is so much more convenient!
#undef JNIEXPORT
#define JNIEXPORT extern "C"






void throwExc(JNIEnv* env, const char* msg) {
	env->ThrowNew(env->FindClass("java/lang/Exception"), msg);
}


// Global World variables


b2World* world = NULL;

b2Body* bodyList[MAX_BODIES];

//----------

b2Fixture* shapeList[MAX_SHAPES];


b2Joint* jointList[MAX_JOINTS];






JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nTestLib
  (JNIEnv *, jobject, jint k)  {

	return k * 2;
	

}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    n_createWorld
 * Signature: (FFFFFFZ)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateWorld
  (JNIEnv * env, jobject caller, jfloat x1, jfloat y1, jfloat x2, jfloat y2, jfloat gx, jfloat gy, jboolean canSleep) {

	for(int i = 0 ; i < MAX_BODIES ; i++) {
		bodyList[i] = 0;
	}

	for(int i = 0 ; i < MAX_SHAPES ; i++)
		shapeList[i] = 0;

	for(int i = 0 ; i < MAX_JOINTS ; i++)
		jointList[i] = 0;

	for(int i = 0 ; i < MAX_GLOBAL_REFS ; i++)
		globalRef[i] = 0;


    b2AABB aabb;
    aabb.lowerBound.Set(x1, y1);
    aabb.upperBound.Set(x2, y2);

    LOGD("Lower Bound %f,%f Upper Bound %f, %f", x1, y1, x2, y2);

    b2Vec2 gravity;
    gravity.Set(gx, gy);
    LOGD("Gravity set to %f, %f", gx, gy);

    //TODO: How do I do aabb now...
    // world = new b2World(aabb, gravity, canSleep);
    world = new b2World(gravity);
    world->SetAllowSleeping(canSleep);
    b2Vec2 origin;
    origin.Set(0, 0);
    world->ShiftOrigin(origin);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    shapeList[0] = groundBody->CreateFixture(&groundBox, 0.0f);
    // ground body
    // TODO: Not sure here....
    bodyList[0] = groundBody;
}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    step
 * Signature: (FI)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_step
  (JNIEnv *, jobject, jfloat dt, jint iterations) {
	//LOGD("Stepping into...");
	if(world == NULL){
		LOGD("Yup that is the issue...");
	}
	else{
	    LOGD("Gravity is %f", world->GetGravity().y);
	}
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
			b2Vec2 position = b->GetPosition();
			float32 angle = b->GetAngle();
			float32 yVelocity = b->GetLinearVelocity().y;
			//LOGD("Before %4.2f %4.2f %4.2f %f \n", position.x, position.y, angle, yVelocity);
	}

	//world->Step(dt, iterations, iterations);
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(dt, velocityIterations, positionIterations);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		b2Vec2 position = b->GetPosition();
		float32 angle = b->GetAngle();
		float32 yVelocity = b->GetLinearVelocity().y;
		//LOGD("Stepping %4.2f %4.2f %4.2f %f \n", position.x, position.y, angle, yVelocity);
	}
}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroy
  (JNIEnv * env, jobject) {

	DeleteAllGlobalRefs(env);

//	cout << "NATIVE goodbye world\n" << flush;


	delete world;
	world = 0;

}

/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nCreateBody
 * Signature: (FF)I
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateBody
  (JNIEnv *, jobject, jfloat x, jfloat y) {
    LOGD("Creating Body");
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
//	bd.fixedRotation = true;
	bd.position.Set(x, y);
        bd.allowSleep = true;
        bd.awake = true;
	// look for free spot and insert.
	for(int i = 0 ; i < MAX_BODIES ; i++) {
		if(bodyList[i] == 0) {
			bodyList[i] = world->CreateBody(&bd);
			bodyList[i]->SetUserData(0);
			return i;
		}
	}

	printf("no free body-slot!");

	return 0;

}


/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroyBody
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroyBody
  (JNIEnv * env, jobject caller, jint bodyID) {

	if(bodyID < 0 || bodyID >= MAX_BODIES) {
		throwExc(env, "destroy body ID outta range.");
		return ;
	}

	world->DestroyBody(bodyList[bodyID]);
	// free spot
	bodyList[bodyID] = 0;


}


int findId(b2Body* body)
{
	for(int i = 0 ; i <= MAX_BODIES ; i++) {
		if(body == bodyList[i]) {
			return i;
		}
	}
//	cout << "NATIVE: did not find body " << body << "\n" << flush;
	return -1;
}

jclass jniBodyClass = 0;
jmethodID callbackSetData = 0;


void updateBodyData(JNIEnv * env, b2Body* body) {


	if(jniBodyClass == 0) {
		jniBodyClass = env->FindClass("com/kristianlm/robotanks/box2dbridge/jnibox2d/JNIBox2DBody");//env->GetObjectClass(caller);
		if(jniBodyClass == 0) {
			throwExc(env, "com/kristianlm/robotanks/box2dbridge/jnibox2d/JNIBox2DBody not found");
			return;
		}

//		cout << "class = " << jniBodyClass << "\n" << flush;

                LOGD("Callback updateBodyData");
		callbackSetData = env->GetMethodID(jniBodyClass, "callbackSetData", "(FFFFFFF)V");
		if(callbackSetData == 0) {
			throwExc(env, "callbackSetData method ID (FFFFFFF)V not found");
			return;
		}
	}

	//b2Body *body = bodyList[id];
	float x = body->GetWorldCenter().x,
			y = body->GetWorldCenter().y,
			vx = body->GetLinearVelocity().x,
			vy = body->GetLinearVelocity().y,
			angle = body->GetAngle(),
			avel = body->GetAngularVelocity(),
			inertiaInv = 1.0f / body->GetInertia();
        
        //LOGD("Body info is %f %f %f %f %f %f %f",x,y,vx,vy,angle,avel,inertiaInv);

	// The JNIBody reference is made global and stored for all body userdata.
	if(body->GetUserData() != bodyList[0]->GetUserData())
		if(body->GetUserData() != 0){
	          //LOGD("Calling the callback from update body");
                  env->CallVoidMethod((jobject)body->GetUserData(), callbackSetData, x, y, vx, vy, angle, avel, inertiaInv);     
                }
//		else
//			cout << "dropped a body (no userdata) \n" << flush;

}
/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nBodyQuery
 * Signature: (FFFFI[I)I
 */

int starting = false;
jmethodID g_mid;
jobject g_obj;
jclass g_clazz;
JavaVM * g_vm;

class MyQueryCallback : public b2QueryCallback {
  public:
      // std::vector<b2Body*> foundBodies;
      bool ReportFixture(b2Fixture* fixture) {
          printf("In Callback");
          JNIEnv * g_env;
          int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
          b2Body* body = fixture->GetBody();
          float x = body->GetWorldCenter().x,
                        y = body->GetWorldCenter().y,
                        vx = body->GetLinearVelocity().x,
                        vy = body->GetLinearVelocity().y,
                        angle = body->GetAngle(),
                        avel = body->GetAngularVelocity(),
                        inertiaInv = 1.0f / body->GetInertia();
          LOGD("Calling Callback from Report Fixture1");
          g_env->CallVoidMethod((jobject)body->GetUserData(), callbackSetData, x, y, vx, vy, angle, avel, inertiaInv);
          // foundBodies.push_back( body ); 
          // if(!body->IsStatic() || !body->IsJNIUpdated()) {
            // updateBodyData(env, body);
            // env->SetObjectArrayElement(array, i, JNIShape);
          // }            
          jobject JNIShape = (jobject) fixture->GetUserData();
          return true;//keep going to find all fixtures in the query area
      }
 };



JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nShapeQuery
  (JNIEnv *env, jobject obj, jfloat x1, jfloat y1, jfloat x2, jfloat y2, jint maxCount, jobjectArray array) {
        printf("Starting Shape Query");
        MyQueryCallback queryCallback;
        env->GetJavaVM(&g_vm);
        g_obj = env->NewGlobalRef(obj);
        if(g_clazz == 0) {
          g_clazz = env->GetObjectClass(g_obj);
        } 
        LOGD("Calling Callback nShapeQuery");
        callbackSetData = env->GetMethodID(g_clazz, "callbackSetData", "(FFFFFFF)V");
        if(callbackSetData == 0) {
          throwExc(env, "callbackSetData method ID (FFFFFFF)V not found");
          return;
        }
	b2AABB aabb;
	aabb.lowerBound.Set(x1, y1);
	aabb.upperBound.Set(x2, y2);

	// list of shapes from query
	// get shape list
	world->QueryAABB(&queryCallback, aabb);
}

/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nRaycastOne
 * Signature: (FFFFLorg/jbox2d/common/RaycastResult;ZLjava/lang/Object;)I
 */
class MyRayCastCallback : public b2RayCastCallback
{
  public:
  MyRayCastCallback()
  {
    m_fixture = NULL;
  }
  float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
  const b2Vec2& normal, float32 fraction)
  {
    printf("Raycast Callback");
    m_fixture = fixture;
    m_point = point;
    m_normal = normal;
    m_fraction = fraction;
    return fraction;
  }
  b2Fixture* m_fixture;
  b2Vec2 m_point;
  b2Vec2 m_normal;
  float32 m_fraction;
};
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nRaycastOne
  (JNIEnv * env, jobject caller, jfloat p1x, jfloat p1y, jfloat p2x, jfloat p2y , jobject raycastRes, jboolean solidShapes, jobject userData) {
        printf("Calling Raycast");
        MyRayCastCallback callback;
        b2Vec2 point1(p1x, p1y);
        b2Vec2 point2(p2x, p2y);
	world->RayCast(&callback, point1, point2);
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nCreateRevoluteJoint
 * Signature: (IIFF)V
 */
JNIEXPORT jint JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nCreateRevoluteJoint
  (JNIEnv *, jobject, jint id1, jint id2, jfloat aX, jfloat aY) {
	b2RevoluteJointDef rj;

	rj.enableLimit = false;
	rj.enableMotor = false;

	b2Vec2 anchor; anchor.Set(aX, aY);
	rj.Initialize(bodyList[id1], bodyList[id2], anchor);


	// find free spot and return its ID
	for(int i = 0 ; i < MAX_JOINTS ; i++) {
		if(jointList[i] == 0) {
			jointList[i] = world->CreateJoint(&rj);
			return i;
		}
	}

	return -1;
}


/*
 * Class:     com_kristianlm_superelevation_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nDestroyJoint
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nDestroyJoint
  (JNIEnv *, jobject, jint jointID) {

	if(jointID < 0 && jointID >= MAX_JOINTS)
		return;

	printf("NATIVE destroying joint #%d (%X)\n", jointID, jointList[jointID]);

	if(jointList[jointID] == 0)
		return;

	world->DestroyJoint(jointList[jointID]);

	jointList[jointID] = 0;

	printf("destroying joint ok\n");
	fflush(stdout);

}


/*
 * Class:     com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld
 * Method:    nUpdateAllPositions
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_kristianlm_robotanks_box2dbridge_jnibox2d_JNIBox2DWorld_nUpdateAllPositions
  (JNIEnv * env, jobject) {
        LOGD("Updating all positions");
        for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
        {
           if(b != 0){
             if(b->GetUserData() != 0){
               updateBodyData(env, b);
             }
           }
        }
        /*
	for(int i = 0 ; i < MAX_BODIES ; i++) {
		// b2Body* body = bodyList[i];
		b2Body body = bodylist[i];
		// valid body pointer
		if(body != 0) {
                        LOGD("Body %d is not 0", i);
			// check if we have userdata (should be pointer to JNIBox2DBody global ref.
			if(body->GetUserData() != 0){
                                LOGD("Body %d has user data", i);
				updateBodyData(env, &body);
                        }
		}
	}
        */
}
