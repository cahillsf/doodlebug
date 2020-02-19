//
//  main.cpp
//  sc2891_hw13_doodlebug
//
//  Created by Stephen Cahill on 4/14/19.
//  Copyright © 2019 Stephen Cahill. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int numOfColumns = 20;
const int numOfRows = 20;

class Organism{
public:
    Organism();
    Organism(int fIndex, int sIndex, int myAge, int myIdNumber);
    Organism(int myIdNumber);
    int get_first_index() const;
    int get_second_index() const;
    int get_age() const;
    int get_idNumber() const;
    bool get_life_status() const;
    virtual char get_symbol();
    void set_first_index(int newFirstIndex);
    void set_second_index(int newSecondIndex);
    void set_age(int newAge);
    void set_id_number(int newIdNumber);
    void set_symbol(char newSymbol);
    void set_life_status(bool newStatus);
    virtual void out_symbol();
    virtual void move();
    virtual void breed(){};
    
private:
    char symbol;
    int firstIndex;
    int secondIndex;
    int age;
    int idNumber;
    bool isAlive;
};

class Space: public Organism
{
public:
    Space();
    virtual void out_symbol();
    virtual char get_symbol();
    
    
private:
    char symbol;
};

class Ant: public Organism{
public:
    Ant();
    virtual void out_symbol();
    virtual char get_symbol();
    virtual void move(Organism* gridArray[numOfRows][numOfColumns], Space spacesArray[]);
    virtual void breed(Organism* gridArray[numOfRows][numOfColumns], Ant antArray[], int &antCounter);
    
    
private:
    char symbol;
};

class Doodlebug: public Organism{
public:
    Doodlebug();
    
    void set_time_since_meal(int newTime);
    int get_time_since_meal() const;
    virtual void out_symbol();
    virtual char get_symbol();
    virtual void move(Organism* gridArray[numOfRows][numOfColumns], Doodlebug doodleBugArray[], Space spacesArray[]);
    virtual void breed(Organism* gridArray[numOfRows][numOfColumns], Doodlebug doodleBugArray[], int &doodleBugCounter);
    void starve(Organism* gridArray[numOfRows][numOfColumns], Space spacesArray[]);
    
    
private:
    char symbol;
    int timeSinceMeal;
};

void initiate_time_step(Organism* gridArray[numOfRows][numOfColumns], Ant antArr[], Space spaceArr[], Doodlebug doodlebugArr[], int &antCounter, int &doodlebugCounter);

int find_next_available_index(Doodlebug arr[]);
int find_next_available_index(Ant arr[]);
int main(){
    srand(time(0)%100);
    int doodlebugCount = 0;
    int antCount = 0;
    int tempFirstI, tempSecondI;
    Space spaceArray[1];
    Doodlebug doodlebugArray[400];
    Ant antArray[400];

    
    Organism* gameSpace[20][20];
    for(int c = 0; c < 20; c++){
        for (int i = 0; i < 20; i++){
            gameSpace[c][i] = nullptr;
        }
    }
    while (doodlebugCount < 5){
        bool spawned = false;
        while(spawned == false){
            tempFirstI = rand() % 20;
            tempSecondI = rand() % 20;
            if(gameSpace[tempFirstI][tempSecondI] == nullptr){
                gameSpace[tempFirstI][tempSecondI] = &doodlebugArray[doodlebugCount];
                gameSpace[tempFirstI][tempSecondI]->set_first_index(tempFirstI);
                gameSpace[tempFirstI][tempSecondI]->set_second_index(tempSecondI);
                gameSpace[tempFirstI][tempSecondI]->set_life_status(true);
                doodlebugCount++;
                spawned = true;
            }
        }
    }

    
    while (antCount < 100){
        bool spawned = false;
        while(spawned == false){
            tempFirstI = rand() % 20;
            tempSecondI = rand() % 20;
            if(gameSpace[tempFirstI][tempSecondI] == nullptr){
                gameSpace[tempFirstI][tempSecondI] = &antArray[antCount];
                gameSpace[tempFirstI][tempSecondI]->set_first_index(tempFirstI);
                gameSpace[tempFirstI][tempSecondI]->set_second_index(tempSecondI);
                gameSpace[tempFirstI][tempSecondI]->set_life_status(true);
                antCount++;
                spawned = true;
            }
        }
    }
  

    
    for(int c = 0; c < numOfColumns; c++){
        for (int i = 0; i < numOfRows; i++){
            if (gameSpace[c][i] == nullptr){
                gameSpace[c][i] = &spaceArray[0];
            }
        }
    }
    for(int c = 0; c < numOfColumns; c++){
        for (int i = 0; i < numOfRows; i++){
            gameSpace[c][i]->out_symbol();
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<"World has been initialized with 100 ants and 5 doodlebugs."<<endl;
    char test;
    bool seenEnd = false;
    while(seenEnd == false){
        cout<<"Press enter to initiate time step: ";
        test = fgetc(stdin);
        if(test == '\n'){
            initiate_time_step(gameSpace, antArray, spaceArray, doodlebugArray, antCount, doodlebugCount);
            seenEnd = false;
        }
        else
            seenEnd = true;
    }


    return 0;
}


Organism::Organism(){
    firstIndex = -1;
    secondIndex = -1;
    age = 0;
    idNumber = -1;
    isAlive = false;
}

Organism::Organism(int fIndex, int sIndex, int myAge, int myIdNumber){
    firstIndex = fIndex;
    secondIndex = sIndex;
    age = myAge;
    idNumber = myIdNumber;
    
}

Organism::Organism(int myIdNumber){
    firstIndex = -1;
    secondIndex = -1;
    age = 0;
    idNumber = myIdNumber;
    
}

int Organism::get_first_index() const{
    return firstIndex;
}

int Organism::get_second_index() const{
    return secondIndex;
}

int Organism::get_age() const{
    return age;
}

int Organism::get_idNumber() const{
    return idNumber;
}

bool Organism::get_life_status() const{
    return isAlive;
}

void Organism::set_first_index(int newFirstIndex){
    firstIndex = newFirstIndex;
}
void Organism::set_second_index(int newSecondIndex){
    secondIndex = newSecondIndex;
}
void Organism::set_age(int newAge){
    age = newAge;
}

void Organism::set_id_number(int newIdNumber){
    idNumber = newIdNumber;
    
}

void Organism:: set_life_status(bool newStatus){
    isAlive = newStatus;
}

char Organism::get_symbol(){
    return symbol;
}


void Organism::out_symbol(){
    cout<<"here's your problem"<<endl;
};

void Organism::move(){
    cout<<"move"<<endl;
};


Space::Space():Organism(), symbol('-'){};

void Space:: out_symbol() {
    cout<<symbol;
}

char Space:: get_symbol(){
    return symbol;
}

Ant::Ant():Organism(), symbol('o'){};

void Ant:: out_symbol() {
    cout<<symbol;
}

char Ant:: get_symbol(){
    return symbol;
}


void Ant::move(Organism* gridArray[numOfRows][numOfColumns], Space spacesArray[]){
    int decision = rand() % 4;
    set_age(get_age() + 1);
    if (decision == 0){
        if ((get_first_index() - 1 >= 0) && (gridArray[get_first_index() - 1][get_second_index()]->get_symbol() == '-'))
        {
            gridArray[get_first_index() - 1][get_second_index()] = this;
            gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
            set_first_index(get_first_index() - 1);
        }
    }
    else if (decision == 1){
        if ((get_second_index() + 1 <= 19) && (gridArray[get_first_index()][get_second_index() + 1]->get_symbol() == '-'))
        {
            gridArray[get_first_index()][get_second_index() + 1] = this;
            gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
            set_second_index(get_second_index() + 1);
        }
    }
    
    else if (decision == 2){
        if ((get_first_index() + 1 <= 19) && (gridArray[get_first_index() + 1][get_second_index()]->get_symbol() == '-'))
        {
            gridArray[get_first_index() + 1][get_second_index()] = this;
            gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
            set_first_index(get_first_index() + 1);
        }
    }
    
    else if (decision == 3){
        if ((get_second_index() - 1 >= 0) && (gridArray[get_first_index()][get_second_index() - 1]->get_symbol() == '-'))
        {
            gridArray[get_first_index()][get_second_index() - 1] = this;
            gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
            set_second_index(get_second_index() - 1);
        }
    }
    else{};
}
void Ant::breed(Organism* gridArray[numOfRows][numOfColumns], Ant antArray[], int &antCounter){
    if(get_age() > 0 && get_age() % 3 == 0){
        bool seenFlag = false;
        int nextAvailIndex = find_next_available_index(antArray);
        bool northCell = false, eastCell = false, southCell = false, westCell = false;
        while(seenFlag == false && ((northCell == false) || (eastCell == false) || (southCell == false) || (westCell == false))){
            int decision = rand() % 4;
            if(decision == 0){
                northCell = true;
                if ((get_first_index() - 1 >= 0) && (gridArray[get_first_index() - 1][get_second_index()]->get_symbol() == '-'))
                {
                    gridArray[get_first_index() - 1][get_second_index()] = &antArray[nextAvailIndex];
                    antArray[nextAvailIndex].set_first_index(get_first_index() - 1);
                    antArray[nextAvailIndex].set_second_index(get_second_index());
                    antArray[nextAvailIndex].set_life_status(true);
                    seenFlag = true;
                }
            }
            else if(decision == 1){
                eastCell = true;
                if ((get_second_index() + 1 <= 19) && (gridArray[get_first_index()][get_second_index() + 1]->get_symbol() == '-')){
                    gridArray[get_first_index()][get_second_index() + 1] = &antArray[nextAvailIndex];
                    antArray[nextAvailIndex].set_first_index(get_first_index());
                    antArray[nextAvailIndex].set_second_index(get_second_index() + 1);
                    antArray[nextAvailIndex].set_life_status(true);
                    seenFlag = true;
                }
            }
            else if (decision == 2){
                southCell = true;
                if ((get_first_index() + 1 <= 19) && (gridArray[get_first_index() + 1][get_second_index()]->get_symbol() == '-')){
                    gridArray[get_first_index() + 1][get_second_index()] = &antArray[nextAvailIndex];
                    antArray[nextAvailIndex].set_first_index(get_first_index() + 1);
                    antArray[nextAvailIndex].set_second_index(get_second_index());
                    antArray[nextAvailIndex].set_life_status(true);
                    seenFlag = true;
                }
            }
            else if (decision == 3){
                westCell = true;
                if ((get_second_index() - 1 >= 0) && (gridArray[get_first_index()][get_second_index() - 1]->get_symbol() == '-')){
                    gridArray[get_first_index()][get_second_index() - 1] = &antArray[nextAvailIndex];
                    antArray[nextAvailIndex].set_first_index(get_first_index());
                    antArray[nextAvailIndex].set_second_index(get_second_index() - 1);
                    antArray[nextAvailIndex].set_life_status(true);
                    seenFlag = true;
                }
            }
        }
    }
}


Doodlebug::Doodlebug(): Organism(), symbol('X'), timeSinceMeal(0){};

void Doodlebug:: out_symbol() {
    cout<<symbol;
}

char Doodlebug:: get_symbol(){
    return symbol;
}

void Doodlebug:: set_time_since_meal(int newTime){
    timeSinceMeal = newTime;
}
int Doodlebug:: get_time_since_meal() const{
    return timeSinceMeal;
}

void Doodlebug:: move(Organism* gridArray[numOfRows][numOfColumns], Doodlebug doodleBugArray[], Space spacesArray[]){
    set_age(get_age() + 1);
    bool seenFlag = false;
    bool northCell = false, eastCell = false, southCell = false, westCell = false;
    while(seenFlag == false && ((northCell == false) || (eastCell == false) || (southCell == false) || (westCell == false))){
        int decision = rand() % 4;
        if(decision == 0){
            northCell = true;
            if ((get_first_index() - 1 >= 0) && (gridArray[get_first_index() - 1][get_second_index()]->get_symbol() == 'o'))
            {
                gridArray[get_first_index() - 1][get_second_index()]->set_life_status(false);
                gridArray[get_first_index() - 1][get_second_index()]->set_age(0);
                gridArray[get_first_index() - 1][get_second_index()] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_first_index(get_first_index() - 1);
                set_time_since_meal(0);
                seenFlag = true;
            }
        }
        else if(decision == 1){
            eastCell = true;
            if ((get_second_index() + 1 <= 19) && (gridArray[get_first_index()][get_second_index() + 1]->get_symbol() == 'o')){
                gridArray[get_first_index()][get_second_index() + 1]->set_life_status(false);
                gridArray[get_first_index()][get_second_index() + 1]->set_age(0);
                gridArray[get_first_index()][get_second_index() + 1] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_second_index(get_second_index() + 1);
                set_time_since_meal(0);
                seenFlag = true;
            }
        }
        else if(decision == 2){
            southCell = true;
            if ((get_first_index() + 1 <= 19) && (gridArray[get_first_index() + 1][get_second_index()]->get_symbol() == 'o')){
                gridArray[get_first_index() + 1][get_second_index()]->set_life_status(false);
                gridArray[get_first_index() + 1][get_second_index()]->set_age(0);
                gridArray[get_first_index() + 1][get_second_index()] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_first_index(get_first_index() + 1);
                set_time_since_meal(0);
                seenFlag = true;
            }
        }
        else if(decision == 3){
            westCell = true;
            if ((get_second_index() - 1 >= 0) && (gridArray[get_first_index()][get_second_index() - 1]->get_symbol() == 'o')){
                gridArray[get_first_index()][get_second_index() - 1]->set_life_status(false);
                gridArray[get_first_index()][get_second_index() - 1]->set_age(0);
                gridArray[get_first_index()][get_second_index() - 1] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_second_index(get_second_index() - 1);
                set_time_since_meal(0);
                seenFlag = true;
            }
        }
    }
    if(seenFlag == false){
        set_time_since_meal(get_time_since_meal() + 1);
        int decision = rand() % 4;
        if (decision == 0){
            if ((get_first_index() - 1 >= 0) && (gridArray[get_first_index() - 1][get_second_index()]->get_symbol() == '-'))
            {
                gridArray[get_first_index() - 1][get_second_index()] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_first_index(get_first_index() - 1);
            }
        }
        else if (decision == 1){
            if ((get_second_index() + 1 <= 19) && (gridArray[get_first_index()][get_second_index() + 1]->get_symbol() == '-'))
            {
                gridArray[get_first_index()][get_second_index() + 1] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_second_index(get_second_index() + 1);
            }
        }
        else if (decision == 2){
            if ((get_first_index() + 1 <= 19) && (gridArray[get_first_index() + 1][get_second_index()]->get_symbol() == '-'))
            {
                gridArray[get_first_index() + 1][get_second_index()] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_first_index(get_first_index() + 1);
            }
        }
        else if (decision == 3){
            if ((get_second_index() - 1 >= 0) && (gridArray[get_first_index()][get_second_index() - 1]->get_symbol() == '-'))
            {
                gridArray[get_first_index()][get_second_index() - 1] = this;
                gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
                set_second_index(get_second_index() - 1);
            }
        }
        else{};
        seenFlag = true;
    }
}


void Doodlebug:: breed(Organism* gridArray[numOfRows][numOfColumns], Doodlebug doodleBugArray[], int &doodleBugCounter){
    if(get_age() > 0 && get_age() % 8 == 0){
        bool seenFlag = false;
        int nextAvailIndex = find_next_available_index(doodleBugArray);
        while(seenFlag == false){
            if ((get_first_index() - 1 >= 0) && (gridArray[get_first_index() - 1][get_second_index()]->get_symbol() == '-'))
            {
                gridArray[get_first_index() - 1][get_second_index()] = &doodleBugArray[nextAvailIndex];
                doodleBugArray[nextAvailIndex].set_first_index(get_first_index() - 1);
                doodleBugArray[nextAvailIndex].set_second_index(get_second_index());
                doodleBugArray[nextAvailIndex].set_life_status(true);
                seenFlag = true;
            }
            else if ((get_second_index() + 1 <= 19) && (gridArray[get_first_index()][get_second_index() + 1]->get_symbol() == '-')){
                gridArray[get_first_index()][get_second_index() + 1] = &doodleBugArray[nextAvailIndex];
                doodleBugArray[nextAvailIndex].set_first_index(get_first_index());
                doodleBugArray[nextAvailIndex].set_second_index(get_second_index() + 1);
                doodleBugArray[nextAvailIndex].set_life_status(true);
                seenFlag = true;
            }
            
            else if ((get_first_index() + 1 <= 19) && (gridArray[get_first_index() + 1][get_second_index()]->get_symbol() == '-')){
                gridArray[get_first_index() + 1][get_second_index()] = &doodleBugArray[nextAvailIndex];
                doodleBugArray[nextAvailIndex].set_first_index(get_first_index() + 1);
                doodleBugArray[nextAvailIndex].set_second_index(get_second_index());
                doodleBugArray[nextAvailIndex].set_life_status(true);
                seenFlag = true;
            }
            
            else if ((get_second_index() - 1 >= 0) && (gridArray[get_first_index()][get_second_index() - 1]->get_symbol() == '-')){
                gridArray[get_first_index()][get_second_index() - 1] = &doodleBugArray[nextAvailIndex];
                doodleBugArray[nextAvailIndex].set_first_index(get_first_index());
                doodleBugArray[nextAvailIndex].set_second_index(get_second_index() - 1);
                doodleBugArray[nextAvailIndex].set_life_status(true);
                seenFlag = true;
            }
            
            seenFlag = true;
        }
    }
}
void Doodlebug::starve(Organism* gridArray[numOfRows][numOfColumns], Space spacesArray[]){
    if (get_time_since_meal() == 3){
        set_life_status(false);
        set_age(0);
        gridArray[get_first_index()][get_second_index()] = &spacesArray[0];
    }
}

void initiate_time_step(Organism* gridArray[numOfRows][numOfColumns], Ant antArr[], Space spaceArr[], Doodlebug doodlebugArr[], int &antCounter, int &doodlebugCounter){
    //int liveAnts = 0;
    //int liveDoodles = 0;
    
    for(int i = 0; i < 400; i++){
        if(doodlebugArr[i].get_life_status() == true)
            doodlebugArr[i].move(gridArray, doodlebugArr, spaceArr);
    }
    for(int i = 0; i < 400; i++){
        if(doodlebugArr[i].get_life_status() == true)
            doodlebugArr[i].breed(gridArray, doodlebugArr, doodlebugCounter);
    }
    
    for(int i = 0; i < 400; i++){
        if(antArr[i].get_life_status() == true)
            antArr[i].move(gridArray, spaceArr);
    }
    
    for(int i = 0; i < 400; i++){
        if(antArr[i].get_life_status() == true)
            antArr[i].breed(gridArray, antArr, antCounter);
    }
    
    for(int i = 0; i < 400; i++){
        if(doodlebugArr[i].get_life_status() == true)
            doodlebugArr[i].starve(gridArray, spaceArr);
    }
    
    cout<<"end of time step"<<endl;
    
    for(int c = 0; c < numOfColumns; c++){
        for (int i = 0; i < numOfRows; i++){
            gridArray[c][i]->out_symbol();
            cout<<" ";
        }
        cout<<endl;
    }
    
    /*for(int i = 0; i < 400; i++){
        if(doodlebugArr[i].get_life_status() == true){
            int x = doodlebugArr[i].get_age();
            cout<<"doodlebugArr["<<i<<"] is "<<x<<endl;
            liveDoodles++;
        }
    }
    for(int i = 0; i < 400; i++){
        if(antArr[i].get_life_status() == true)
            liveAnts++;
    }
    cout<<"live ant count is "<<liveAnts<<endl;
    cout<<"live doodlebug count is "<<liveDoodles<<endl;
    cout<<"TIME STEP"<<endl;*/
}

int find_next_available_index(Doodlebug arr[]){
    int nextIndex = 0;
    for(int i = 0; i < 400; i++){
        if (arr[i].get_life_status() == 0){
            nextIndex = i;
            i = 400;
        }
    }
    return nextIndex;
}

int find_next_available_index(Ant arr[]){
    int nextIndex = 0;
    for(int i = 0; i < 400; i++){
        if (arr[i].get_life_status() == 0){
            nextIndex = i;
            i = 400;
        }
    }
    return nextIndex;
}
