#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    //All class calls for StudentWold.cpp
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Player*  getPlayer();
  Actor* validPos(double x, double y);
    ~StudentWorld();
    bool overlappingPlayer(Actor* me);
    bool intersecting(double x1, double y1, double x2, double y2);
    bool overlapping(Actor* a, Actor* b);
//    bool overlapping(double x1, double y1, double x2, double y2);
    void increasePeas();
    void addMeanTheifBot(double x, double y, int dir);
    void makeVisible();
    bool blockedObject(Actor* me);
    void restoreHealth();
    Actor* theifGoodie(Actor* a);
    void extraLife();
    bool overlappingPit(Actor* me);
    bool overlappingExit(Actor* m);
    void levelCompleted(Actor* me);
    bool addExit(double x, double y);
    bool noObstaclesInPath(int bX, int bY, int pX, int pY, int dir);
    int cyrstalsLeft();
    bool isBlocked(double x, double y);
    bool overlappingGoodie(Actor* a);
    bool intersectingGoodie(double x1, double y1, double x2, double y2);
    void addPea(double x, double y, int dir);
    void addTheifBot(double x, double y, int dir);
    Actor* getOverlappingObject(Actor* me);
    void levelCompleted() { level_completed = true; }; //Says level is completed
    bool checkIfPeaHits(int x, int y);
    bool surroundingRobots(double x, double y);
    bool botCanMove(int a, int b);
private:
    vector<Actor*> my_map; //Vector
    Player* m_player; //player
    bool level_completed; //Is the level completed

};

#endif // STUDENTWORLD_H_

