/*
// Callback function when NTP Sync is done
void time_is_set() {
  if (DEBUGLEVEL > 0) Serial.println("NTP Server Timestamp Synchronisation");
  if (DEBUGTIMESTAMPACTIVATE) sntp_real_timestamp = DEBUGTIMESTAMP;
}

// function for setting NTP sync intervall
uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 () {
  return INTERVAL_UPDATENTP;
}
*/
void updateTime() {
  unsigned long currentMillis = millis();
  if (currentMillis - pm_updateTime <= INTERVAL_UPDATETIME && !firstFlow) {
    return;
  }
  pm_updateTime = currentMillis;
  
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  //tm = gmtime ((time_t *)&epochTime);
}

void printTime() {
  if (DEBUGLEVEL <= 0) {
    return;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - pm_printTime <= INTERVAL_PRINTTIME && !firstFlow) {
    return;
  }
  pm_printTime = currentMillis;

  //Serial.print("year:");
  //Serial.print(tm->tm_year + 1900);  // years since 1900
  //Serial.print("  month:");
  //Serial.print(tm->tm_mon + 1);      // January = 0 (!)
  //Serial.print("  day:");
  //Serial.print(tm->tm_mday);         // day of month
  Serial.print("  hour:");
  Serial.print(timeClient.getHours());         // hours since midnight  0-23
  Serial.print("  min:");
  Serial.print(timeClient.getMinutes());          // minutes after the hour  0-59
  Serial.print("  sec:");
  Serial.print(timeClient.getSeconds());          // seconds after the minute  0-61*
  //Serial.print("  wday");
  //Serial.print(tm->tm_wday);         // days since Sunday 0-6
  //if (tm->tm_isdst == 1)             // Daylight Saving Time flag
  //  Serial.print("  DST");
  //else
  //  Serial.print("  standard");
  Serial.println();
}
