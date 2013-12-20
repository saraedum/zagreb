#ifndef MASTER_SLAVE_H
#define MASTER_SLAVE_H

// make this Arduino a slave by putting a jumper between MASTER_SLAVE_PIN and 13
const bool MASTER = (pinMode(13, OUTPUT), digitalWrite(13, HIGH), pinMode(MASTER_SLAVE_PIN, INPUT_PULLUP), (digitalRead(MASTER_SLAVE_PIN)==HIGH));

#endif
