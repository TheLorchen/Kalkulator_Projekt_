#include <iostream>

#include "serial.h"

#include <string>

#include <windows.h>

#include <fstream>

using namespace std;


int main() {

    // Begrüßung und Erklärung der Grenzen des Kalkulator-Programms
    cout<< "Willkommen zu meinem Kalkulator-Programm!\n"
        << "Dieses unterschuetzt folgende Opperationen : \n"
        << "Addition, Subtraktion, Multiplikation und Division.\n"
        << "Bitte nutzen Sie nur Ganzzahlen bis maximal + / -1.000.000.\n"
        << "Bei einer Division wird maximal eine Nachkommastelle angezeigt.\n"
        << "Das Ergebnis der Multiplikation darf maximal 100.000.000 betragen, bitte beachten Sie das!\n"
        << "Zum Beenden des Programms bitte 'quit' eingeben, viel Spass.\n\n";


    string antwort = "Noch keine Antwort (Arduino nicht verbunden)";

    // Dateiobjekt erstellen und Textdatei anlegen für die Verfolgung der Kommunikation
    ofstream datei("Kommunikation.txt", ios::app);


     // Das ist die Variable für die Benutzereingabe.
     string eingabe;


    // Hier soll die Verbindung zum Arduino hergetellt werden.
    int arduino = Simple_sopen((char*)"COM7", READ | WRITE, 9600);


    // Hier soll dem Arduino Zeit zum Starten gegeben werden
    Sleep(2000);

        while (true) {
            
            // Hier wird eine Eingabeaufforderung gestellt und gespeichert.
            cout << "Bitte Rechnung eingeben: ";

            getline(cin, eingabe);

            // Mit der Eingabe "quit" wird das Programm beendet.
            if (eingabe == "quit") {

                cout << "Danke, dass Sie sich für mein Programm entschieden haben!\nIch wuensche noch einen angenehmen Tag!";

                datei << "Gesendet: " << eingabe << endl;

                datei << endl;   

                break;

            }

            // Hier sollen eine leere Eingaben abgefangen werden.
            if (eingabe.empty()) {

                cout << "Oops! Sie haben nichts eingegeben! Versuchen wir es nochmal :)\n\n";

                continue;

            }

            // Hier wird die Eingabe ueber die serielle Schnittstelle an den Arduino geschickt.
            string nachricht = eingabe + "\n";
            swrite(arduino, (char*)nachricht.c_str(), nachricht.length());

            // Dem Arduino kurz Zeit zum Antworten geben
            Sleep(100);

            // Hier die Antwort vom Arduino empfangen
            char empfangen[100];

            int anzahl = sread(arduino, empfangen, 99);

            if (anzahl > 0) {

                empfangen[anzahl] = '\0';

                antwort = empfangen;

                cout << "Dein Ergebnis lautet: "
                    << antwort << endl;
            }
            else {

                antwort = "Keine Antwort von Arduino";

                cout << antwort << endl;
            }

            // Hier soll die Kommunikation in einer Logdatei gespeichert werden.
            datei << "Gesendet: " << eingabe << endl;

            datei << "Empfangen: " << antwort << endl;

            datei << endl;
        }

    // Hier soll die Logdatei geschlossen werden.
    datei.close();

    // Hier soll der Inhalt der Logdatei eingelesen und auf dem Bildschirm ausgegeben werden.
    cout << "\n---Inhalt der Logdatei---\n";

    ifstream dateiLesen("Kommunikation.txt");

    string zeile;

    while (getline(dateiLesen, zeile)) {

        cout << zeile << endl;
    }


    dateiLesen.close();

    return 0;

}


























    

