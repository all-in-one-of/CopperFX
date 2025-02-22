#ifndef GEOMETRY_OP_DATA_H
#define GEOMETRY_OP_DATA_H

#include <vector>
#include <string>
#include <map>

#include "copper/OpData/OpDataBase.h"
#include "copper/Prims/Point.h"

namespace copper {

class GeometryOpData: public OpDataBase {
	public:
		GeometryOpData(){};

		const std::string& name() const override;

		void saveToFile(const std::string& filename, const unsigned int version) const override;
    void loadFromFile(const std::string& filename, const unsigned int version) override;

    std::vector<Point3d>  *points();
    std::vector<Point3d>  *points() const;
    Point3d 							*createPoint();

    // factory methods
    static std::string myTypeName();
		static OpDataBase *myConstructor();
		
	private:
		std::vector<Point3d> _points;

	private:
		static std::string _ui_name;
};

}

#endif // GEOMETRY_OP_DATA_H