#pragma once
#include <d2d1.h>

class FrameResource
{
public:
	FrameResource()
	{
		rectForYear = D2D1::RectF(
			520, 200,
			600, 230
		);
		rectForMonth = D2D1::RectF(
			520, 300,
			600, 330
		);
		for (int x = 0; x < 7; x++)
			for (int y = 0; y < 7; y++)
			{
				rectForCal[y * 7 + x] = D2D1::RectF(
					x * 34.2f,
					y * 15.2f,
					(x + 1) * 34.2f,
					(y + 1) * 15.2f
				);
				rectForCalSingleMonth[y * 7 + x] = D2D1::RectF(
					x * 70.0f,
					y * 91.4f,
					(x + 1) * 70.0f,
					(y + 1) * 91.4f
				);
			}
	}
	D2D1_RECT_F rectForYear;
	D2D1_RECT_F rectForMonth;
	D2D1_RECT_F rectForCal[49];
	D2D1_RECT_F rectForCalSingleMonth[49];
};