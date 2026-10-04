long zahl1 = 0;

long zahl2 = 0;

long ergebnis = 0;

char operatorZeichen;

String eingabe = "";

 

void setup()
{
  Serial.begin(9600);

}


void loop()
{
    if(Serial.available() > 0)
    {
        eingabe = Serial.readStringUntil('\n');

        int positionOperator = -1;

        //Hier soll nach einer Muliplikation gesucht werden, wenn das Mal-Zeichen gefunden wird, wird die Position des Operators geaendert zu "*" statt "-1":
        if(positionOperator == -1)
          {
            positionOperator = eingabe.indexOf('*');
          }

        //Wenn keine Multiplikation gefunden wurde, wird nach einer Division gesucht.
        if(positionOperator == -1)
          {
            positionOperator = eingabe.indexOf('/');
          }

        //Wenn keine Division festgestellt wurde, wird nach einem Plus gesucht.
        if(positionOperator == -1)
          {
            positionOperator = eingabe.indexOf('+');
          }

        //Wenn kein Plus gefunden wurde, wird nach einem Minus gesucht.
        //Jedoch nicht an der ersten Position, fuer den Fall, dass die erste Zahl eine Negative ist.
        if(positionOperator == -1)
          {
            positionOperator = eingabe.indexOf('-',1);
          }

        //Wenn ein Operator gefunden wurde, werden die Zahlen, die verrechnet werden sollen, gespeichert.
        if(positionOperator != -1)
          {
            //Dies ist die erste Zahl, vor dem Operator. Diese wird hier gespeichert:
            zahl1 = eingabe.substring(0, positionOperator).toInt();

            //Die ermittelte Position des Operators wird aufgerufen und das dort gefundene Zeichen wird gespeichert.
            operatorZeichen = eingabe.charAt(positionOperator);

            //Dies ist die zweite Zahl, nach dem Operator. Diese wird hier gespeichert:
            zahl2 = eingabe.substring(positionOperator + 1).toInt();


            //Vor der Berechnung soll noch geprueft werden, ob die Zahl weder zu gross, noch zu klein ist.
            if(zahl1 < -1000000 || zahl1 > 1000000 ||
               zahl2 < -1000000 || zahl2 > 1000000)
              {
                  Serial.println("Whoopsie! Die Zahlen duerfen maximal -/+1.000.000 betragen! Dies ist daher keine gueltige Eingabe!");
              }

                //Hier findet entsprechend des Operators die Berechnung statt.
              else if(operatorZeichen == '+')
                {
                    ergebnis = zahl1 + zahl2;  
                    //Das Ergebnis wird hier zurueck an den PC gesendet.
                    Serial.println((double)ergebnis, 0);
                }
              else if(operatorZeichen == '-')
                {
                    ergebnis = zahl1 - zahl2;
                    //Das Ergebnis wird hier zurueck an den PC gesendet.
                    Serial.println((double)ergebnis, 0);
                }
              else if(operatorZeichen == '*')
                {
                    //Hier wird uepferprueft, ob die Groesse des Ergebnisses der Multiplikation innerhalb des erlaubten Bereichs liegt.
                    if(zahl1 * zahl2 > 100000000)
                      {
                        Serial.println("Ohh nein! Das Ergebnis der Multiplikation ist zu gross!");
                      }else if(zahl1 * zahl2 < -100000000){
                        Serial.println("Ohh nein! Das Ergebnis der Multiplikation ist zu klein!");      
                                                  
                      }else{
                        ergebnis = zahl1 * zahl2;
                        //Das Ergebnis wird hier zurueck an den PC gesendet.
                        Serial.println(ergebnis);
                           }
                }
              else if(operatorZeichen == '/')
                {

                    //Hier bei der Division ist zu ueberpruefen, ob es sich um eine Division durch Null handelt.
                    if(zahl2 != 0)
                      {
                        double ergebnisDivision = (double)zahl1 / zahl2;
                        //Das Ergebnis wird hier zurueck an den PC gesendet. 
                        Serial.println(ergebnisDivision, 1); 
                      }
                    else
                      {
                        Serial.println("Hoppala! Sie versuchen gerade durch Null zu teilen!");
                      }
               
                }


          }else{
              //Fuer den Fall, dass kein Operator gefunden werden kann, wird der Nutzer benachrichtigt.
              Serial.println("Es konnte kein Operator gefunden werden!");
            }
    
    }

   
}

