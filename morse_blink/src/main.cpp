#include "Arduino.h"

#define LED_BUILTIN 13
#define DIT 100
#define DAH 300
#define MORSE_SPACE 150
#define LETTER_SPACE 450
#define WORD_SPACE 600

const char *morse[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// Get the Morse code for a given letter
const char *get_morse_code(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return morse[letter - 'a'];
    }
    return "";
}

// Blink a Morse code sequence
void blink_morse_letter(const char *sequence) {
    for (int i = 0; sequence[i] != '\0'; i++) {
        if (sequence[i] == '.') {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(DIT);
            digitalWrite(LED_BUILTIN, LOW);
        } else if (sequence[i] == '-') {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(DAH);
            digitalWrite(LED_BUILTIN, LOW);
        }
        if (sequence[i + 1] != '\0') {
            delay(MORSE_SPACE);
        }
    }
    delay(LETTER_SPACE);
}

// Blink a message in Morse code
void blink_morse_message(const char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        char letter = message[i];
        if (letter == ' ') {
            delay(WORD_SPACE);
            continue;
        }
        const char *morse_code = get_morse_code(letter);
        blink_morse_letter(morse_code);
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    const char *message = "hello morse";

    Serial.print("Blinking message: ");
    Serial.println(message);

    blink_morse_message(message);
    delay(5000);
}
