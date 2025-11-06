#include "engine.h"

Vector2 GetPositionInsideRectangle(Rectangle rec)
{
	int randX =	GetRandomValue(rec.x, rec.width);
	int randY = GetRandomValue(rec.y, rec.height);
	Vector2 randVector = {randX, randY};
	return randVector;
}

Vector2 GetPositionOutsideRectangle(Rectangle rec, int min, int max)
{
    int side = GetRandomValue(0, 3);
    Vector2 pos = {0};

    switch (side)
    {
        case 0: // left
            pos.x = rec.x - GetRandomValue(min, max);
            pos.y = GetRandomValue((int)rec.y, (int)(rec.y + rec.height));
            break;

        case 1: // right
            pos.x = rec.x + rec.width + GetRandomValue(min, max);
            pos.y = GetRandomValue((int)rec.y, (int)(rec.y + rec.height));
            break;

        case 2: // top
            pos.x = GetRandomValue((int)rec.x, (int)(rec.x + rec.width));
            pos.y = rec.y - GetRandomValue(min, max);
            break;

        case 3: // bottom
            pos.x = GetRandomValue((int)rec.x, (int)(rec.x + rec.width));
            pos.y = rec.y + rec.height + GetRandomValue(min, max);
            break;
    }

    return pos;
}
