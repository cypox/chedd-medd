#include <iostream>
#include <sqlite3.h>
#include <queue>


class Database {
public:
  Database() {};

  ~Database()
  {
    if (m_connected)
    {
      sqlite3_close(m_db);
      std::cout << "disconnected database" << std::endl;
    }
  }

  void connect(std::string path)
  {
    int rc = sqlite3_open(path.c_str(), &m_db);

    if( rc )
    {
      std::cout << "error opening database: " << sqlite3_errmsg(m_db) << std::endl;
      m_connected = false;
    }
    else
    {
      std::cout << "opened database successfully" << std::endl;
      m_connected = true;
    }
  }

  int find_user(std::string username)
  {
    int rc = SQLITE_ERROR;
    if (m_connected)
    {
      std::stringstream ss;
      ss << "SELECT * FROM USERS WHERE NAME = '" << username << "';";
      auto callback = [](void* /* data */, int argc, char** argv, char** azColName) -> int {
        for (int i = 0 ; i < argc ; ++ i)
        {
          std::cout << azColName[i] << " : " << argv[i] << std::endl;
        }
        return 0;
      };
      rc = sqlite3_exec(m_db, ss.str().c_str(), callback, NULL, NULL);
    }
    if (rc)
    {
      std::cout << "error executing statement: " << sqlite3_errmsg(m_db) << std::endl;
    }
    return rc;
  }

  bool execute_statement(std::string st)
  {
    int rc = sqlite3_exec(m_db, st.c_str(), NULL, 0, NULL);
    return rc == SQLITE_OK;
  }

private:
  bool m_connected = false;
  sqlite3 *m_db;
  std::mutex m_queue_mutex;
};
