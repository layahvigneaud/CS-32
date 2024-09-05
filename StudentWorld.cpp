#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_player = nullptr;
        my_map.clear();
}
//Adds peas
void StudentWorld::addPea(double x, double y, int dir) {
    Peas* p = new Peas(this,5,x,y,dir,0);
    p->setVisible(true);
    my_map.push_back(p);
}
//Adds theifBots
void StudentWorld::addTheifBot(double x, double y, int dir) {
    TheifBot* q = new TheifBot(this, 2, x, y, 0);
    q->setVisible(true);
    my_map.push_back(q);
}
//Adds mean TheifBots
void StudentWorld::addMeanTheifBot(double x, double y, int dir) {
    MeanTheifBot* j = new  MeanTheifBot(this, 3, x, y, 0);
    j->setVisible(true);
    my_map.push_back(j);
}


//Loads level
int StudentWorld::init()
{
    level_completed = false;
    Level lev(assetPath());
    string level_n = "level";
    string level_num = to_string(getLevel()); //Checks if level 0-9
    if(getLevel() <= 9){
        level_n += "0";
    }
    level_n += level_num;
    level_n += ".txt"; //Adds txt
    if(getLevel() > 99){ //Checks if won game
        return GWSTATUS_PLAYER_WON;
    }
    Level::LoadResult result = lev.loadLevel(level_n); //loads level
    if(result == Level:: load_fail_file_not_found){
        cerr << "Cannot find " << level_n << " data file" << endl;
        return GWSTATUS_LEVEL_ERROR; //Check error
    }
    else if(result == Level::load_fail_bad_format){
        cerr << "Level is improperly formated. " << endl;
        return GWSTATUS_LEVEL_ERROR; //Check error
    }
    else if(result == Level:: load_success){ //load level
        cerr << "Level loaded succefully " << endl;
        for (int y = 0; y < VIEW_HEIGHT; y++){
            for (int x = 0; x < VIEW_WIDTH; x++){
                Level::MazeEntry ge = lev.getContentsOf(x, y); //Adds stuff to level
                switch(ge)
                { //Adds all actors to the level
                    case Level:: empty:
                       // cerr << "Location " << x << " " << y << " is empty" << endl;
                        break;
                    case Level:: player:
                      //  cerr << "Player is at " << x << " " << y << endl;
                        m_player = new Player(this, 0, x, y, 0, 20);
                        break;
                    case Level:: horiz_ragebot:
                     //   cerr << "horiz_ragebot is at " << x << " " << y << endl;
                        my_map.push_back(new RageBot(this, 1, x, y, 0));
                        break;
                    case Level:: vert_ragebot:
                     //   cerr << "vert_ragebot is at " << x << " " << y << endl;
                        my_map.push_back(new RageBot(this, 1, x, y, 90));
                        break;
                    case Level:: thiefbot_factory:
                        my_map.push_back(new Factory(this,  4, x, y, 0));
                      //  cerr << "thiefbot_factory is at " << x << " " << y << endl;

                        break;
                    case Level:: mean_thiefbot_factory:
                        my_map.push_back(new Factory(this,  4, x, y, 1));
                        cerr << "mean_thiefbot_factory is at " << x << " " << y << endl;
                        break;
                    case Level:: wall:
                       // cerr << "wall is at " << x << " " << y << endl;
                        my_map.push_back(new Walls(this, 6, x, y, -1));
                        break;
                    case Level:: marble:
                       // cerr << "marble is at " << x << " " << y << endl;
                        my_map.push_back(new Marbles(this, 8, x, y, 0, 20));
                        break;
                    case Level:: pit:
                        //cerr << "pit is at " << x << " " << y << endl;
                        my_map.push_back(new Pits(this, 9, x, y, -1));
                        break;
                    case Level:: crystal:
                        my_map.push_back(new Crystals(this, 10, x, y));
                        //cerr << "crystal is at " << x << " " << y << endl;
                        break;
                    case Level:: restore_health:
                        my_map.push_back(new RestorLife(this, 11, x, y));
                        //cerr << "restore_health is at " << x << " " << y << endl;
                        break;
                    case Level:: extra_life:
                        my_map.push_back(new ExtraLife(this, 12, x, y));
                        //cerr << "extra_life is at " << x << " " << y << endl;
                        break;
                    case Level:: ammo:
                        //cerr << "ammo is at " << x << " " << y << endl;
                        my_map.push_back(new Ammo(this, 13, x, y));
                        break;
                    case Level:: exit:
                        //cerr << "exit is at " << x << " " << y << endl;
                       my_map.push_back(new Exits(this, 7, x, y, -1));
                        break;
                }
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q
    queue<Actor*> willMoveTick; //Creates queue
    for(vector<Actor*>:: iterator it = my_map.begin(); it != my_map.end(); it++){
        willMoveTick.push(*it); //pushes all vector actors into queue
    }
    willMoveTick.push(m_player); //pushes player into queue
    while(!willMoveTick.empty()){
        Actor* a = willMoveTick.front();
        willMoveTick.pop();
        if(a->isAlive()){
            (a->doSomething()); //runs do something for everything currently in the queue
        }
        if (!(m_player->isAlive())) { //Check if player is alive
                        decLives();
                        return GWSTATUS_PLAYER_DIED;
                    }
        if (level_completed) { //Check if level is finished.
                        playSound(SOUND_FINISHED_LEVEL);
                        increaseScore(2000 + m_player->getBonus());
                        return GWSTATUS_FINISHED_LEVEL;
                    }
    }
        
            
        for(vector<Actor*>:: iterator p = my_map.begin(); p != my_map.end(); p++){ //Delete any dead objects
                if (!(*p)->isAlive()) {
                    delete *p;
                    my_map.erase(p);
                    p = my_map.begin();
                }
            }
    
    ostringstream oss; //stream operations

        oss.fill('0');
        oss << "Score: ";
        oss << setw(6) << getScore() << "  "; //output score

        oss << "Level: ";
    if (getLevel() < 10) { //output level
        oss << "0";
    }
    oss << getLevel() << "  ";


        oss << "Lives: ";
        oss << getLives() << "  "; //output lives

        oss << "Health: ";
           oss << m_player->getHealth()*100/20 << "%  "; //Output health

        oss << "Ammo: ";
       oss << m_player->getAmmo() << "  "; //Output ammo

       oss << "Bonus: ";
       oss << m_player->getBonus() << "  "; //Output bonus



        setGameStatText(oss.str());

        return GWSTATUS_CONTINUE_GAME;
    //setGameStatText("Game will end when you type q");
    
}


//Deconstructor
StudentWorld::~StudentWorld() {
    cleanUp();
}
//Delete any pointers or objects at the end of the game.
void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator i;
    
    i = my_map.begin();
    while(i != my_map.end()){
        delete* i;
        i = my_map.erase(i);
    }
  delete m_player;
    m_player = nullptr;
}
//Check for pointer "actor" or nullptr "no actor" at grid.
Actor* StudentWorld:: validPos(double x, double y){
    for(vector<Actor*>:: iterator p = my_map.begin(); p != my_map.end(); p++){
        if((*p)-> getX() == x && (*p) ->getY() == y){
            return *p;
        }
    }
    return nullptr;
}
//Check if overlapping a player.
bool StudentWorld::overlappingPlayer(Actor* me) {
    if (m_player->isAlive() && overlapping(me, m_player))
        return true;
    return false;
}

//bool StudentWorld::overlapping(double x1, double y1, double x2, double y2) {
//    double dx = x1 - x2, dy = y1 - y2;
//    return dx * dx + dy * dy <= 100;
//}

//gets goodie pointer and assigns it to theifbot
Actor* StudentWorld::theifGoodie(Actor* a){
    for (Actor* b : my_map){
        if(b->isStolen() && b->canBeStolen()){
            int x = b->getX();
            int y = b->getY();
            if(a->getX() == x && a->getY() == y){
                b->setVisible(false);
                b->updateStolen(false);
                return b;
            }
        }
    }
    return nullptr;
}


//Check if two actors are overlapping
bool StudentWorld::overlapping(Actor* a, Actor* b) {
    return intersecting(a->getX(), a->getY(), b->getX(), b->getY());
}
//Check if two actors are intersecting
bool StudentWorld::intersecting(double x1, double y1, double x2, double y2) {
        if(x1 == x2 && y1 == y2){
            return true;
        }
        return false;


   }

//Check if a player is overlapping a goodie.
bool StudentWorld :: overlappingGoodie(Actor* a){
    return intersectingGoodie(a->getX(), a->getY(),m_player->getX(), m_player->getY());
}
//Check if a player is intersecting a goodie.
bool StudentWorld::intersectingGoodie(double x1, double y1, double x2, double y2) {
        if(x1 == x2 && y1==y2){
            playSound(SOUND_GOT_GOODIE);
            return true;
        }
        return false;
    }



//Increase peas
void StudentWorld::increasePeas() {
    m_player->increasePeas(20);
    playSound(SOUND_GOT_GOODIE);
}

//Increase health
void StudentWorld::restoreHealth() {
    m_player->restoreHealth(20);
    playSound(SOUND_GOT_GOODIE);
}
//Give extra life
void StudentWorld::extraLife() {
    incLives();
    playSound(SOUND_GOT_GOODIE);
}


//Check if something is overlapping the pit.
bool StudentWorld::overlappingPit(Actor* m) {
    for (Actor* x : my_map)
        if (x != m)
            if (x->eatsMarble() && overlapping(m, x)){
                m->setVisible(false);
                x->setVisible(false);
                x->die();
                m->die();
                
                return true;
            }
    return false;
}

//Set an actor to visible.
void StudentWorld::makeVisible(){
    for (Actor* j : my_map){
        if (j->eatsPlayer()){
            j->setVisible(true);
        }
            }

}
// Check if the peat hits any actor or player, and if so perform damage on that actor/player
bool StudentWorld::checkIfPeaHits(int x, int y) { //this x and y are the current position of the pea
    bool hit = false;
    for (Actor* actor : my_map) {
        if(actor->canKill() || actor->killsPeas()){
            if(actor->getX() == x && actor->getY() == y){
                actor->damage(2);
                hit = true;
            }
        }
    }
    
    if(m_player->getX() == x && m_player->getY() == y){
        m_player->damage(2);
        playSound(SOUND_PLAYER_IMPACT);

        hit = true;
    }

    return hit;
}


//Check if overlapping exit
bool StudentWorld::overlappingExit(Actor* m) {
    for (Actor* x : my_map)
        if (x != m)
            if (x->isAlive() && x->canExit() && overlapping(m, x))
                return true;
    return false;
}

//Check how many chrystals are left
int StudentWorld::cyrstalsLeft() {
   
    int c = 0;
    for (Actor* x : my_map)
        if (x->isAlive() && x->playerBonus()){
            c++;
        }

    return c;
}

// Get the pointer to the overlapping goodie
Actor* StudentWorld::getOverlappingObject(Actor* me) {
    for (Actor* actor : my_map) {
        if (actor != me && overlappingGoodie(me)) {
            return actor;
        }
    }
    return nullptr;
}


//get the player
Player* StudentWorld::getPlayer(){
    return m_player;
}

//See if there is an object the blocks the robot from shooting at the player
bool StudentWorld::blockedObject(Actor* me){
    int one = me->getX();
    int two = me->getY();
    for (Actor* actor : my_map) {
        int three = actor->getX();
        int four = actor->getY();
        
        if (one == three && two == four && actor ->blocksMovement()) {
            return false;
        }
    }
    return true;
}

//Check for obstecles in path
bool StudentWorld::noObstaclesInPath(int bX, int bY, int pX, int pY, int dir) {
    bool sameDirection = false;

    switch (dir) {
        case 0:
            sameDirection = (bY == pY && bX < pX);
            for (Actor* actor : my_map) {
                int actorX = actor->getX();
                int actorY = actor->getY();
                if (actorY == bY && actorX > bX && actorX < pX && actor->blocksDamage()) {
                    return false;
                }
            }
            break;
        case 90:
            sameDirection = (bX == pX && bY < pY);
            for (Actor* actor : my_map) {
                int actorX = actor->getX();
                int actorY = actor->getY();
                if (actorX == bX && actorY > bY && actorY < pY && actor->blocksDamage()) {
                    return false;
                }
            }
            break;
        case 180:
            sameDirection = (bY == pY && bX > pX);
            for (Actor* actor : my_map) {
                int actorX = actor->getX();
                int actorY = actor->getY();
                if (actorY == bY && actorX > pX && actorX < bX && actor->blocksDamage()) {
                    return false;
                }
            }
            break;
        case 270:
            sameDirection = (bX == pX && bY > pY);
            for (Actor* actor : my_map) {
                int actorX = actor->getX();
                int actorY = actor->getY();
                if (actorX == bX && actorY < bY && actorY > pY && actor->blocksDamage()) {
                    return false;
                }
            }
            break;
        default:
            break;
    }

    return sameDirection;
}
//Check if blocks movements
bool StudentWorld::isBlocked(double x, double y) {
    
    for (Actor* actor : my_map)  {
        if (actor->blocksMovement() && actor->getX() == x && actor->getY() == y) {
            return true;
        }
    }
    return false; 
}


//Check if bot can move
bool StudentWorld:: botCanMove(int a, int b){
    for (Actor* x : my_map){
            if ((x->getX()) == a && x->getY() == b){
                if(x->blocksMovement()){
                    return false;
                }
            }
        if(m_player->getX() == a && m_player->getY() == b){
            return false;
        }
    }
    return true;
}

//Check for souurounding robots
bool StudentWorld:: surroundingRobots(double x, double y){
    int count = 0;
    bool factorySquareOccupied = false;
    for (Actor* a : my_map){
        int robotX = static_cast<int>(a->getX());
                int robotY = static_cast<int>(a->getY());
                if (robotX >= x - 3 && robotX <= x + 3 && robotY >= y - 3 && robotY <= y + 3) {
                    if (a->eatsGoodie() && a->isAlive()) {
                        count++;
                    }
                if (robotX == static_cast<int>(x) && robotY == static_cast<int>(y)) {
                        factorySquareOccupied = true;
                    }
                }
        
    }
    if(count < 3 ){
        return true;
    }
    return false;
}


