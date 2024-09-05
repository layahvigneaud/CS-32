//Tour h class deffinition
#ifndef tour_generator_h
#define tour_generator_h
//#include "HashMap.h"
#include "base_classes.h"
#include "geotools.h"
#include <vector>
#include <stdio.h>
#include <stack>
class TourGenerator: public TourGeneratorBase
{
public:
 TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
 virtual ~TourGenerator();
 virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const GeoDatabaseBase* m_data;
    const RouterBase* m_route;
};
#endif /* tour_generator_h */
