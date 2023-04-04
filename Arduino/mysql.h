#ifndef MYSQL_H
#define MYSQL_H

#include "Arduino.h"

namespace mysql {

enum ErrorCode {
  kSuccess,
  kUninitialized,
  kSerialOff,
  kFail
};

/**
 * @brief The connection based on the program "mysqlio" uses the Serial Port as a medium between PHP and the mysql database.
 * Will fail miserably without the Serial being started.
 * 
 */
class DatabaseConnection {
 public:
  /**
   * @brief Save the given host, user, password and database name. DOES NOT MAKE THE ACTUAL CONNECTION.
   * 
   * @param host IP of the host.
   * @param user User to be used.
   * @param pass Password for the user.
   * @param db Database name.
   */
  DatabaseConnection(const String &host_, const String &user_, const String &pass_, const String &db_);

  /**
   * @brief Makes the connection to the database.
   * 
   * @return ErrorCode Whether the oepration failed or not.
   */
  ErrorCode Connect();

  /**
   * @brief Send a query to the database.
   * 
   * @param query Query to be sent.
   * @return ErrorCode Whether the oepration failed or not.
   */
  ErrorCode Query(const String &query);

  /**
   * @brief Send a query to the database that expects a ResultSet.
   * 
   * @details No actual idea if this function works.
   * @param[in] query Query to be sent.
   * @param[out] result_set Results of the query.
   * @return ErrorCode Whether the oepration failed or not.
   */
  ErrorCode ResultSetQuery(const String &query, String &result_set);

  /**
   * @brief Kills the connection to the database.
   * 
   */
  ~DatabaseConnection();

  /**
   * @brief Get the current error code.
   * 
   * @return ErrorCode Internal error code.
   */
  ErrorCode get_error_code() const {
    return error_code;
  }

 private:
  ErrorCode error_code;

  const String host;
  const String user;
  const String pass;
  const String db;
};

/**
 * @brief Return the string form of the error code.
 * 
 * @details Commented to reduce used memory on the device.
 * @param code Error code to be converted.
 * @return const char* String form of the error code.
 */
// const char *Error_code_to_string(const ErrorCode code) {
//   switch (code) {
//     case kSuccess: return "Success";
//     case kUninitialized: return "Uninitialized";
//     case kSerialOff: return "SerialOff";
//     case kFail: return "Fail";
//   }
// }

} /* namespace mysql */

#endif /* MYSQL_H */
