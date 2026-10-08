#include <Arduino.h>
#include <Pixy2.h>

// Pixy2 Objekt erstellen
Pixy2 pixy;

void setup() {
  // Seriellen Monitor starten (Baudrate muss mit monitor_speed in platformio.ini übereinstimmen)
  Serial.begin(115200);
  Serial.println("Starte Pixy2 Kommunikation...");

  // Pixy2 Kamera initialisieren (kommuniziert über SPI am ICSP-Header)
  pixy.init();
}

void loop() {
  // Blöcke (erklärte Farbsignaturen) von der Kamera anfordern
  pixy.ccc.getBlocks();

  // Prüfen, ob Objekte erkannt wurden
  if (pixy.ccc.numBlocks) {
    Serial.print("Erkannte Objekte: ");
    Serial.println(pixy.ccc.numBlocks);

    // Alle erkannten Objekte durchgehen und Koordinaten ausgeben
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial.print("  [Objekt ");
      Serial.print(i + 1);
      Serial.print("] Signatur: ");
      Serial.print(pixy.ccc.blocks[i].m_signature); // Angelerne Farbe (1-7)
      Serial.print(" | X: ");
      Serial.print(pixy.ccc.blocks[i].m_x);         // X-Koordinate (0 bis 315)
      Serial.print(" | Y: ");
      Serial.print(pixy.ccc.blocks[i].m_y);         // Y-Koordinate (0 bis 207)
      Serial.print(" | B: ");
      Serial.print(pixy.ccc.blocks[i].m_width);     // Breite in Pixeln
      Serial.print(" | H: ");
      Serial.println(pixy.ccc.blocks[i].m_height);  // Höhe in Pixeln
    }
  }

  // Kurze Pause vor der nächsten Abfrage (20ms entsprechen ca. 50 FPS)
  delay(20);
}