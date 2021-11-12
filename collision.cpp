#include "collision.h"
#include "Math.h"



bool Collision_CircleAndCircleHit(const CollisionCircle * pC1, const CollisionCircle * pC2)
{
	float x = pC1->center.x - pC2->center.x;
	float y = pC1->center.y - pC2->center.y;
	if ((x*x + y*y) < (pC1->radius + pC2->radius) * (pC1->radius + pC2->radius))
	{
		return true;
	}

	return false;
}

bool Collision_RectangleAndRectangleHit(const CollisionRectangle * pR1, const CollisionRectangle * pR2)
{
	if (pR2->x >= pR1->x + pR1->w ||
		pR2->y >= pR1->y + pR1->h ||
		pR1->x >= pR2->x + pR2->w ||
		pR1->y >= pR2->y + pR2->h
		) {
		return false;
	}
	return true;
}

bool Collision_RectangleAndPointHit(const CollisionRectangle * pR, const CollisionPoint * pP)
{
	if (pP->point.x > pR->x&&
		pP->point.y > pR->y&&
		pP->point.x < pR->x + pR->w&&
		pP->point.y < pR->y + pR->h) {
		return true;
	}
	return false;
}

bool Collision_CircleAndPointHit(const CollisionCircle * pC, const CollisionPoint * pP)
{	
	float x = pC->center.x - pP->point.x;
	float y = pC->center.y - pP->point.y;
	if ((x*x + y*y)< pC->radius * pC->radius)
	{
		return true;
	}
	return false;
}

bool Collision_RectangleAndCircleHit(const CollisionRectangle * pR, const CollisionCircle * pC)
{
	float DisX = (float)fabs((pR->x + pR->w*0.5f) - pC->center.x);
	float DisY = (float)fabs((pR->y + pR->h*0.5f) - pC->center.y);
	
	if (DisX >= pR->w *0.5f + pC->radius)return false;
	if (DisY >= pR->h *0.5f + pC->radius)return false;

	if (DisX < (pR->w*0.5f))return true;
	if (DisY < (pR->h*0.5f))return true;

	float Dis = (DisX - pR->w*0.5f)*(DisX - pR->w*0.5f) + (DisY - pR->h*0.5f)*(DisY - pR->h*0.5f);


	return Dis < pC->radius*pC->radius;
}

Cross_imf Collision_LineAndLineHit(const CollisionLine L1, const CollisionLine L2)
{
	//ベクトルL1
	double vL1x = L1.ex - L1.sx;
	double vL1y = L1.ey - L1.sy;
	//ベクトルL2
	double vL2x = L2.ex - L2.sx;
	double vL2y = L2.ey - L2.sy;

	//L1に比較ベクトル１
	double v1s2sx = L2.sx - L1.sx;
	double v1s2sy = L2.sy - L1.sy;
	//L1比較ベクトル２
	double v1s2ex = L2.ex - L1.sx;
	double v1s2ey = L2.ey - L1.sy;

	double L1temp1 = vL1x * v1s2sy - vL1y * v1s2sx;
	double L1temp2 = vL1x * v1s2ey - vL1y * v1s2ex;

	//L2比較ベクトル１
	double v2s1sx = L1.sx - L2.sx;
	double v2s1sy = L1.sy - L2.sy;
	//L2比較ベクトル２
	double v2s1ex = L1.ex - L2.sx;
	double v2s1ey = L1.ey - L2.sy;

	double L2temp1 = vL2x * v2s1sy - vL2y * v2s1sx;
	double L2temp2 = vL2x * v2s1ey - vL2y * v2s1ex;

	Cross_imf cf;
	cf.flag = false;
	cf.interX = 0;
	cf.interY = 0;

	if (L1temp1 * L1temp2 <= 0 && L2temp1 * L2temp2 <= 0) {
		cf.flag = true;
		float k1, k2;
		float b1, b2;
		if (vL1x == 0&& vL2x == 0) {
			cf.flag = false;
		}
		else if (vL1x ==0 && vL2x !=0)
		{
			cf.interX = L1.sx;
			k2 = static_cast<float>(vL2y / vL2x);
			b2 = L2.sy - L2.sx * k2;
			cf.interY = k2 * cf.interX + b2;
		}
		else if (vL1x!=0&&vL2x == 0)
		{
			cf.interX = L2.sx;
			k1 = static_cast<float>(vL1y / vL1x);
			b1 = L1.sy - L1.sx * k1;
			cf.interY = k1 * cf.interX + b1;
		}
		else {
			k1 = static_cast<float>(vL1y / vL1x);
			b1 = L1.sy - L1.sx * k1;

			k2 = static_cast<float>(vL2y / vL2x);
			b2 = L2.sy - L2.sx * k2;

			//(y - b1)/k1 = (y - b2)/k2 ;
			
			cf.interX = (b2 - b1) / (k1 - k2);
			cf.interY = k1 * cf.interX + b1;
		}
	}

	return cf;
}

bool Collision_LineAndRectangleHit(const CollisionLine * pL, const CollisionRectangle * pR)
{
	CollisionLine l1 = { pR->x,pR->y,pR->x + pR->w,pR->y };
	CollisionLine l2 = { pR->x,pR->y,pR->x,pR->y + pR->h };
	CollisionLine l3 = { pR->x,pR->y + pR->h,pR->x + pR->w,pR->y + pR->h };
	CollisionLine l4 = { pR->x + pR->w,pR->y,pR->x + pR->w,pR->y + pR->h };
	if (Collision_LineAndLineHit(*pL, l1).flag)return true;
	if (Collision_LineAndLineHit(*pL, l2).flag)return true;
	if (Collision_LineAndLineHit(*pL, l3).flag)return true;
	if (Collision_LineAndLineHit(*pL, l4).flag)return true;
	CollisionPoint p1, p2;
	p1.point = { pL->sx, pL->sy };
	p2.point = { pL->ex, pL->ey };
	if (Collision_RectangleAndPointHit(pR, &p1))return true;
	if (Collision_RectangleAndPointHit(pR, &p2))return true;
	return false;
}

bool Collision_LineAndLineDistance(const CollisionLine L1, const CollisionLine L2,float length)
{
	CollisionCircle c1;
	c1.center.x = L2.sx;
	c1.center.y = L2.sy;
	c1.radius = length + 0.1f;
	CollisionCircle c2;
	c2.center = { L2.ex,L2.ey };
	c2.radius = length + 0.1f;
	CollisionCircle c3;
	c3.center = { L1.sx,L1.sy };
	c3.radius = length + 0.1f;
	CollisionCircle c4;
	c4.center = { L1.ex,L1.ey };
	c4.radius = length + 0.1f;
	if (Collision_LineAndCircleHit(L1, c1))return true;
	
	if (Collision_LineAndCircleHit(L1, c2))return true;
	
	if (Collision_LineAndCircleHit(L2, c3))return true;
	
	if (Collision_LineAndCircleHit(L2, c4))return true;

	return false;
}

bool Collision_LineAndCircleHit(const CollisionLine L, const CollisionCircle C)
{
	

	CollisionPoint start;
	start.point = { L.sx,L.sy };
	CollisionPoint end;
	end.point = { L.ex,L.ey };
	if (Collision_CircleAndPointHit(&C, &start)) {
		return true;
	}
	if (Collision_CircleAndPointHit(&C, &end)) {
		return true;
	}
	if (fabsf(L.ex - L.sx) <= 0.1f) {
		CollisionLine cl;
		cl.sx = C.center.x - C.radius;
		cl.sy = C.center.y;
		cl.ex = C.center.x + C.radius;
		cl.ey = C.center.y;
		Cross_imf cif = Collision_LineAndLineHit(cl, L);
		if (cif.flag) {
			return true;
		}
	}
	else if (fabsf(L.ey - L.sy) <= 0.1f) {
		CollisionLine cl2;
		cl2.sx = C.center.x;
		cl2.sy = C.center.y - C.radius;
		cl2.ex = C.center.x;
		cl2.ey = C.center.y + C.radius;
		Cross_imf cif = Collision_LineAndLineHit(cl2, L);
		if (cif.flag) {
			return true;
		}
	}
	else
	{
		float k = -(L.ex - L.sx) / (L.ey - L.sy);
		//float k = (L.ey - L.sy) / (L.ex - L.sx);
		float b = C.center.y - k * C.center.x;
		float angle = atanf(k);
		float x1 = C.center.x - C.radius * cosf(angle);
		float y1 = C.center.y - C.radius * sinf(angle);
		float x2 = C.center.x + C.radius * cosf(angle);
		float y2 = C.center.y + C.radius * sinf(angle);
		CollisionLine cl3;
		cl3.sx = x1;
		cl3.sy = y1;
		cl3.ex = x2;
		cl3.ey = y2;
		Cross_imf cif = Collision_LineAndLineHit(cl3, L);
		if (cif.flag) {
			return true;
		}
	}
	return false;
}

CLCross_imf Collision_LineANDCircle_forCLCross(CollisionLine line, CollisionCircle circle) {
	float cx = circle.center.x;
	float cy = circle.center.y;
	float cr = circle.radius;
	float sx = line.sx;
	float sy = line.sy;
	float ex = line.ex;
	float ey = line.ey;

	float k = 0;
	float b = 0;

	CLCross_imf cimf;
	cimf.p1x = 0;
	cimf.p1y = 0;
	cimf.p2x = 0;
	cimf.p2y = 0;
	cimf.flag = false;

	if (fabsf(ex - sx) <= 0.1f) {
		CollisionPoint pp;
		pp.point = { sx,cy };
		if (Collision_CircleAndPointHit(&circle, &pp)) {
			float len = sqrtf(cr*cr - (cx - sx)*(cx - sx));
			
			float minY = min(sy, ey);
			float maxY = max(sy, ey);
			cimf.p1x = sx;
			cimf.p1y = cy - len;
			cimf.p2x = sx;
			cimf.p2y = cy + len;

			bool b1 = false;
			bool b2 = false;
			if (cimf.p1y > minY&&cimf.p1y < maxY) {
				b1 = true;
			}
			if (cimf.p2y > minY&&cimf.p2y < maxY) {
				b2 = true;
			}
			if (b1 && !b2) {
				cimf.p2x = cimf.p1x;
				cimf.p2y = cimf.p1y;
				cimf.flag = true;
			}
			else if (!b1&&b2) {
				cimf.p1x = cimf.p2x;
				cimf.p1x = cimf.p2y;
				cimf.flag = true;
			}
			else if (b1&&b2) {
				cimf.flag = true;
			}
			else if (!b1 && !b2) {
				cimf.flag = false;
			}
		}
	}
	else if (fabsf(ey - sy) <= 0.1f) {
		CollisionPoint pp;
		pp.point = { cx,sy };
		if (Collision_CircleAndPointHit(&circle, &pp)) {
			float len = sqrtf(cr*cr - (cy - sy)*(cy - sy));
			
			float minX = min(sx, ex);
			float maxX = max(sx, ex);
			cimf.p1x = cx - len;
			cimf.p1y = sy;
			cimf.p2x = cx + len;
			cimf.p2y = sy ;
			
			bool b1 = false;
			bool b2 = false;
			if (cimf.p1x > minX&&cimf.p1x < maxX) {
				b1 = true;
			}
			if (cimf.p2x > minX&&cimf.p2x < maxX) {
				b2 = true;
			}
			if (b1 && !b2) {
				cimf.p2x = cimf.p1x;
				cimf.p2y = cimf.p1y;
				cimf.flag = true;
			}
			else if (!b1&&b2) {
				cimf.p1x = cimf.p2x;
				cimf.p1x = cimf.p2y;
				cimf.flag = true;
			}
			else if (b1&&b2) {
				cimf.flag = true;
			}
			else if (!b1 && !b2) {
				cimf.flag = false;
			}
		}
	}
	else {
		k = (ey - sy) / (ex - sx);
		b = sy - k * sx;

		float k2 = -1 / k;
		float b2 = cy - cx * k2;
		
		float px = (b2 - b) / (k - k2);
		float py = px * k + b;
		CollisionPoint pp;
		pp.point = { px,py };
		if (Collision_CircleAndPointHit(&circle, &pp)) {

			float len1_2 = (pp.point.x - cx)*(pp.point.x - cx) + (pp.point.y - cy)*(pp.point.y - cy);
			float len2 = sqrtf(cr * cr - len1_2);
			float per = len2 / sqrtf(len1_2);
			float offx = (cy - py)*per;
			float offy = (px - cx)*per;

			float minX = min(sx, ex);
			float maxX = max(sx, ex);

			cimf.p1x = px - offx;
			cimf.p1y = py - offy;
			cimf.p2x = px + offx;
			cimf.p2y = py + offy;
			
			bool b1 = false;
			bool b2 = false;
			if (cimf.p1x > minX&&cimf.p1x < maxX) {
				b1 = true;
			}
			if (cimf.p2x > minX&&cimf.p2x < maxX) {
				b2 = true;
			}
			if (b1 && !b2) {
				cimf.p2x = cimf.p1x;
				cimf.p2y = cimf.p1y;
				cimf.flag = true;
			}
			else if (!b1&&b2) {
				cimf.p1x = cimf.p2x;
				cimf.p1x = cimf.p2y;
				cimf.flag = true;
			}
			else if (b1&&b2) {
				cimf.flag = true;
			}
			else if (!b1 && !b2) {
				cimf.flag = false;
			}
		}
	}
	return cimf;
}

float Collision_PointAndPoint_Distance(float p1x, float p1y, float p2x, float p2y)
{
	float length = (p1x - p2x)*(p1x - p2x) + (p1y - p2y)*(p1y - p2y);
	float len = sqrtf(length);
	return len;
}

float Collision_PointAndLine_Distance(float px, float py, CollisionLine L)
{
	if (fabsf(L.ex - L.sx) <= 0.5f) {
		float miY = min(L.ey, L.sy);
		float maY = max(L.ey, L.sy);
		if (py <= miY) {
			float len = Collision_PointAndPoint_Distance(px, py, L.sx, miY);
			return len;
		}
		else if (py >= maY) {
			float len = Collision_PointAndPoint_Distance(px, py, L.sx, maY);
			return len;
		}
		else {
			float len = fabsf(L.sx - px);
			return len;
		}
	}else if (fabsf(L.ey - L.sy) <= 0.5f) {
		float miX = min(L.ex, L.sx);
		float maX = max(L.ex, L.sx);
		if (px <= miX) {
			float len = Collision_PointAndPoint_Distance(px, py, miX, L.sy);
			return len;
		}
		else if (px >= maX) {
			float len = Collision_PointAndPoint_Distance(px, py, maX, L.sy);
			return len;
		}
		else {
			float len = fabsf(L.sy - py);
			return len;
		}
	}
	else {
		float k = (L.ey - L.sy) / (L.ex - L.sx);
		float b = L.ey - k * L.ex;
		float k2 = -1 / k;
		float b2 = py - k2 * px;

		float nx = (b2 - b) / (k - k2);
		float ny = nx * k2 + b2;

		float minX = min(L.sx, L.ex);
		float maxX = max(L.sx, L.ex);

		if (nx < minX) {
			float len = Collision_PointAndPoint_Distance(px, py, minX, minX * k + b);
			return len;
		}
		else if (nx > maxX) {
			float len = Collision_PointAndPoint_Distance(px, py, maxX, maxX * k + b);
			return len;
		}
		else {
			float len = Collision_PointAndPoint_Distance(px, py, nx, ny);
			return len;
		}
	}

	return 0.0f;
}
