
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria instância com MFRC522
 

char st[20];


void setup() 
{
  Serial.begin(9600);   // Inicia comunicação Serial
  SPI.begin();          // Inicia comunicação SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
}



void loop() 
{
  // Verifica novos cartões
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona um dos cartões
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  // Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
  if (conteudo.substring(1) == "45 A0 D2 65") //UID 1 - Chaveiro
  {
    Serial.println("Chaveiro identificado!"); 
    Serial.println();
    digitalWrite(2,!digitalRead(2));
    delay(1500);
     
  }
 
  if (conteudo.substring(1) == "78 F2 65 10") //UID 2 - Cartao
  {
    Serial.println("Cartao identificado");
    Serial.println();
    digitalWrite(3,!digitalRead(3));
    delay(3000);
    
  }
  
  
} //end loop
 
 
