/*
è necessario importaer la libreria servo e creare un'istanza per utilizzare il motore
*/
#include <Servo.h>
Servo myServo;

//crea le costanti per dare un nome ai tuoi ingressi e uscite
const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;
 
//crea variabili per memorizzare i valori dell'interruttore e del piezo
int knockVal;
int switchVal;
 
//crea delle costanti da usare come soglie per i livello minimo e massimo dei colpi
const int quietKnock = 1;
const int loudKnock = 10;
 
/*
la variabile locked ti consente di sapere se la serratura è chiusa o no. Il boolean 
è un tipo di dato che può essere vero (1) o falso (0). dovresti iniziare con la serratura sbloccata.
L'altra variabile contiene il numero di colpi validi che ha rilevato
*/
boolean locked = false;
int numberOfKnocks = 0;
 
int interval = 500;
float lastTime = 0.0;
 
// nel setup attacca il sevo al piedino 9.
//imposta i piedini del LED come uscite e i piedini dell'interruttore come ingressi
void setup()
{
  myServo.attach(9);
 
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);
 
  Serial.begin(9600);
 
/*
 avvia la comunicazione seriale con il comptuter in modo da poter controllare il volume del colpo, lo stato corrente del blocco
e quanti colpi mancano allo sblocco.
accendi il led verde, muovi il servo nella posizione di sblocco e stampa lo stato attuale sul monitor seriale indicando che il circuito
è nella posizione sbloccata.
*/
  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  Serial.println("The box is unlocked!");
}
 
/*
Nel loop, per prima cosa verifica se la scatola è bloccata o no. questo determina ciò che accade nel resto
del programma. se è bloccata leggi il valore dell'interettutore.
*/
void loop()
{
  if (locked == false)
  {
    switchVal = digitalRead(switchPin);

/*
se l'interruttore (lo stai premendo), modifica la variabile locked a true, indicando che il blocco è innestato.
spegni il led verde e accendi il led rosso. se non hai acceso il monitor seriale, questo è un utile feedback visivo per
informarti dello stato del blocco.
Sposta il servo in posizione di blocco e stampa un messaggio sul monitor seriale che indica che la scatola è
bloccata. aggiungi un ritardo in modo che la serratura abbia tempo per cambiare posizione.
*/
    if (switchVal == HIGH)
    {
      locked = true;
      numberOfKnocks = 0;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      myServo.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  }
/*
Se la variabile locked è vera, ed è attivo il blocco, leggi l'intensità della vibrazione del piezo e memorizzala in knockVal
*/
  else if (locked == true)
  {
    knockVal = analogRead(piezo);
/*
l'istruzione successiva verifica se hai meno di tre colpi validi e se ci sono vibrazioni sul sensore. se questi sono entrambi veri
controlla per vedere se il colpo corrente è valido o no e incrementa la variabile numberOfKnocks. Qui chiami la funzione checkForKnocks().
scriverai la funzione una volta che hai finito il loop, ma già sai che stai per chiedere se si tratta di un colpo valido perciò passa knockVal 
come parametro. Dopo aver verificato il risultato, stampa il numero di colpi di cui hai ancora bisogno.
*/
    if (numberOfKnocks < 3 && knockVal > 0)
    {
      if (checkForKnock(knockVal) == true)
      {
        numberOfKnocks++;
      }
      Serial.print(3-numberOfKnocks);
      Serial.println(" more knocks to go");
    }
   /*
    controlla se hai tre o più colpi validi. in questo caso, cambia la variabile locked su falso e sposta il servo nella posizione di sblocco.
    attendi pochi milesimi di secondi per dargli tempo di muoversi e modifica lo stato dei LED verde e rosso. stampa un messaggio di stato 
    sul monitor seriale, indicando che la scatola è sbloccata
   */
    if (numberOfKnocks >= 3)
    {
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println("The box is unlocked!");
    }
  }
}
 
/*
è ora di scrivere la funzione checkForKnock(). questa funzione verificherà un numero (la variabile knockVal per vedere se è valido o no. 
Per passare questa variabile alla funzione, crea un parametro quando dichiari la funzione.
*/
boolean checkForKnock(int value)
{
/*
nella funzione ogni volta che ti rifesci a value conterrà il numero ricevuto come argomento. a questo punto value è impostato al valore della
variabile knockval. controlla  se value è maggiore del colpo debole e inferiore del colpo forte.
*/
  if (value > quietKnock && value < loudKnock)
  {
    if (millis() - lastTime >= interval)
    {
      lastTime = millis();
      /*
      se il valore è tra questi due, è un bussare valido. fai lampeggiare una volta il led giallo e stampa il valore del colpo
      */
      digitalWrite(yellowLed, HIGH);
      delay(50);
      digitalWrite(yellowLed, LOW);
      Serial.print("Valid knock of value ");
      Serial.println(value);

      //per informare il programma principale dell'esito del confronto utilizza il comando return, che termina anche la funzione. si ritorna al programma //principale
      return true;
    }
    else
    {
      Serial.println("Use the right interval");
    }
  }
//se value è fuori dall'intervallo previsto stampa il valore sul monitor seriale e la funzione restituisce false.
  else
  {
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}
