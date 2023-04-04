#include "mysql.h"

namespace mysql {

DatabaseConnection::DatabaseConnection(const String &host_, const String &user_, const String &pass_, const String &db_)
  : host(host_), user(user_), pass(pass_), db(db_) {
    error_code = kUninitialized;
  }

ErrorCode DatabaseConnection::Connect() {
  // Kill everything if the Serial is not connected
  if (!Serial) {
    return kSerialOff;
  }
  
  // Save the variables
	Serial.print("host="); Serial.println(host.c_str());
	Serial.print("user="); Serial.println(user.c_str());
	Serial.print("pass="); Serial.println(pass.c_str());
	Serial.print("db="); Serial.println(db.c_str());
  Serial.println("mysql_connect()");

  // If no response is given it's a fail
  if (!Serial.available())
    return error_code = kFail;
	int x = Serial.read();

  if (x == '-')
    return error_code = kFail;

  while (x <= 0) {
    // If no response is given it's a fail
    if (!Serial.available())
      return error_code = kFail;
    x = Serial.read();

    if (x == '-')
      return error_code = kFail;
  }

  return error_code = kSuccess;
}

ErrorCode DatabaseConnection::Query(const String &query) {
  // Kill everything if the Serial is not connected
  if (!Serial) {
    return kSerialOff;
  }
  
  // Save the query
	Serial.print("query="); Serial.println(query);

  // If no response is given it's a fail
  if (!Serial.available())
    return error_code = kFail;
	int x = Serial.read();

  if (x == '-' || x == '0')
    return kFail;

  while (x <= 0) {
    // If no response is given it's a fail
    if (!Serial.available())
      return error_code = kFail;
    x = Serial.read();

    if (x == '-' || x == '0')
      return kFail;
  }

  return kSuccess;
}

ErrorCode DatabaseConnection::ResultSetQuery(const String &query, String &result_set) {
  // Kill everything if the Serial is not connected
  if (!Serial) {
    return kSerialOff;
  }

  Serial.println(query);

  // If no response is given it's a fail
  if (!Serial.available())
    return error_code = kFail;
  
  result_set = Serial.readString();
  if (result_set == "-")
    return error_code = kFail;

  while (result_set.length() <= 0) {
    // If no response is given it's a fail
    if (!Serial.available())
      return error_code = kFail;
    result_set = Serial.readString();

    if (result_set == "-")
      return error_code = kFail;
  }

  return error_code = kSuccess;
}

DatabaseConnection::~DatabaseConnection() {
  // Kill everything if the Serial is not connected
  if (!Serial) {
    error_code = kSerialOff;
    return;
  }

	Serial.println("mysql_close()");
}

} /* namespace mysql */
