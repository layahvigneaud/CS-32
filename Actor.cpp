#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void MovingActor::getPlayerRecord(int& x, int& y, int dir){ //Gets the new position of an actor in the game
    int newX = this->getX();
    int newY = this->getY();
    switch(dir){
        case 0: // moves x or y based on direction
            newX++;
            break;
        case 90:
            newY++;
            break;
        case 180:
            newX--;
            break;
        case 270:
            newY--;
            break;
    }
    x = newX; //Sets new x or y
    y = newY;
 }
// Damages the player and updates Plyaers health.
void Player:: damage(int amount){
    player_health-=amount;
    //getWorld()->playSound(SOUND_PLAYER_IMPACT);
    if(player_health <= 0)
    {
        die();
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
    else{
        
        updateHealth(player_health);
    }
};
//Moves player
void Player::doSomething() {
    if(isAlive()){ //Check if alive
        bonus--;
        int ph;
        int x = this->getX();
        int y = this->getY();
        if(this->getWorld()->getKey(ph)){ //gets direction of player
            switch (ph)
            {
                case KEY_PRESS_ESCAPE:
                    this->die();
                    return;
                
                case KEY_PRESS_SPACE: { //Player shoot peas
                    if(num_peas > 0){
                        num_peas--;
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        shootPeas();
                    }
                    break;
                }
                case KEY_PRESS_LEFT: //Player going left
                {
                    this->setDirection(180);
                    getPlayerRecord(x,y,180);
                    break;
                }
                    
                case KEY_PRESS_RIGHT: //Player going right
                {
                    this->setDirection(0);
                    getPlayerRecord(x,y,0);
                    break;
                }
                    
                case KEY_PRESS_UP: // Player going up
                {
                    this->setDirection(90);
                    getPlayerRecord(x,y,90);
                    break;
                }
                case KEY_PRESS_DOWN: //Player going down
                {
                    this->setDirection(270);
                    getPlayerRecord(x,y,270);
                    break;
                }
                default:
                    break;
            }
            Actor* move = (getWorld()->validPos(x, y)); //Checks if next space is open to move
            if(getDirection() == 90)
                        {
                            
                            if (move == nullptr && this->canMove()) { // If space is open move player.
                                moveTo(x, y);
                                
                            }
                            else if (move->eatsPlayer() && this->canMove()) { //Allows player to move on exit
                                moveTo(x, y);
                                
                            }
                            else if(move != nullptr && move->isGoodie() && move->getWorld()->blockedObject(move)){ //Move plyer onto goodie
                                moveTo(x, y);
                            }
                            else if(move != nullptr && move->canMove()){
                                
                                if((getWorld()->validPos(x, y + 1)) == nullptr && this->canMove()&& !(this->eatsPlayer())) //If space is open move, and player is pushing marble move space and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x, y + 1);
                                    
                                }
                                else if((getWorld()->validPos(x, y + 1))->eatsMarble() && this->canMove() && !(this->eatsPlayer())) //If space has a pit and player is pushing marble move player and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x, y + 1);
                                    
                                }
                            }
                           
                        }
                        if(getDirection() == 270)
                        {
                            if (move == nullptr && this->canMove()) { // If space is open move player.
                                moveTo(x, y);
                                
                            }
                            else if (move->eatsPlayer() && this->canMove()) {  //Allows player to move on exit
                                moveTo(x, y);
                                
                            }
                            else if(move != nullptr && move->isGoodie() && move->getWorld()->blockedObject(move)){//Move plyer onto goodie
                                moveTo(x, y);
                            }
                            else if(move != nullptr && move->canMove()){
                                if((getWorld()->validPos(x, y -1)) == nullptr && this->canMove() && !(this->eatsPlayer())) //If space is open move, and player is pushing marble move space and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x, y - 1);
                                    
                                }
                                
                                else if((getWorld()->validPos(x, y-1))->eatsMarble() && this->canMove()  && !(this->eatsPlayer())) //If space has a pit and player is pushing marble move player and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x, y -1);
                                    
                                }
                            }
                            
                            
                        }
                        if(getDirection() == 180)
                        {
                            if (move == nullptr && this->canMove()) { // If space is open move player.
                                moveTo(x, y);
                                
                            }
                            else if (move->eatsPlayer() && this->canMove()) {  //Allows player to move on exit
                                moveTo(x, y);
                                
                            }
                            else if(move != nullptr && move->isGoodie() && move->getWorld()->blockedObject(move)){  //Move plyer onto goodie
                                moveTo(x, y);
                            }
                            else if(move != nullptr && move->canMove()){
                                
                                if((getWorld()->validPos(x - 1, y)) == nullptr && this->canMove() && !(this->eatsPlayer())) //If space is open move, and player is pushing marble move space and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x - 1, y);
                                    
                                }
                                else if((getWorld()->validPos(x-1, y))->eatsMarble() && this->canMove() && !(this->eatsPlayer()))//If space has a pit and player is pushing marble move player and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x-1, y);
                                    
                                }
                                
                            }
                           
                        }
                        if(getDirection() == 0)
                        {
                            if (move == nullptr && this->canMove()) { // If space is open move player.
                                moveTo(x, y);
                                
                            }
                            else if (move->eatsPlayer() && this->canMove()) {  //Allows player to move on exit
                                moveTo(x, y);
                                
                            }
                            else if(move != nullptr && move->isGoodie() && move->getWorld()->blockedObject(move)){  //Move plyer onto goodie
                                moveTo(x, y);
                            }
                            else if(move != nullptr && move->canMove()){
                                
                                if((getWorld()->validPos(x + 1, y)) == nullptr && this->canMove() && !(this->eatsPlayer()))//If space is open move, and player is pushing marble move space and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x + 1, y);
                                    
                                }
                                else if((getWorld()->validPos(x+1, y))->eatsMarble() && this->canMove() && !(this->eatsPlayer()))//If space has a pit and player is pushing marble move player and marble.
                                {
                                    moveTo(x, y);
                                    move ->moveTo(x+1, y);
                                    
                                }
                            }
                        }
        }
    
        
        if(getWorld()->cyrstalsLeft() == 0){ //Makes exit visible after cyrstals are gone.
            this->getWorld()->makeVisible();
        }
        
    }
}



void Marbles::doSomething() {
    // Check if the marble overlaps with a pit
    if (getWorld()->overlappingPit(this)) {
        // Set the marble to invisible
        setVisible(false);
    }
}

void MovingActor::shootPeas() {
//Get the direction of the Pea
    int dir = this->getDirection();
    int px = getX(), py = getY();
//Get the position of the pea
    this->getPlayerRecord(px,py,getDirection());
//Add pea
    this->getWorld()->addPea(px, py, dir);
    
}

void Peas::move() {
    // Get the current position of the pea
    double x = getX();
    double y = getY();
    
    // Get the direction of the pea
    int dir = getDirection();
    
    // Update the position based on the direction
    switch (dir) {
        case 0:  // Moving right
            x ++;  // Assuming SPRITE_WIDTH_GL is the width of a grid square
            break;
        case 90:  // Moving up
            y ++;  // Assuming SPRITE_HEIGHT_GL is the height of a grid square
            break;
        case 180:  // Moving left
            x --;
            break;
        case 270:  // Moving down
            y --;
            break;
        default:
            // Handle invalid direction
            break;
    }
    
}


void Peas:: doSomething(){
    // Cheack if pea is alive
    if (isAlive()) {
        if(getWorld()->checkIfPeaHits(getX(), getY())){ //Check if pea hits something
            die();
            return;
        }
        
        int x,y;
        this->getPlayerRecord(x,y,getDirection()); //Gets pea's new position.
    
        this->moveTo(x,y); //Moves pea
      
        if(getWorld()->checkIfPeaHits(getX(), getY())){ //Check if pea hits something
            die();
            return;
        }
    }
}


void Goodie:: doSomething(){
    //Cheack if overlaping goodie
    if (getWorld()->overlappingGoodie(this) && canBeStolen()) {
       this->setVisible(false);
            die();
           //Give the goodie to the player
            giveGoodie();
            return;
        }
   
}




void Ammo::giveGoodie() {
    //Increase players peas and score.
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(100);
    getWorld()->increasePeas();
}

void RestorLife::giveGoodie(){
    //Increase players health and score.
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(500);
    getWorld()->restoreHealth();
}
void ExtraLife::giveGoodie(){
    //Increase players lives and score.
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(1000);
    getWorld()->extraLife();
}

void Crystals::giveGoodie(){
    //Increase players score.
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(50);
    this->die();
}
void Exits::doSomething() {
    if(getWorld()->cyrstalsLeft() == 0){ //If zero cyrstals are left reveal exit
        if(play){
            getWorld()->playSound(SOUND_REVEAL_EXIT);
            play = false;
        }
        if (getWorld()->overlappingPlayer(this)){ //Only then if player overlapps exit level is completed
            getWorld()->levelCompleted();
            getWorld()->playSound(SOUND_FINISHED_LEVEL);
        }
    }


   
}
void TheifBot:: doSomething(){
    if (!isAlive()) //Check is thiefbot is alive.
        return;
    

    // Check if it's time for the TheifBot to rest
    if (m_ticks == m_restTicks) {
        int levelNumber = getWorld()->getLevel();
        m_restTicks = (28 - levelNumber) / 4;
        if (m_restTicks < 3)
            m_restTicks = 3;

        m_ticks = 0;
    }

   

    // Increment the ticks counter
    m_ticks++;
    int chance = randInt(1, 10);
    if(!(hasGoodie()) && chance == 1){
        Actor* value = getWorld()->theifGoodie(this); //Check for goodie to steal
        if (value != nullptr) {
            updateGoodie(value);
            getWorld()->playSound(SOUND_ROBOT_MUNCH);
        }
    }
 //If it is time for a thief bot to move, then move.
    if (m_ticks == m_restTicks) {
        moveThiefBot(this);
    }
   
}


void TheifBot::moveThiefBot(Actor* b) {
    //Get current x, y and direction
    int currentX = b->getX();
    int currentY = b->getY();
    int currentDirection = b->getDirection();

    int nextX = currentX;
    int nextY = currentY;
    getPlayerRecord(nextX, nextY, currentDirection); // get next actors next spot

    
    if (m_distanceBeforeTurning > 0 && getWorld()->botCanMove(nextX, nextY)) { //Move until it is time to picka new random direction.
       
        moveTo(nextX, nextY);
        m_distanceBeforeTurning--;
        return; // Do nothing more during the current tick
    }

    m_distanceBeforeTurning = rand() % 6 + 1; // Randomize distance before turning
    currentDirection = (((rand() % 4) * 90) % 360); // Get a new random direction
    setDirection(currentDirection); // Set the new direction
}

//FIX
void TheifBot:: duringDeath() {
    getWorld()->playSound(SOUND_ROBOT_DIE);
    Actor* x = getGoodie();
    if(x != nullptr){
        x->moveTo(this->getX(), this->getY()); // Move goodie to robots location
        x->setVisible(true); // Make goodie visible.
        x->updateStolen(true); //Say the goodie can be stolen again.
        updateGoodie(nullptr); //set goodie robot was holding to nullptr.
    }
    
//    if (hasGoodie()) { //If a thiefBot has a goodie
//
//        Actor* x = getGoodie(); //Set x to that goodie
//        if(x != nullptr){
//            if(x == nullptr){
//                return;
//            }
//            x->moveTo(this->getX(), this->getY()); // Move goodie to robots location
//            x->setVisible(true); // Make goodie visible.
//            x->updateStolen(true); //Say the goodie can be stolen again.
//            updateGoodie(nullptr); //set goodie robot was holding to nullptr.
//        }
//        
//    }
    
    return;
}



void MeanTheifBot:: doSomething(){
    if (!isAlive())
        return;

    // Check if it's time for the TheifBot to rest
    if (m_ticks == m_restTicks) {
        int levelNumber = getWorld()->getLevel();
        m_restTicks = (28 - levelNumber) / 4;
        if (m_restTicks < 3)
            m_restTicks = 3;

        m_ticks = 0;
    }

   

    // Increment the ticks counter
    m_ticks++;
    if (shouldFirePea()) { //Check is the robot should fire peas
        getWorld()->playSound(SOUND_ENEMY_FIRE);
        if (m_ticks == m_restTicks){
            shootPeas();
        }
    }
    if(!(hasGoodie())){
        Actor* a = getWorld()->theifGoodie(this); // Check fo goodie to steal
        if (a != nullptr) {
            updateGoodie(a);
            getWorld()->playSound(SOUND_ROBOT_MUNCH);
        }
    }

    if (m_ticks == m_restTicks) { // Checkif robot should move
        moveThiefBot(this);
    }
   
}


void RageBot::damage(int amount){ // Damages ragebot
    m_hit_points-=amount;
    getWorld()->playSound(SOUND_ROBOT_IMPACT);
    if(m_hit_points <= 0)
    {
    getWorld()->playSound(SOUND_ROBOT_DIE);
     die();
}
};


void RageBot::doSomething() {
    // Check if RageBot is alive
    if (!isAlive())
        return;

    // Check if it's time for the RageBot to rest
    if (m_ticks == m_restTicks) {
        int levelNumber = getWorld()->getLevel();
        m_restTicks = (28 - levelNumber) / 4;
        if (m_restTicks < 3)
            m_restTicks = 3;

        m_ticks = 0;
    }

   
   

    // Increment the ticks counter
    m_ticks++;
    bool doesAnything = true;
    if (shouldFirePea()) {  // Check if the RageBot should fire its pea cannon
        doesAnything = false;
       
        if (m_ticks == m_restTicks){
            cout << "Vibes" << endl;
            
            cout << "Cool" << endl;
            shootPeas();
           
        }
    }
    // Only move if it's time for the RageBot to act
    if (m_ticks == m_restTicks) {
        double x = getX();
        double y = getY();

        // Compute the next position based on the direction
        double nextX = x;
        double nextY = y;
        switch (getDirection()) {
            case 0:  // Moving right
                nextX += 1;
                break;
            case 90:  // Moving up
                nextY += 1;
                break;
            case 180:  // Moving left
                nextX -= 1;
                break;
            case 270:  // Moving down
                nextY -= 1;
                break;
            default:
                // Handle invalid direction
                break;
        }

        // Check if the next spot has an object that blocks damage
        if ((doesAnything) && getWorld()->isBlocked(nextX, nextY)) {
            // Change direction to the opposite
            setDirection((getDirection() + 180) % 360);
        } else if(doesAnything) {
            // Move to the next spot
            moveTo(nextX, nextY);
        }
    }
}
bool MovingActor:: shouldFirePea(){
    int playerX = getWorld()->getPlayer()->getX();
        int playerY = getWorld()->getPlayer()->getY();

        // Get the coordinates of the RageBot
        int rageBotX = getX();
        int rageBotY = getY();

        // Check if the player is in the same row or column as the RageBot
        if (playerX == rageBotX || playerY == rageBotY) {
            // Check if the RageBot is currently facing the player
            int dir = getDirection();

                if (getWorld()->noObstaclesInPath(rageBotX, rageBotY, playerX, playerY, dir)) { //check for obstecles in path
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    return true;
                    
                }
       }
        return false;
}




 void Factory:: doSomething(){
     if ((getWorld()->surroundingRobots(getX(), getY()))){ // Checks for surrounding robots
         int chance = randInt( 1, 50);
             if (chance == 1) {
                 if(m_type  == 0){
                     getWorld()->addTheifBot(getX(), getY(), 0); // //If chance is one in 50 add robot
                     getWorld()->playSound(SOUND_ROBOT_BORN);
                 }
                 else{
                     getWorld()->addMeanTheifBot(getX(), getY(), 0);
                     getWorld()->playSound(SOUND_ROBOT_BORN);
                 }
               
                 }
     }
 };
