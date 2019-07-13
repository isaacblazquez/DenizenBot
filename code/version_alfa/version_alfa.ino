//definimos los pines de los sensores
//SENSOR ULTRA SONIDO
int Trig = 48;
int Echo = 49;

// bloque motor izquierdo
int enA = 10;
int in1 = 9;
int in2 = 8;
// bloque motor derecho
int enB = 5;
int in3 = 7;
int in4 = 6;

//BUMPER
int bumperD = 30;             //bumper derecho
int bumperI = 31;             //bumper izquierdo

//Variable en la que se va a almacenar el valor correspondiente a la distancia
int Distancia;
int buttonStateD = 0;         // variable for reading the pushbutton status
int buttonStateI = 0;         // variable for reading the pushbutton status


#define maximum_distance 200
int MAX_VEL = 255;            //MAXIMA VELOCIDAD DE LOS MOTORES
int MIN_VEL = 10;             //MINIMA VELOCIDAD . MODIFICAR PARA AJUSTAR A TUS MOTORES
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

  if ((buttonStateD == LOW) | (buttonStateI == LOW)){
    Serial.println("¡¡¡¡GOLPE!!!!");


    
    //PARAR MOTORES
    Parar();
    //MARCHA ATRAS
    
    //GIRAR DEPENDIENDO DE DONDE ESTE EL GOLPE

      // GOLPE EN DERECHA - GIRO A IZQUIERDA

      // GOLPE EN IZQUIERDA - GIRO A DERECHA

  }else{
      
      Avanzar();



    //COMPRUEBO DISTANCIA
      //SI DISTANCIA > 30 -> AVANZO RAPIDO
      //SI DISTANCIA 29 - 21  -> AVANZO MEDIAVELOCIDAD
      //SI DISTANCIA 20 - 10 -> AVANZO LENTO
      //SI DISTANCIA MENOR 10 -> GIRAR



   
   
  }
  
}



void comprobacion(){

  
}

void Avanzar(){
     digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);

      analogWrite(enA, 200);
      analogWrite(enB, 200);
      
  }

void Parar(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
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
