int MPin = 9;
int C=8;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  

pinMode(MPin, OUTPUT);
pinMode(C,INPUT);


}


void loop() {

  val = digitalRead(C);   // read the input pin

while(val==HIGH){
  
  long DO=261.626, //definimos las frecuencias de las notas
        DOS=277.183,
        RE=293.665,
        RES=311.127,
        MI=329.628,
        FA=349.228,
        FAS=369.994,
        SOL=391.995,
        SOLS=415.305,
        LA=440,
        LAS=466.164,
        SI=493.88,
        DO2=523.251,
        DOS2=552.365,
        RE2=587.33,
        RES2=622.254,
        MI2=659.255,
  
        PAU=30000; //pausa

       int d=1000, e=500, m=250, c=125; 

       int melodia[] = {MI,FAS,SOL,MI,SI,MI,FAS,SOL,SI,SI,PAU,SI,DO2,SI,LA,SOL,SOL,FAS,MI,PAU,MI,FAS,SOL,MI,SOL,LA,SI,SOL,PAU,SI,DOS2,RE2,DOS2,RE2,DOS2,RE2,MI2,RE2,DOS2,SI,SI,PAU,MI,FAS,SOL,MI,SOL,LA,SI,SOL,PAU,SI,DOS2,RE2,DOS2,RE2,DOS2,RE2,MI2,RE2,DOS2,SI,SI,PAU,
       SI,DOS2,RE2,RE2,RE2,RE2,RE2,MI2,RE2,DOS2,RE2,SI,PAU,DOS2,RE2,RE2,RE2,MI2,RE2,DOS2,SI,PAU,SI,DOS2,RE2,RE2,RE2,RE2,RE2,MI2,RE2,DOS2,RE2,SI,DOS2,RE2,RE2,RE2,MI2,RE2,DOS2,SI,PAU,
       MI,RES,MI,FAS,SOL,FAS,SOL,LA,LAS,LAS,LAS,SI,SI,SI,PAU,MI,RES,MI,FAS,SOL,FAS,SOL,LA,RE2,RE2,RE2,RE,RE,RE,PAU,SI,SI,SI,LAS,SI,SI,SI,SI,LAS,LAS,LAS,SI,SI,SI,PAU,SI,SI,SI,DO2,SI,SI,SI,RE2,RE2,RE2,RE,RE,RE,PAU,
       MI,FAS,SOL,SI,DO2,SI,PAU,MI,FAS,SOL,MI,SI,MI,PAU,MI,FAS,SOL,SI,DO2,SI,PAU,MI,FAS,SOL,MI,SI,MI};

       
for (int notaActual = 0; notaActual < 176; notaActual++) { //va a repetir las 176 notas
 val = digitalRead(C);
 if(val==LOW){
  notaActual=notaActual+175;
  delay(800);
 }
tone(9, melodia[notaActual]); //da el tono a la frecuencia de la nota en ese momento
delay(m);//se mantiene con la nota el tiempo definido para esa nota
noTone(9); //finaliza la melodía
}
}

while(val==LOW){
  
long DO=261.626, //definimos las frecuencias de las notas
        DOS=277.183,
        RE=293.665,
        RES=311.127,
        MI=329.628,
        FA=349.228,
        FAS=369.994,
        SOL=391.995,
        SOLS=415.305,
        LA=440,
        LAS=466.164,
        SI=493.88,
        DO2=523.251,
        DOS2=552.365,
        RE2=587.33,
        RES2=622.254,
        MI2=659.255,
  
        PAU=30000; //pausa

       int d=1000, e=500, m=250, c=125; 
//SI,LA,SI,LA,SI,LA,DO2,SI,LA,PAU,LA,SI,DO2,LA,SI,DO2,DO2,SI,PAU,
       int melodia2[] = {DO2,DO2,LA,DO2,SI,DO2,SI,SOL,PAU,LA,MI2,RE2,DO2,SI,DO2,SI,SOL,PAU,
       DO2,DO2,LA,DO2,SI,DO2,SI,SOL, PAU, LA,LA,FA,LA,SOL,LA,SOL,DO,PAU,
       DO2,DO2,LA,DO2,SI,DO2,SI,SOL, PAU, LA,MI2,RE2,DO2,SI,DO2,SI,SOL};
       
for (int notaActual2 = 0; notaActual2 < 66; notaActual2++) {  //va a repetir las 176 notas
val = digitalRead(C);
if(val==HIGH){
  notaActual2=notaActual2+65;
  delay(800);
 }
tone(9, melodia2[notaActual2]); //da el tono a la frecuencia de la nota en ese momento
delay(m);//se mantiene con la nota el tiempo definido para esa nota
noTone(9); //finaliza la melodía
}
}

}
