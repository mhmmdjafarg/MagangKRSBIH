#include "Car.hpp"
#include <cmath>
#include <iostream>


// class position
//constructor
Position::Position(){
    x = 0;
    y = 0;
    orientation = 0;
}

Position::Position(double x, double y, double theta)
{
   this->x = x;
   this->y = y;
   orientation = theta;
}

// setter
void Position::setX(double x){this-> x = x;}
void Position::setY(double y){this-> y = y;}
void Position::setOrientation(double orientation){this->orientation=orientation;}


//getter
double Position::getX(){return x;}
double Position::getY(){return y;}
double Position::getOrientation(){return orientation;}

// methods lain
double Position::euclideanDistance(double x1, double y1, double x2, double y2)
{
    this-> x=x1;
    this-> y=y1;
    this-> x=x2;
    this-> y=y2;
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));

}

void Position::printPosition()
{
    cout << "X : " << getX() << " m" << endl;
    cout << "Y : " << getY() << " m" << endl;
    cout << "Orientation : " << getOrientation() << " degree(s)" << endl;
}


// Class car
// constructor

//inisialisasi nilai awal
Car::Car(double fuel, double max, double min) : maxSpeed(max), minSpeed(min)
{
    this->fuel = fuel;
    speed=0;
    accel=0;
    gear=0;
    steer=0;
    distanceTraveled=0;
    gasOn=false;
    brakeOn=false;
}

//getter
Position Car::getPost(){return P;}
//mengembalikan nilai P


//mengembalikan nilai speed
double Car::getSpeed(){return speed;}

// ubah nilai gear menjadi val
void Car::changeGear(int val)
{
    gear=val;
}


// method lain
void Car::applyPedal(double pressureLevel)
{
    // On = true;
    gasOn=true;
    if(fuel > 0)
    {
        accel = pressureLevel * pedalConst * gear;
    } else{
        On=false;
    }
}

void Car::applyBrake(double pressureLevel)
{
    brakeOn=true;
    if(On && speed>=0.001 && speed <= (-0.001))
    {
        accel = pressureLevel * brakeConst * (-1) * abs(speed) / speed;
    } else{
        accel = 0;
    }
}

void Car::start(){On=true;}

void Car::stop(){On, gasOn, brakeOn =false; speed,accel = 0; }

void Car::speedControl(){
    if(gasOn){
        if(speed>minSpeed && speed<maxSpeed){
            speed = speed + accel;
        } else if(speed >= maxSpeed){
            speed=maxSpeed;
        }else{
            speed = minSpeed;
        }
    } else{
        if(speed>=(-0.001) && speed <= maxSpeed){
            speed=speed + accel;
        } else if (speed < (-0.001) || speed > 0.001){
            speed=0;
        }
    }
}


void Car::fuelControl(double newDistance, double oldDistance){
    fuel = fuel - (newDistance - oldDistance) * fuelConsumptionConst;
    if(fuel < 0){
        fuel = 0;
    }
}

void Car::applySteer(double theta){
    double Sudut;
    Sudut = theta+P.getOrientation();
    P.setOrientation(Sudut);
    /*if(Sudut > 360 || Sudut <= 0){
        Sudut = fmod(Sudut,360); // agar nilai orientation tidak lebih dari 360
    }
    P.setOrientation(Sudut); */
}

void Car::move(){
    speedControl();
    // Update x dan y
    double prevX, prevY;
    prevX = P.getX();
    prevY = P.getY();
    P.setX(prevX+speed*cos(ToRadian(P.getOrientation())));
    P.setY(prevY+speed*sin(ToRadian(P.getOrientation())));

    double newDistance;
    newDistance = distanceTraveled + P.euclideanDistance(prevX,prevY,P.getX(),P.getY());
    fuelControl(newDistance, distanceTraveled);

    // update nilai distanceTraveled
    distanceTraveled = newDistance;
}


void Car::addFuel(double amount){
    fuel = fuel + amount;
}

void Car::printCarStatus(){
    cout << "-- STATUS -- " << endl;
    P.printPosition();
    cout << "distanceTraveled : " << distanceTraveled << endl;
    cout << "fuelConsumptionConst : " << fuelConsumptionConst << " ltr/m" << endl;
    cout << "steer : " << endl;
    cout << "speed : " << speed << endl;
    cout << "maxSpeed : " << maxSpeed << endl;
    cout << "fuel : " << fuel << endl;
    cout << "gear : " << gear << endl;
}
