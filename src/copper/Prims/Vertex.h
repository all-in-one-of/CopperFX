#ifndef __Vertex_h__
#define __Vertex_h__

#include <vector>
#include <stdexcept>
#include <math.h>

#include "Point.h"


namespace copper {

class Vertex { 
	public:
		Vertex(Point3d *pt);

	private:
		Point3d *_pt;
};

}

#endif