//definimos los pines de los sensores
//SENSOR ULTRA SONIDO
int Trig = 48;
int Echo = 49;

// bloque motor izquierdo
int enA = 8;
int in1 = 10;
int in2 = 9;
// bloque motor derecho
int enB = 5;
int in3 = 6;
int in4 = 7;

//BUMPER
int bumperD = 30;             //bumper derecho
int bumperI = 31;             //bumper izquierdo

//Variable en la que se va a almacenar el valor correspondiente a la distancia
int Distancia;
int buttonStateD = 0;         // variable for reading the pushbutton status
int buttonStateI = 0;         // variable for reading the pushbutton status

#define maximum_distance 200
int MAX_VEL = 255;            //MAXIMA VELOCIDAD DE LOS MOTORES
int MIN_VEL = 150;             //MINIMA VELOCIDAD . MODIFICAR PARA AJUSTAR A TUS MOTORES
int STOPPED = 0;              //VELOCIDAD DE PARADA




void setup() {
  
  Serial.begin(9600);         // PARA VERLO POR MONITOR SERIAL
    
  pinMode (Trig, OUTPUT);     //DEFINIMOS Trig como salida
  pinMode (Echo, INPUT);      //DEFINIMOS Echo como entrada
  pinMode(bumperD, INPUT);    //DEFINIMOS bumperD como entrada
  pinMode(bumperI, INPUT);    //DEFINIMOS bumperI como entrada

  // Defino todos los pines de motor como salidas
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 buttonStateD = digitalRead(bumperD);
 buttonStateI = digitalRead(bumperI);


//COMPROBACION DE CHOQUE
  if ((buttonStateD == LOW) | (buttonStateI == LOW)){
    Serial.println("¡¡¡¡GOLPE!!!!");
    
//PARAR MOTORES
     Parar();
     DesactivaMotores();
//MARCHA ATRAS
      MarchaAtras();
      ActivaMotores();
      delay(2000);
//GIRAR DEPENDIENDO DE DONDE ESTE EL GOLPE
 // GOLPE EN DERECHA - GIRO A IZQUIERDA
       if (buttonStateD == LOW){
         GiroEjeAIzquierda();
         ActivaMotores();
         delay(2000);
         Parar();
         DesactivaMotores();
         delay(2000);
       }
 // GOLPE EN IZQUIERDA - GIRO A DERECHA
       if (buttonStateI == LOW){
         GiroEjeADerecha();
         ActivaMotores();
         delay(2000);
         Parar();
         DesactivaMotores();
         delay(2000);
       }
  }else{
     Serial.println("AVANZAR");
      Avanzar();
      ActivaMotores();
  }
}



void comprobacion(){

  
}

void ActivaMotores(){
  ponVelocidadMotor(100);
}

void DesactivaMotores(){
  ponVelocidadMotor(0);
}

void Avanzar(){
    //MOTOR A (IZQUIERDO)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  //MOTOR B (DERECHO)    
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void MarchaAtras(){
  //MOTOR A (IZQUIERDO)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  //MOTOR B (DERECHO)    
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  }

void Parar(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void ponVelocidadMotor(int velocidad){
    analogWrite(enA, velocidad);
    analogWrite(enB, velocidad);
}

void GiroEjeAIzquierda(){
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH); 
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW); 
}

void GiroEjeADerecha(){
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW); 
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH); 
}


void modoGiroIzquierda(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void modoGiroIzquierdaHaciaAtras(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void modoGiroDerecha(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void modoGiroDerechaHaciaAtras(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


int dameDistanciaUltraSonido(){
   //Para estabilizar el valor del pin Trig se establece a LOW
  digitalWrite (Trig, LOW);
  delay(10);

  //Se lanzan los 8 pulsos
  digitalWrite (Trig, HIGH);
  delay(10);
  digitalWrite (Trig, LOW);

  /*
    Se mide el tiempo que tarda la señal en regresar y se calcula la distancia.
    Observa que al realizar pulseIn el valor que se obtiene es tiempo, no distancia
    Se está reutilizando la variable Distancia.
  */

  Distancia = pulseIn (Echo, HIGH);
  Distancia = Distancia / 58;
  delay(100);
  return Distancia;
}
