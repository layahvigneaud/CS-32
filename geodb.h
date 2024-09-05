

#ifndef geodb_h
#define geodb_h


#include "base_classes.h"
#include "HashMap.h"
#include "geotools.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

//h class deffinitions
class GeoDatabase: public GeoDatabaseBase
{
public:
    GeoDatabase();
     virtual ~GeoDatabase();
     virtual bool load(const std::string& map_data_file);
     virtual bool get_poi_location(const std::string& poi,
     GeoPoint& point) const;
     virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
     const;
     virtual std::string get_street_name(const GeoPoint& pt1,
     const GeoPoint& pt2) const;
private:
    GeoPoint processPoint(ifstream &file);
    void connectedPoints(const GeoPoint& p1, const GeoPoint& p2);
    HashMap<std::vector<GeoPoint>> connectingPoints;
    HashMap<std::string> streetSegment;
    HashMap<GeoPoint> importantPoints;
};


   




#endif /* geodb_h */
