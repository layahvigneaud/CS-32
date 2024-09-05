
#ifndef router_h
#define router_h
#include <vector>
#include <queue>
#include "HashMap.h"
#include "base_classes.h"
#include <stdio.h>
#include "geodb.h"
//Router deffinition
class Router: public RouterBase
{
public:
 Router(const GeoDatabaseBase& geo_db);
 virtual ~Router();
 virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
 const GeoPoint& pt2) const;
private:
   const GeoDatabaseBase* m_database;
    struct Pathway {
        Pathway(GeoPoint m_currPoint, double m_smallestDistance, double m_endDistance)
        {
            currPoint = m_currPoint;
            smallestDistance = m_smallestDistance;
            endDistance = m_endDistance;
            finalDistance = smallestDistance + endDistance;
            
        }
        GeoPoint currPoint;
        double smallestDistance;
        double endDistance;
        double finalDistance;
        
    };
    
    struct myComparator {
        bool operator()(Pathway const& p1, Pathway const& p2)
                {
                    return p1.finalDistance > p2.finalDistance;
                }
        };
   
};
#endif /* router_hpp */
