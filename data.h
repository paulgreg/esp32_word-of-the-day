#define LANG_LEN 4
#define TRANS_LEN 50
#define NB 5

struct Words {
  char languages[NB][LANG_LEN];
  char translations[NB][TRANS_LEN];
};

/* word-of-the-day.json
{"word":"stumble v.","languages":["fr","sp","it","po"],"translations":["achopper","trastabillar","barcollare","cambalear"]}
*/

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
  }
  
  return true;
}
