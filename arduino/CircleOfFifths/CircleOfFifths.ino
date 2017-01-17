//#define DEBUG // uncomment this line to turn on debugging information which is really helpful after first assembling your circle of fifths
#define MUSE_USE_SERIAL1 // this tells MUSE to use the MIDI port rather than using the Serial connection over USB

#define SELECTOR_BIT0_PIN 17
#define SELECTOR_BIT1_PIN 16
#define SELECTOR_BIT2_PIN 15
#define SELECTOR_BIT3_PIN 14

#include <MUSE.h>

MUSE muse;

int roots[] = { MUSE_C4, MUSE_G4, MUSE_D4, MUSE_A4, MUSE_E4, MUSE_B4, MUSE_FS4, MUSE_CS4, MUSE_GS4, MUSE_DS4, MUSE_AS4, MUSE_F4 };
int selector = 0;

void setup() {
  muse.setup();

  // Callbacks for the 12 different notes around the circle of fifths
  muse.registerDigitalInputCallback(C_Callback, 8, false);
  muse.registerDigitalInputCallback(G_Callback, 7, false);
  muse.registerDigitalInputCallback(D_Callback, 6, false);
  muse.registerDigitalInputCallback(A_Callback, 5, false);
  muse.registerDigitalInputCallback(E_Callback, 4, false);
  muse.registerDigitalInputCallback(B_Callback, 3, false);
  muse.registerDigitalInputCallback(Fs_Callback, 2, false);
  muse.registerDigitalInputCallback(Db_Callback, 20, false);
  muse.registerDigitalInputCallback(Ab_Callback, 19, false);
  muse.registerDigitalInputCallback(Eb_Callback, 18, false);
  muse.registerDigitalInputCallback(Bb_Callback, 10, false);
  muse.registerDigitalInputCallback(F_Callback, 9, false);

  // Callbacks for changes on the 4 selector pins
  muse.registerDigitalInputCallback(bit0, SELECTOR_BIT0_PIN, false);
  muse.registerDigitalInputCallback(bit1, SELECTOR_BIT1_PIN, false);
  muse.registerDigitalInputCallback(bit2, SELECTOR_BIT2_PIN, false);
  muse.registerDigitalInputCallback(bit3, SELECTOR_BIT3_PIN, false);

  initSelector();
}

void loop() {
  muse.loop(); // check for and respond to events that we registered
}

void initSelector() {
    int bit0 = digitalRead(SELECTOR_BIT0_PIN);
    int bit1 = digitalRead(SELECTOR_BIT1_PIN);
    int bit2 = digitalRead(SELECTOR_BIT2_PIN);
    int bit3 = digitalRead(SELECTOR_BIT3_PIN);

    selector = bit0 | (bit1 << 1) | (bit2 << 2) | (bit3 << 3);
    if(selector > 11) {
      selector = 0;
    }
#ifdef DEBUG
    debugSelector();
#endif
}

#ifdef DEBUG
void debugSelector() {
  switch(selector) {
    case 0:
        Serial.println("Selected C Major");
        break;
    case 1:
        Serial.println("Selected G Major");
        break;
    case 2:
        Serial.println("Selected D Major");
        break;
    case 3:
        Serial.println("Selected A Major");
        break;
    case 4:
        Serial.println("Selected E Major");
        break;
    case 5:
        Serial.println("Selected B Major");
        break;
    case 6:
        Serial.println("Selected F# Major");
        break;
    case 7:
        Serial.println("Selected Db Major");
        break;
    case 8:
        Serial.println("Selected Ab Major");
        break;
    case 9:
        Serial.println("Selected Eb Major");
        break;
    case 10:
        Serial.println("Selected Bb Major");
        break;
    case 11:
        Serial.println("Selected F Major");
        break;
  }
}
#endif

void bit0(bool state) {
  selector = (selector & 0b1110) | state;
  if(selector > 11) {
    selector = 0;
  }

#ifdef DEBUG
  debugSelector();
#endif
}

void bit1(bool state) {
    selector = (selector & 0b1101) | (state << 1);
    if(selector > 11) {
      selector = 0;
    }

#ifdef DEBUG
    debugSelector();
#endif
}

void bit2(bool state) {
    selector = (selector & 0b1011) | (state << 2);
    if(selector > 11) {
      selector = 0;
    }
#ifdef DEBUG
    debugSelector();
#endif
}

void bit3(bool state) {
    selector = (selector & 0b0111) | (state << 3);
    if(selector > 11) {
      selector = 0;
    }
#ifdef DEBUG
    debugSelector();
#endif
}


void C_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("C ");
#endif
  doNote(state, MUSE_C4);
}

void G_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("G ");
#endif
  doNote(state, MUSE_G4);
}

void D_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("D ");
#endif
  doNote(state, MUSE_D4);
}
void A_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("A ");
#endif
  doNote(state, MUSE_A4);
}

void E_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("E ");
#endif
  doNote(state, MUSE_E4);
}
void B_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("B ");
#endif
  doNote(state, MUSE_B4);
}

void Fs_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("F# ");
#endif
  doNote(state, MUSE_FS4);
}

void Db_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("Db ");
#endif
  doNote(state, MUSE_CS4);
}

void Ab_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("Ab ");
#endif
  doNote(state, MUSE_GS4);
}

void Eb_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("Eb ");
#endif
  doNote(state, MUSE_DS4);
}

void Bb_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("Bb ");
#endif
  doNote(state, MUSE_AS4);
}

void F_Callback(bool state) {
#ifdef DEBUG
  if(state) {
    Serial.print("Released ");
  } else {
    Serial.print("Pressed ");
  }
  Serial.print("F ");
#endif
  doNote(state, MUSE_F4);
}
void doNote(bool state, int note) {
    for(int i = -1; i < 2; i++) {
      if(roots[(selector+i+12)%12] == note) {
#ifdef DEBUG
        Serial.print("major");
#endif
        doMajorTriad(state,note);
      }
    }
    for(int i = 2; i < 5; i++) {
      if(roots[(selector+i)%12] == note) {
#ifdef DEBUG
        Serial.print("minor");
#endif
        doMinorTriad(state,note);
      }
    }
    if(roots[(selector+5)%12] == note) {
#ifdef DEBUG
        Serial.print("diminished");
#endif

      doDiminishedTriad(state,note);
    }
#ifdef DEBUG
    Serial.println();
#endif
}

void doMajorTriad(bool state, int note) {
  if(state) {
    muse.noteOff(note);
    muse.noteOff(note+4);
    muse.noteOff(note+7);
  } else {
    muse.noteOn(note);
    muse.noteOn(note+4);
    muse.noteOn(note+7);
  }
}

void doMinorTriad(bool state, int note) {
  if(state) {
    muse.noteOff(note);
    muse.noteOff(note+3);
    muse.noteOff(note+7);
  } else {
    muse.noteOn(note);
    muse.noteOn(note+3);
    muse.noteOn(note+7);
  }
}

void doDiminishedTriad(bool state, int note) {
  if(state) {
    muse.noteOff(note);
    muse.noteOff(note+3);
    muse.noteOff(note+6);
  } else {
    muse.noteOn(note);
    muse.noteOn(note+3);
    muse.noteOn(note+6);
  }
}
