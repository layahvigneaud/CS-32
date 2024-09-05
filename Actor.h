#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject // Base class, everything is derieved from
{
public:
    
    Actor(StudentWorld* world, int imageID, double x, double y, int dir) :
        GraphObject(imageID, x, y, dir),
        m_world(world) {
            alive = true;
            setVisible(true);
        };

    StudentWorld* getWorld() {
        return m_world;
    };
    virtual bool blocksMovement(){return true;}; //Blocks movement
    virtual bool killsPeas(){return false;}; //Kills peas
    virtual bool canExit() { return false; }; //Checks if something can exit
    virtual void doSomething() = 0 ;
    virtual void die() { // Kill
        alive = false;
    };
    virtual void updateStolen(bool value){ // Update a whether or not a goodie has been stolen.
        stolen = value;
    }
    virtual bool canBeStolen(){ //Check if a goodie canbe stolen
        return stolen;
    }
    virtual bool blocksDamage() { return true; } //Check if something blocks damage
    virtual bool canKill() { return false; }; //Check if something can be kiled
   virtual bool isAlive() { // Check if something is alive
        return alive;
    };
    
    virtual bool canMove(){  // Check if something can be moved
        return false;
    };
    virtual bool isGoodie(){ // Check if something is a goodie
        return false;
    }
    virtual bool eatsMarble() { return false; }; // Check if something eats a marble
    virtual bool eatsPlayer() { return false; }; // Check if something eats a player
    virtual bool eatsGoodie(){return false;} // Check if something eats a goodie
    virtual bool playerBonus() { return false; }; // Get players bonus
    virtual bool isStolen() { return false; }; //Check if stolen

    virtual void damage(int amount) {}; // Base damage class
//    virtual void attack(){
//        
//    }

private:
    StudentWorld* m_world;
    bool alive;
    bool stolen = true;
   
};





class MovingActor : public Actor {
public:
    MovingActor(StudentWorld* world, int imageID, double x, double y, int dir, int health): 
    Actor(world, imageID, x, y, dir), m_health(health)
    {
        
    }
    virtual void getPlayerRecord(int& x, int& y, int dir); //Gets record of moving object
    virtual void doSomething() {};
    virtual void shootPeas(); //Shoots peas
    virtual bool shouldFirePea(); //Checks if peas shoul be fired
  //  virtual void attack(){};

    int getHealth(){return m_health;}; // Gets health
    int updateHealth(int h){ //Updates health
        m_health = h;
        return m_health;
    };
   
private:
    int num_points;
    int m_health;
};


class Player : public MovingActor {
public:
    Player(StudentWorld* world, int imageID, double x, double y, int dir, int health):  MovingActor(world, imageID, x,  y, dir, health), num_peas(20)
    
    {
        
    }
    virtual bool canMove(){
        return true;
    };
    virtual bool canKill(){return true;}; //Change boolean value
    virtual bool killsPeas(){return true;}; //Change boolean value
    virtual bool blocksDamage() { return false; } //Change boolean value
    virtual void damage(int amount); //Player damage
    virtual void doSomething();
    virtual bool canExit() { return true; }; //Change boolean value
    void increasePeas(int n){num_peas += n;}; //Increases peas
    int getAmmo(){ //returns ammo
        return num_peas;
    }

    int getBonus(){ //gets bonus
        if(bonus >= 0){
            return bonus;
        }
        else{
            bonus = 0;
            return bonus;
        }
    }
    void restoreHealth(int n){ //restores health
        updateHealth(20);
    };

private:
    int bonus = 1000;
    int num_peas = 20;
    
    int player_health = 20;
    int num_points = 0;
    
};

class Exits : public Actor {
public:
    Exits(StudentWorld* world, int imageID, double x, double y, int dir):  Actor(world, imageID, x, y, dir), play(true)
    {
        setVisible(false);
    }
    virtual void doSomething();
    virtual bool eatsPlayer() { return true; }; //Change boolean value
    //bool visability();
private:
    bool play;

};

class Walls : public Actor {
public:
    Walls(StudentWorld* world, int imageID, double x, double y, int dir):  Actor(world, imageID, x, y, dir)
    {
        
    }
    virtual void doSomething() {};
    //virtual void attack(){};
     bool killsPeas() {return true;}; //Change boolean value
    //virtual bool blocksDamage() { return true; }
};

class Pits : public Actor {
public:
    Pits(StudentWorld* world, int imageID, double x, double y, int dir):  Actor(world, imageID, x, y, dir)
    {
        
    }
    //virtual bool blocksMovement(){return false;};
   // virtual bool killsPeas() { return false; };
    virtual bool blocksDamage() { return false; }; //Change boolean value
    virtual bool eatsMarble() { return true; }; //Change boolean value
    virtual void doSomething(){};
   
};




class Marbles : public MovingActor {
public:
    Marbles(StudentWorld* world, int imageID, double x, double y, int dir, int health = 20):  MovingActor(world, imageID, x,  y, dir, health)
    {
        
    }
    virtual void doSomething();
    virtual bool canKill(){return true;}; //Change boolean value
    virtual bool killsPeas(){return true;}; //Change boolean value
    virtual bool canMove(){ //Change boolean value
        return true;
    };
    
    virtual void damage(int amount){ //Marble damage
        // Subtract 'amount' from the actor's hit points
        marble_num -= amount;

        // Check if the actor has run out of hit points
        if (marble_num <= 0) {
            // Set the actor's state to dead
            die();
        }
    };
private:
    int marble_num = 10;
    
};

class  Peas : public MovingActor {
public:
   // virtual bool blocksDamage() { return false; }
    //virtual bool blocksDamage(){return true;}
    virtual void doSomething();
    void move();
    Peas(StudentWorld* world, int imageID, double x, double y, int dir, int health):  MovingActor(world, imageID, x,  y, dir, health)
    {
        setVisible(true);
    }
};




class Goodie : public Actor {
public:
    Goodie(StudentWorld* world, int imageID, double x, double y) :
    Actor(world, imageID, x, y, 1) {};
   
    
    virtual bool blocksDamage() { return false; } //Change boolean value
    virtual void doSomething();
    virtual bool blocksMovement(){return false;}; //Change boolean value
    virtual bool isGoodie(){ //Change boolean value
        return true;
    }
    
private:
//    bool stolen = false;
    virtual void giveGoodie() = 0;
};




class Ammo : public Goodie {
public:
    Ammo(StudentWorld* world, int imageID, double x, double y):  Goodie(world, imageID, x, y)
    {
        
    }
    virtual bool isStolen() { return true; }; //Change boolean value
private:
    virtual void giveGoodie(); // Gives goodie to player
   
};

class ExtraLife : public Goodie {
public:
    ExtraLife(StudentWorld* world, int imageID, double x, double y):  Goodie(world, imageID, x, y)
    {
        
    }
    virtual bool isStolen() { return true; }; //Change boolean value

private:
    virtual void giveGoodie(); //Gives goodie to player
   
};
class RestorLife : public Goodie {
public:
    RestorLife(StudentWorld* world, int imageID, double x, double y):  Goodie(world, imageID, x, y)
    {
        
    }
    virtual bool isStolen() { return true; }; //Change boolean value
private:
    virtual void giveGoodie(); //Gives goodie to player
   
};

class Crystals : public Goodie {
public:
    Crystals(StudentWorld* world, int imageID, double x, double y):  Goodie(world, imageID, x, y)
    {
        
    }
    virtual bool playerBonus() { return true; }; //Change boolean value
private:
    virtual void giveGoodie(); //Gives goodie to player
   
};




class TheifBot : public MovingActor {
public:
    TheifBot(StudentWorld* world, int imageID, double x, double y, int dir)
    : MovingActor(world, imageID, x, y, dir, 5), m_ticks(0) {
        setVisible(true);
        m_distanceBeforeTurning = rand() % 6 + 1;
    }
    virtual bool killsPeas(){return true;}; //Change boolean value
    virtual bool canKill() { return true; }; //Change boolean value
    virtual bool blocksMovement(){return true;}; //Change boolean value
    virtual void doSomething();
    virtual void damage(int amount){ //Robot damage
        mT_hit_points-=amount;
        if(mT_hit_points <= 0){
            duringDeath();
            die();
            
        }
        };
    void moveThiefBot(Actor* b); //Moves thiefBot
    virtual void duringDeath(); //Drops goddie if goodie is with bot
    virtual bool eatsGoodie(){return true;} //Change boolean value
    //virtual bool shouldFirePea();
    virtual int get_points(){ //Gets hit points
        return mT_hit_points;
    };
    virtual bool hasGoodie(){ //Checks if it has a goodie
        return m_goodie != nullptr;
    }
    virtual void updateGoodie(Actor* value){ //Gives goodie pointer to m_goodie
        m_goodie = value;
    }
    virtual Actor* getGoodie(){ //gets goodie
        return  m_goodie;
    }
    
private:
    int m_ticks = 0; // Current tick count
        int m_restTicks = 0; // Number of ticks to rest
        //bool m_facingPlayer;
       int mT_hit_points = 5;
    Actor* m_goodie = nullptr;
    int m_distanceBeforeTurning;
   
};

class MeanTheifBot : public TheifBot {
public:
    // Constructor
    MeanTheifBot(StudentWorld* world, int imageID, double x, double y, int dir)
        : TheifBot(world, imageID, x, y, dir)
    {
      
    }
    //virtual bool shouldFirePea();
    virtual void doSomething();
    virtual void damage(int amount){ //Robot damage
        mT_hit_points-=amount;
        if(mT_hit_points <= 0){
            die();
            duringDeath();

            
        }
        };
private:
    int m_ticks = 0; // Current tick count
        int m_restTicks = 0; // Number of ticks to rest
        //bool m_facingPlayer;
       int mT_hit_points = 5;
    bool goodie = false;
    int m_distanceBeforeTurning;
};

class RageBot : public MovingActor {
public:
    RageBot(StudentWorld* world, int imageID, double x, double y, int dir)
    : MovingActor(world, imageID, x, y, dir, 10), m_ticks(0) {
        setVisible(true); // Make RageBot visible
       
    }
    virtual void damage(int amount); //Ragebot damage
    virtual bool canKill(){return true;}; //Change boolean value
    virtual bool killsPeas(){return true;}; //Change boolean value
    //virtual bool shouldFirePea();
    virtual void doSomething();
    virtual int get_points(){ //Get hit points
        return m_hit_points;
    };
    
private:
    int m_ticks = 0; // Current tick count
        int m_restTicks = 0; // Number of ticks to rest
       int m_hit_points = 10;
};

class Factory : public Actor {
public:
    Factory(StudentWorld* world, int imageID, double startX, double startY, int type)
            : Actor(world, imageID, startX, startY, 1) {
            m_type = type;
        }
    virtual void doSomething();
    
private:
    int m_type; //Checks for mean theifbot factory or other factory
    
};







#endif // ACTOR_H_
