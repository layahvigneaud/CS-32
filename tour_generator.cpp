
#include "tourcmd.h"
#include "tour_generator.h"

//Tour constuctor
TourGenerator:: TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router){
    m_data = &geodb;
    m_route = &router;
}

//Tour deconstructor
TourGenerator::~TourGenerator(){
    
}



//Generates tour
std::vector<TourCommand> TourGenerator:: generate_tour(const Stops& stops) const {
    std::vector<TourCommand> directions;

    std::stack<GeoPoint> recent_points;


    int k = 0;
//For loop gets all data for the first point output
    for (int i = 0; i < stops.size(); i++) {
        std::cerr << std::endl << std::endl << std::endl;

        std::string firstPoint;
        std::string comments;
        std::string streeName = "";
    k++;
    stops.get_poi_data(i, firstPoint, comments);
    GeoPoint poi_location;
        m_data->get_poi_location(firstPoint, poi_location);
    TourCommand commentary;
    commentary.init_commentary(firstPoint, comments);
        //Gets all data need for next point output
    directions.push_back(commentary);
        std::cerr << comments << std::endl;
        std::string dest;
        std::string commentaryTwo;
    stops.get_poi_data(k, dest, comments);
    GeoPoint detLoc;
        m_data->get_poi_location(dest, detLoc);
    double distBetween;
//calculates the route
        std::vector<GeoPoint> new_route = m_route->route(poi_location, detLoc);
    if (!new_route.empty()) {
    recent_points.push(new_route[0]);
//For loop runs through points in the loop
    for (int i = 1; i < new_route.size(); i++) {
    recent_points.push(new_route[i]);
    GeoPoint first = new_route[i - 1];
    GeoPoint second = new_route[i];
        std::string streetNameTwo = m_data->get_street_name(first, second);
    distBetween = distance_earth_miles(first, second);
    if (streeName != streetNameTwo) {
    
//Stack runs through points
    if (recent_points.size() > 2) {

    GeoPoint c = recent_points.top();
    recent_points.pop();
    GeoPoint b = recent_points.top();
    recent_points.pop();
    GeoPoint a = recent_points.top();
    recent_points.pop();

    recent_points.push(b);
    recent_points.push(c);

//Gets angle for turn and sets dirAngle
    const double angle = angle_of_turn(a, b, c);


        std::string dirAngle = "";

    if (angle != 0 && angle != 180.0) {

    if (angle < 180.0 && angle >= 1.0) {
    dirAngle = "left";
    }
    else if (angle <= 359.0 && angle >= 180.0){
    dirAngle = "right";
    }
    if (dirAngle != "") {
    TourCommand turn_dir;
    turn_dir.init_turn(dirAngle, streetNameTwo);
    directions.push_back(turn_dir);
        std::cerr << "angle of turn is: " << dirAngle << std::endl;
    }
    }



    }


    }



        std::string direction;
//Get the direction for output
    double line = angle_of_line(first, second);
    if (line < 22.5 && line >= 0) {
    direction = "east";
    }
    else if (line < 67.5 && line >= 22.5) {
    direction = "northeast";
    }
    else if (line < 112.5 && line >= 67.5) {
    direction = "north";
    }
    else if (line < 157.5 && line >= 112.5) {
    direction = "northwest";
    }
    else if (line < 202.5 && line >= 157.5) {
    direction = "west";
    }
    else if (line < 247.5 && line >= 202.5) {
    direction = "southwest";
    }
    else if (line < 292.5 && line >= 247.5) {
    direction = "south";
    }
    else if (line < 337.5 && line >= 292.5) {
    direction = "southeast";
    }
    else if (line >= 337.5) {
    direction = "east";
    }

//Plans the next move

    TourCommand nextMove;
    nextMove.init_proceed(direction, streetNameTwo, distBetween, first, second);
    directions.push_back(nextMove);
        std::cerr << "move " << distBetween << " " << direction << " on " << streetNameTwo << std::endl;


    streeName = streetNameTwo;



    }


    }


    while (!recent_points.empty()) {
    recent_points.pop();
    }

    }






   //returns directions vector

    return directions;

    }



        

    
    
    
    
