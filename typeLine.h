#ifndef TYPELINE_H
#define TYPELINE_H

#include "collision.h"

//íºê¸
class LineStraightC {
public:
	LineStraightC(float sx, float sy, float ex, float ey) {
		startX = sx;
		startY = sy;
		endX = ex;
		endY = ey;

		if (endY - startY == 0) {
			type = typeLine_vertical;

			k = 0;
			hk = 0;
			b = endY;
			hb = 0;

		}
		else if (endX - startX == 0) {
			type = typeLine_horizontal;
			k = 0;
			hk = 0;
			b = 0;
			hb = endX;
		}
		else {
			type = typeLine_diagonal;

			k = (endY - startY) / (endX - startX);
			hk = (endX - startX) / (endY - startY);
			b = endY - k * endX;
			hb = endX - hk * endY;
		}
	}
	~LineStraightC() {};

	enum 
	{
		typeLine_horizontal,
		typeLine_vertical,
		typeLine_diagonal,

	};

	float GetX_fromY(float* x, float y) {
		switch (type)
		{
		case LineStraightC::typeLine_diagonal:
			*x = hk * y + hb;
			break;
		case LineStraightC::typeLine_horizontal:
			*x = hb;
			break;
		case LineStraightC::typeLine_vertical:
			break;
		default:
			break;
		}
		return *x;
	}
	float GetY_formX(float* y, float x) {
		switch (type)
		{
		case LineStraightC::typeLine_diagonal:
			*y = k * x + b;
			break;
		case LineStraightC::typeLine_horizontal:
			
			break;
		case LineStraightC::typeLine_vertical:
			*y = b;
			break;
		default:
			break;
		}
		return *y;
	}

	float GetK() { return k; }
	float GetB() { return b; }

	float GetSX() { return startX; }
	float GetSY() { return startY; }
	float GetEX() { return endX; }
	float GetEY() { return endY; }

	CollisionLine GetLine() {
		CollisionLine cl = { startX,startY,endX,endY };
		return cl;
	}

private:
	float k;
	float b;
	float hk;
	float hb;

	float startX;
	float startY;
	float endX;
	float endY;

	int type;
};

//ã»ê¸

#endif // !TYPELINE

