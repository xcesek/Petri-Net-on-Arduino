

log(int enabled, char *str1, char *str2) {
  if (enabled) {
    Serial.print(str1); Serial.println(str2);
  }
}
