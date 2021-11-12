#ifndef COLLISION_H
#define COLLISION_H
#include <d3dx9.h>

typedef struct CollisionCircle_tag 
{
	/*CollisionCircle_tag()
		:center(D3DXVECTOR2(0.0f,0.0f))
		,radius(0.0f)
	{}
	explicit CollisionCircle_tag(float inX, float inY, float inR)
	{
		center.x = inX, center.y = inY, radius = inR;
	}*/

	D3DXVECTOR2 center;
	float radius;

}CollisionCircle;

typedef struct CollisionRectangle_tag
{
	/*CollisionRectangle_tag()
		:x(0.0f)
		,y(0.0f)
		,w(0.0f)
		,h(0.0f)
	{}*/
	/*explicit CollisionRectangle_tag(float inX, float inY, float inW, float inH)
	{
		x = inX, y = inY, w = inW, h = inH;
	}*/

	float x, y;
	float w, h;
}CollisionRectangle;

typedef struct CollisionPoint_tag 
{
	D3DXVECTOR2 point;
}CollisionPoint;

typedef struct CollisionLine_tag
{
	/*CollisionLine_tag()
		:sx(0.0f)
		,sy(0.0f)
		,ex(0.0f)
		,ey(0.0f)
	{}*/
	/*explicit CollisionLine_tag(float inSX, float inSY, float inEX, float inEY)
	{
		sx = inSX, sy = inSY, ex = inEX, ey = inEY;
	}*/

	float sx, sy;
	float ex, ey;
}CollisionLine;

struct Cross_imf {
	/*Cross_imf()
		:flag(false)
		,interX(0.0f)
		,interY(0.0f)
	{}*/
	
	bool flag;
	float interX, interY;
};

struct CLCross_imf {
	float p1x;
	float p1y;
	float p2x;
	float p2y;
	bool flag;
};

bool Collision_CircleAndCircleHit(const CollisionCircle* pC1, const CollisionCircle* pC2);

bool Collision_RectangleAndRectangleHit(const CollisionRectangle * pR1, const CollisionRectangle* pR2);

bool Collision_RectangleAndPointHit(const CollisionRectangle* pR, const CollisionPoint* pP);

bool Collision_CircleAndPointHit(const CollisionCircle* pC, const CollisionPoint* pP);

bool Collision_RectangleAndCircleHit(const CollisionRectangle* pR, const CollisionCircle* pC);

Cross_imf Collision_LineAndLineHit(const CollisionLine L1, const CollisionLine L2);

bool Collision_LineAndRectangleHit(const CollisionLine* pL, const CollisionRectangle* pR);

bool Collision_LineAndLineDistance(const CollisionLine L1, const CollisionLine L2,float length);

bool Collision_LineAndCircleHit(const CollisionLine L, const CollisionCircle C);

//åì_Ç™Ç†Ç¡ÇΩèÍçáÅBCLCross_imf.flagÇ™true
CLCross_imf Collision_LineANDCircle_forCLCross(CollisionLine line, CollisionCircle circle);

float Collision_PointAndPoint_Distance(float p1x, float p1y,float p2x,float p2y);
float Collision_PointAndLine_Distance(float px, float py, CollisionLine L);
//bool Collision_LineAndPointHit(CollisionLine pL, float x,float y);

#endif // !COLLISION_H

