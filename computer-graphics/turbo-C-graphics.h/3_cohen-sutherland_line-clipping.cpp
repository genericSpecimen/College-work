#include <iostream>
#include <graphics.h>

// Outcode: TBRL

const int INSIDE	= 0; // 0000
const int LEFT		= 1; // 0001
const int RIGHT		= 2; // 0010
const int BOTTOM	= 4; // 0100
const int TOP		= 8; // 1000

const int x_min = 40;
const int x_max = 100;
const int y_min = 10;
const int y_max = 100;

int compute_outcode(double x, double y) {
	int code = INSIDE;

	if (x < x_min) {
		// point is to the LEFT of the left clip boundary
		code |= LEFT;	//set the last bit
	}
	else if (x > x_max) {
		// point is to the RIGHT of the right clip boundary
		code |= RIGHT;	//set the second last bit
	}
	
	if (y < y_min) {
		// point is to the BOTTOM of the bottm clip boundary
		code |= BOTTOM; // set the second bit
	}
	else if(y > y_max) {
		// point is to the TOP of the top clip boundary
		code |= TOP;	// set the first bit
	}
	return code;
}

void cohen_sutherland_clip(double x0, double y0, double x1, double y1) {
	/*
	 * clip the line segment PQ where P = (x0, y0) and Q = (x1, y1)
	 * against the clip rectangle as defined by x_min, x_max, y_min, y_max
	 */

	// region codes for P and Q
	int oc0 = compute_outcode(x0, y0);
	int oc1 = compute_outcode(x1, y1);

	bool accept = false;

	while (true) {
		if(oc0 == 0 && oc1 == 0) {
			/* region codes of both points is 0,
			 * thus both points lie inside the clip rectangle
			 * TRIVIAL ACCEPTANCE
			 */
			accept = true;
			break;
		} else if((oc0 & oc1) != 0) {
			/* logical AND of both points is not 0,
			 * thus, both points lie outside the clip rectangle
			 * TRIVIAL REJECTION
			 */
			accept = false;
			break;
		} else {
			/* logical AND is 0,
			 * tests for both trivial acceptance / rejection have failed;
			 * the line segment intersects with some clip boundary
			 * we need to clip against that boundary
			 */

			// pick the outcode of a point which is outside the clip rectangle
			// (there must be one such point)
			int oc_outside = (oc0 != 0) ? oc0 : oc1;
			double x, y;

			/*
			 * Find the intersection point using the formulae
			 * y = y0 + m(x - x0)
			 * x = x0 + (1/m)(y - y0)
			 */

			double slope = (y1 - y0) / (x1 - x0);

			if (oc_outside & TOP) {
				// intersects with TOP edge (y = y_max)
				y = y_max;
				x = x0 + (1/slope) * (y - y0);
			} else if (oc_outside & BOTTOM) {
				// intersects with BOTTOM edge (y = y_min)
				y = y_min;
				x = x0 + (1/slope) * (y - y0);
			} else if (oc_outside & RIGHT) {
				// intersects with RIGHT edge (x = x_max)
				x = x_max;
				y = y0 + slope * (x - x0);
			} else {
				// intersects with LEFT edge (x = x_min)
				x = x_min;
				y = y0 + slope * (x - x0);
			}

			if (oc_outside == oc0) {
				x0 = x; y0 = y;
				oc0 = compute_outcode(x0, y0);
			} else {
				x1 = x; y1 = y;
				oc1 = compute_outcode(x1, y1);
			}
		}
	}

	// display clip rectangle
	// left-top right-bottom
	rectangle(x_min, y_min, x_max, y_max);
	if(accept) {
		std::cout << "Line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ") has been accepted.\n";
		// display the line
		line(x0, y0, x1, y1);
	} else {
		std::cout << "Line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ") has been rejected.\n";
		// display nothing else
	}
}

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	cohen_sutherland_clip(50, 50, 70, 70);
	cohen_sutherland_clip(70, 90, 110, 40);
	cohen_sutherland_clip(30, 15, 40, 110);
	cohen_sutherland_clip(30, 10, 110, 110);
	cohen_sutherland_clip(30, 0, 110, 110);
	getch();
	closegraph();
	return 0;
}
