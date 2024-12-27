#define LANG_LEN 4
#define TRANS_LEN 50
#define NB 5

struct Words {
  char languages[NB][LANG_LEN];
  char translations[NB][TRANS_LEN];
};

/* word-of-the-day.json
{"languages":["en:","fr:","sp:","it:","po:"],"translations":["toe","doigt","punter\\xeda","mignolo","ponta"]}
*/

void decodeEscapeSequences(char* str) {
  char buffer[TRANS_LEN];
  int i = 0, j = 0;
  while (str[i] != '\0') {
    if (str[i] == '\\' && str[i+1] == 'x') {
      // Found an escape sequence like \xeda
      char hex[3] = { str[i+2], str[i+3], '\0' };  // Extract the 2 hex digits after \x
      int value = strtol(hex, NULL, 16);  // Convert hex to integer
      buffer[j++] = (char) value;  // Store the corresponding character
      i += 4;  // Skip over \x and the 2 hex digits
    } else {
      buffer[j++] = str[i++];
    }
  }
  buffer[j] = '\0';  // Null-terminate the buffer
  strcpy(str, buffer);  // Copy the processed string back into the original buffer
}

boolean fillWordsFromJson(JSONVar json, Words* data) {
  if (!json.hasOwnProperty("languages")) {
    Serial.println("fillWordsFromJson: languages not found");
    return false;
  }
  if (!json.hasOwnProperty("translations")) {
    Serial.println("fillWordsFromJson: translations not found");
    return false;
  }

  for (int i = 0; i < NB; i++) {
    sprintf(data->languages[i], "%s", (const char*) json["languages"][i]);
    sprintf(data->translations[i], "%s", (const char*) json["translations"][i]);
    decodeEscapeSequences(data->translations[i]);
  }
  
  return true;
}