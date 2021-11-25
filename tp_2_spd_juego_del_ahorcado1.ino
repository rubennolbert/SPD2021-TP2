// C++ code
//

//   https://www.tinkercad.com/things/7GcudGEOU7t-tp-2-spd-juego-del-ahorcado/editel?sharecode=vFKy8tsh1qnOKloVHYLn2uTTB0dmka8i_eRxi1b32Vc


#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);



char cadena[25] = "aleatorios"; 
int valorA0;
char letra [] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int vidas = 3;
int caracCorrecto=2; 
int indiceLetra=0;


void setup()
{
  
  
  	Serial.begin(9600);
  	pinMode(A0, INPUT);
 	lcd.begin(16, 2);
  	lcd.setCursor(3, 1);
	lcd.print("__________");
 	lcd.setCursor(3, 0);	
  	lcd.print(letra[indiceLetra]);
 	setear();
  
  
  	
  	
}

int botonAntes = 0;
int iUp=0;
int iDown = 0;



void loop()
{
 	
  
  	int botonAhora = leerBoton();
  
    if(botonAhora != 0 && botonAhora != botonAntes)
    {
         
             switch(botonAhora)
             {
                 case 1: //subir	
               		subirLetra();
                     lcd.setCursor(3, 0);		
                     lcd.print(letra[indiceLetra]);
                 break;
                 case 2:  //probar
               		buttonProbar(cadena,letra[indiceLetra]);
               		setear();
                 break;
                 case 3:  //bajar
               		bajarLetra();
               		lcd.setCursor(3, 0);		
               		lcd.print(letra[indiceLetra]);
                 break;
             }       
    }
  
  	botonAntes = botonAhora;
  
  	Perder();  
   	 	
  	Ganar(cadena);
  
 	ahorcadoInit();
   
  
}



//Funcion bajarLetra
// Deciende la letra para el usuario

void bajarLetra(){
	iDown --;
    indiceLetra--;
        
  	if(indiceLetra==-1){
          indiceLetra=25;
            }

}

//Funcion subirLetra
// Asciende la letra para el usuario

void subirLetra(){
	iUp ++;
	indiceLetra++;
    
  	if(indiceLetra>=26){
        indiceLetra=0;
       }

}

//Funcion Setear
// Setea y muestra el display

void setear(){

	lcd.setCursor(6, 0);
	lcd.print("Vidas: ");
  	lcd.setCursor(13, 0);						
  	lcd.print(vidas);    
}

//Funcion LeerBoton
// Lee la tension que recibe el pin analogico y retorna
// un numero entero segun dicha tension 

int leerBoton()
{
	int valorA0 = analogRead(A0);
  
    if(valorA0 > 502 && valorA0 < 522)
    return 1;

    if(valorA0 > 672 && valorA0 < 692)
    return 2;

    if(valorA0 > 757 && valorA0 < 777)
    return 3;
  
  return 0;
}
 

// Funcion Probar 
// 	Recibe una cadena y una letra elegida por el usuario
//	y comprueba que la letra este en la cadena de lo contrario
// 	resta una vida 

void buttonProbar(char cadena[],int letra){

 int indCaracter=0;
  if(String(cadena).indexOf(letra,0)==-1)
  {
  	vidas--; 
    
  }else{
    caracCorrecto++;   
    for(int i = 0 ; i<String(cadena).length(); i++)
    {
      if(String(cadena).indexOf(letra,indCaracter)!=-1)
      {
        indCaracter = String(cadena).indexOf(letra,indCaracter);
    	Serial.println("Se encontro el caracter");
        Serial.println(indCaracter);
    	lcd.setCursor((indCaracter+3),1);
        lcd.print(cadena[indCaracter]);
        indCaracter++;
      }else{
      	
        	break;
      		}
      };
      
      
  }
       
}

//Funcion Perder
//No recibe parametros, ni no devuelve ningun dato
//Nos muestras en el display "PERDISTE" despues de perder todas las vidas.
void Perder(){
  if(vidas==0){ 
    
   
    lcd.setCursor(3,1);
    lcd.print(" PERDISTE ");  
    
  		delay(1500);
      	ahorcado();
      	lcd.clear();
        
    	reiniciar();   
    	
    
}
}

//Funcion Ganar
//Recibe una cadena de caracteres, devuelve vacio
//si se encuentran los caracteres correctos no muestra en el 
//display "GANASTE"
void Ganar(char cadena[]){
  if(caracCorrecto==String(cadena).length()){ 
  	lcd.clear();  
    lcd.setCursor(4,1);
    lcd.print("Ganaste"); 
    
    unsigned long millisAnterior=0;
   	unsigned long millisActual = millis(); 
  	if((millisActual - millisAnterior) >= 3000)
  	{
  		delay(1500);/////////
        reiniciar();  
    	caracCorrecto=0;
   		millisAnterior = millisActual;
      	
  	}
    
}
}

//Funcion Reiniciar
//No recibe, ni devuelve parametros
//Despues finalizar el juego reinicia el display
void reiniciar()
{
		vidas=3;
  		setear();
      	lcd.setCursor(3, 0);
    	lcd.print(letra[0]);
        lcd.setCursor(3, 1); 
      	lcd.print("__________");
  		indiceLetra=0;
}

//Funcion Ahorcado
//No recibe, ni devuelve parametros
//Muestra en el display emulacion de un ahorcado luego de perder
void ahorcado()
{
  
      byte ahorcado1[] = {
      B11111,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000
    };
  
  
      byte ahorcado2[] = {
      B11111,
      B00100,
      B00100,
      B01110,
      B01110,
      B00100,
      B01110,
      B10101
    };
  
  byte ahorcado3[] = {
      B00100,
      B00100,
      B01110,
      B01010,
      B01010,
      B11011,
      B00000,
      B00000
    };
  
  byte ahorcado4[] = {
      B10001,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000,
      B10000
    };
  
  byte ahorcado5[] = {
      B11111,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
  byte ahorcado6[] = {
      B10000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };

  
  
  
  lcd.begin(16, 2);
  lcd.createChar(byte(0), ahorcado1);
  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.createChar(byte(1), ahorcado2);
  lcd.setCursor(8, 0);
  lcd.write(byte(1));
  lcd.createChar(byte(2), ahorcado3);
  lcd.setCursor(8, 1);
  lcd.write(byte(2));
  lcd.createChar(byte(3), ahorcado4);
  lcd.setCursor(7, 1);
  lcd.write(byte(3));
  lcd.createChar(byte(4), ahorcado5);
  lcd.setCursor(9, 0);
  lcd.write(byte(4));
  lcd.createChar(byte(5), ahorcado6);
  lcd.setCursor(9, 1);
  lcd.write(byte(5));

  delay(1500);
  

}

//Funcion AhorcadoInit
//no recibe, ni devuelve parametros
//Muestra en el display una emulacion de un ahorcado
//que interactua cuando se pierden vidas
void ahorcadoInit(){
  
    if(vidas == 3){
       byte base[] = {
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B11111,
        B11111,
        B11111
      };

          byte mastil[] = {
        B00000,
        B00111,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100
      };
      
       //lcd.begin(16, 2);
        lcd.createChar(byte(0), base);
        lcd.setCursor(0, 1);
        lcd.write(byte(0));
        lcd.createChar(byte(1), mastil);
     	lcd.setCursor(0, 0);
        lcd.write(byte(1));
      
    }
      
      if(vidas == 2){
              byte cabeza[] = {
          B00000,
          B11100,
          B01010,
          B11011,
          B10001,
          B10101,
          B01010,
          B00100
        };
        
         lcd.createChar(byte(2), cabeza);
      	lcd.setCursor(1, 0);
        lcd.write(byte(2));
    
      }
  
  	if(vidas == 1){

            byte bracitos[] = {
        B00100,
        B11111,
        B10101,
        B10101,
        B00100,
        B00000,
        B00000,
        B00000
      };

      
        lcd.createChar(byte(3), bracitos);
       	lcd.setCursor(1, 1);
        lcd.write(byte(3));
      
    }

 }
