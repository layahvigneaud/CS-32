#include "geodb.h"
//Constructor
GeoDatabase::GeoDatabase()
{

}
//Deconstructor
GeoDatabase::~GeoDatabase()
{

}
//Loads the file
bool GeoDatabase::load(const std::string& map_data_file){
    std::ifstream file(map_data_file);
    if(!file){
        std::cerr << "bad file" << std::endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        string street_name = line;
        GeoPoint start = processPoint(file);
        GeoPoint end = processPoint(file);
        file.ignore(10000, '\n');
        string street_segment = start.to_string() + " " + end.to_string();
        connectedPoints(start, end);
        streetSegment.insert(street_segment, street_name); //Inserts street name
        int numPoints = 0;
        file >> numPoints;
        file.ignore(10000, '\n');
        //Reads in character by character
        for (int i = 0; i < numPoints; ++i) {
            char c;
            string intrestName;
            while(file.get(c) && c != '|'){
                intrestName += c;
            }
            //Process intrest points
            GeoPoint poi = processPoint(file);
            file.ignore(10000, '\n');
            importantPoints.insert(intrestName, poi);
            if(importantPoints.find(intrestName) == nullptr){
                return false;
            }
            GeoPoint mid = midpoint(start, end); //Gets midpoint
            string mid_segment = mid.to_string();
            string path = mid_segment + " " + poi.to_string();
            connectedPoints(mid, poi);
            streetSegment.insert(path, "a path"); 
            //Insert street segments
            if(i == 0)
            {
                string startPoint = mid_segment + " " + start.to_string();
                string endPoint = mid_segment + " " + end.to_string();
                connectedPoints(mid, start);
                connectedPoints(mid, end);
                streetSegment.insert(startPoint, street_name);
                streetSegment.insert(endPoint, street_name);
            }
        }
    }
    return true;
}

//Push in the conecting points
void GeoDatabase::connectedPoints(const GeoPoint& p1, const GeoPoint& p2){
    connectingPoints[p1.to_string()].push_back(p2);
    connectingPoints[p2.to_string()].push_back(p1);
}




//Gets the street name
std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    string pathOne = pt1.to_string() + " " + pt2.to_string();
    string pathTwo = pt2.to_string() + " " + pt1.to_string();
    const string* street_name = streetSegment.find(pathOne);
    if(street_name != nullptr){
        return *street_name;
    }
    street_name = streetSegment.find(pathTwo);
    if(street_name != nullptr){
        return *street_name;
    }
    return "";
}
//Get the point location
bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    const GeoPoint* pointFound = importantPoints.find(poi);
    if(pointFound == nullptr){
        return false;
    }
    else{
        point = *pointFound;
    }
    return true;
}
//Process the point
GeoPoint GeoDatabase::processPoint(ifstream &file)
{
    string latitude;
    file >> latitude;
    string longitude;
    file >> longitude;
    GeoPoint coord = GeoPoint(latitude,longitude);
    return coord;
}


std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    const std::vector<GeoPoint>* connected_Segments = connectingPoints.find(pt.to_string());
    if(connected_Segments == nullptr)
    {
        return  std::vector<GeoPoint>();
    }
    return *connected_Segments;
    
}

