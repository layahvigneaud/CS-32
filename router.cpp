
#include "router.h"


//Route constructor
Router::Router(const GeoDatabaseBase& geo_db)  {
    m_database = &geo_db;
}

//Route deconstructor
Router::~Router(){
    
}




std::vector<GeoPoint>Router::route(const GeoPoint& pt1,const GeoPoint& pt2) const {
    //Vectors for the routes
    std::priority_queue<Pathway, std::vector<Pathway>, myComparator> openQueue;//priority queue
    std::vector<GeoPoint> closedList;
    std::vector<GeoPoint> tempList;
    std::vector<GeoPoint> children;
    HashMap<GeoPoint> visited;
    HashMap<GeoPoint> closed;
    //Push first point
    Pathway first{pt1, 0, 0,};
    openQueue.push(first);
    
    GeoPoint current;
    //Run through priority list
    while (!openQueue.empty()) {
        first = openQueue.top();
        openQueue.pop();
        if(first.currPoint.to_string() == pt2.to_string()){
            current = first.currPoint;
            while(current.to_string() != pt1.to_string()){ //See if current point is pt1 and if not push into templist
                tempList.push_back(current);
                current = *visited.find(current.to_string());
            }
            tempList.push_back(pt1);
            vector<GeoPoint>::iterator it;
            for (it = tempList.end() - 1; it != tempList.begin(); --it) {
                closedList.push_back(*it);
            }
            closedList.push_back(pt2);
            return closedList;
        }
      //Get children or neighbor nodes
        children = m_database->get_connected_points(first.currPoint);
        std::vector<GeoPoint>::iterator i;
        for (i = children.begin(); i != children.end(); i++){
            GeoPoint* child = &(*i);
            if(visited.find(child->to_string())){
                continue;
            }
            Pathway x(*child, first.smallestDistance + distance_earth_km(first.currPoint, *child),distance_earth_km(*child, pt2)); //calculate distance and push shortest into priority queue
            openQueue.push(x);
            visited.insert(child->to_string(), first.currPoint); //insert point into visited node
        }
        
    }
    return closedList; //Return the closed list
}
