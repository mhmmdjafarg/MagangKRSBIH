#ifndef CAR_HPP
#define CAR_HPP

# include <iostream>
# include <cmath>

#define PI 3.14
#define ToDegree(X) (X)*180/PI
#define ToRadian(X) (X)*PI/180

using namespace std;

class Position {
	private :
		double x; //meter
  	double y; //meter	
  	double orientation;
  public :

    // Constructor
  	Position();
    /* 
      Inisialisasi x, y, dan orientation dengan 0
    */

  	Position(double x, double y, double theta);
    /*
      inisialisasi x, y, dan orientation sesuai dengan parameter
    */

    // Setter
  	void setX(double x);
  	void setY(double y);
  	void setOrientation(double orientation);

    // Getter  
  	double getX();
  	double getY();
    double getOrientation();

    // Methods lain
    double euclideanDistance(double x1, double y1, double x2, double y2);
    /* Menghitung dan mengembalikan jarak eucledian titik 1 dan 2 */
  	
    void printPosition();
    /* 
      Menampilkan ke layar dengan format 
      X : ... m
      Y : ... m
      Orientation : ... degree(s)

      "ganti ... dengan nilai sebenarnya" 
    */
};

class Car {
	private :
  	Position P;
  	double distanceTraveled; // in meter
  	double steer;
  	double speed; // meter per second
    double accel;
    bool On, gasOn, brakeOn;
    double fuelConsumptionConst = 0.05; // liter/meter
    const double pedalConst = 0.5;
    const double brakeConst = 0.25;
  	const double maxSpeed;
    const double minSpeed;
  	double fuel; //liter
  	int gear; // Valid value : 0, 1, -1 
  
  public :
    // Constructor
  	Car(double fuel, double max, double min);
    /*
      Menginisialisasikan nilai awal kepada tiap parameter
      fuel bernilai fuel,
      maxSpeed bernilai max,
      minSpeed bernilai min.
      speed, accel, gear, steer dan distanceTraveled bernilai 0,
      gasOn dan brakeOn bernilai false

      NB : Perhatikan, variabel const tidak dapat diubah di dalam fungsi
    */

    // Getter
  	Position getPost();
    /* Mengembalikan nilai P */

    double getSpeed();
    /* Mengembalikan nilai speed */
      
  	void changeGear(int val);
    /* 
      IS : Sembarang
      FS : nilai gear berubah menjadi val
    */

    // Methods lain
  	void applyPedal(double pressureLevel);
    /*
      IS : On = true, lainnya sembarang
      FS : Lakukan rangkaian perintah berikut
            - gasOn menjadi true
            - jika mesin menyala
                - jika fuel > 0, accel menjadi pressureLevel * pedalConst * gear
                - jika fuel <= 0, berhenti 
    */
  
  	void applyBrake(double pressureLevel);
    /*
      IS : On = true
      FS : Lakukan rangkaian perintah berikut
            - brakeOn menjadi true
            - jika mesin menyala
                - accel menjadi pressureLevel * brakeConst * (-1) * |speed|/speed 
                - jika pada akhirnya -0.001 < speed << 0.001, accel menjadi 0 
    */

    void start();
    /* 
      IS : On = false
      FS : On = true 
    */

    void stop();
    /* 
      IS : On = true
      FS : On, gasOn dan brakeOn bernilai false
           speed dan accel bernilai 0 
    */

    void speedControl();
    /*
      IS : On = true
      FS : Jika gasOn = true
             jika minSpeed < speed < maxSpeed, maka speed = speed + accel
             jika speed >=spe maxSpeed, maka speed = maxSpeed
             jika speed < 0, maka speed = minSpeed
           jika gasOn = false
             jika -0.001 <= speed <= maxSpeed, maka speed = speed + accel
             jika speed < -0.001 atau speed > 0.001, maka speed = 0
    */

    void fuelControl(double newDistance, double oldDistance);
    /*
      IS : Sembarang
      FS : fuel berkurang sebanyak (newDistance - oldDistance) * fuelConsumptionConst.
           jika pada akhirnya fuel < 0, maka fuel = 0
    */
  
  	void applySteer(double theta);
    /*
      IS : Sembarang
      FS : Orientasi mobil menjadi orientasi sebelumnya ditambah theta
    */
  
  	void move();
    /*
      IS : Sembarang
      FS : Melakukan serangkaian perintah dengan urutan berkut
            - speedcontrol
            - update nilai X dan Y
            - fuelControl
            - update nilai distanceTraveled
      
      NB : Perhatikan disini saat newDistance dihitung dengan menggunakan X dan Y sebelum diubah 
    */
  	
  	void addFuel(double amount);
    /*
      IS : Sembarang
      FS : fuel bertambah sebanyak amount
    */
  
  	void printCarStatus();
    /*
      Menampilkan status di layar dengan format
      --- STATUS ---
      Menampilkan ke layar dengan format 
      X : ... m
      Y : ... m
      Orientation : ... degree(s)
      distanceTraveled: ...
      fuelConsumptionConst: ...ltr/m
      steer: ...
      speed: ...
      maxSpeed: ...
      fuel: ...
      gear: ...

      "ganti ... dengan nilai yang sebenarnya"
    */
};

#endif