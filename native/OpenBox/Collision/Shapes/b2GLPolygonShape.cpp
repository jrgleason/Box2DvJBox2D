#include "b2GLPolygonShape.h"

void b2GLPolygonShape::Draw(){
	LOGD("in Draw");
	if(world == NULL){
		LOGD("World is not set for some reason");
	}
	else{
		LOGD("World is set");
	    LOGD("Gravity is.... %f,%f", world->GetGravity().x, world->GetGravity().y);

		for ( b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		{
			LOGD("Body found");
		  for( b2Fixture* f = b->GetFixtureList();f;f=f->GetNext()){
			  LOGD("Fixture found");
			  if(f->GetType()==2){
				  b2PolygonShape* ps = (b2PolygonShape*) f->GetShape();
				  LOGD("Trying to draw");
				  this->Draw(ps, b);
	//			  ps.draw();
			  }
			  f->GetShape();
		  }
		}
	}
}

void b2GLPolygonShape::Draw(b2PolygonShape* s, b2Body* b){
	b2Vec2 center = b->GetPosition();
	LOGD("Count is... %d, Center is %f, %f", s->m_count, center.x, center.y);
	GLfloat c[s->m_count*2];
	int i=0;
	int i2=0;
//	for ( b2Vec2* v = s->m_vertices; v; v = v->GetNext())
//	{
    for(i=0;i < s->m_count;i++){
    	b2Vec2 v = s->m_vertices[i];
		float x = center.x + v.x;
		float y = center.y + v.y;
		LOGD("Vertex is... %f, %f", x, y);
		c[i2++] =  x;
		c[i2++] =  y;
	}
	glPushMatrix();
	glVertexPointer(2, GL_FLOAT, 0, &c[0]);
	glDrawArrays(GL_LINE_LOOP,0, s->m_count);

}
