#ifndef LIB_HPP
#define LIB_HPP

#include <Preferences.h>

extern Preferences prefs; //to remind that theris  an external istance of prefs (in main)

/* ========= DECLARATION OF GENERIC TEMPLATES ========= */

template<typename T>
bool prefPut(const char* key, T value);

template<typename T>
T prefGet(const char* key);



//API-----------------------------------------


template<typename T>
bool modifyPermanentData(const char* dataName, T value){
  prefs.begin("config", false);
  bool ok=prefPut<T>(dataName, value);
  prefs.end();
  return ok;
}

template<typename T>
T getPermanentData(const char* dataName){
  prefs.begin("config", true);
  T value=prefGet<T>(dataName);
  prefs.end();
  return value;
}




//generic prefsPut---------------------------------------------------



template<>
bool prefPut<int>(const char* key, int value) {
  return prefs.putInt(key, value);
}

template<>
bool prefPut<bool>(const char* key, bool value) {
  return prefs.putBool(key, value);
}

template<>
bool prefPut<float>(const char* key, float value) {
  return prefs.putFloat(key, value);
}

template<>
bool prefPut<String>(const char* key, String value) {
  return prefs.putString(key, value);
}



//generic prefsGet---------------------------------------------------





template<>
int prefGet<int>(const char* key) {
  return prefs.getInt(key, -1);
}

template<>
bool prefGet<bool>(const char* key){
  return prefs.getBool(key, false);
}

template<>
float prefGet<float>(const char* key) {
  return prefs.getFloat(key, 0.0);
}

template<>
String prefGet<String>(const char* key) {
  return prefs.getString(key, "");
}



#endif
