#include "DatabaseAccess.h"

bool DatabaseAccess::open()
{
	db = nullptr;

	int fileExists = _access(DB_FILENAME, 0);
	int res = sqlite3_open(DB_FILENAME, &db);

	if (res != SQLITE_OK)
	{
		std::cout << "Failed to open database" << std::endl;
		return false;
	}

	if (fileExists == -1)
	{
		std::string dbSchema = "CREATE TABLE IF NOT EXISTS users ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(255) NOT NULL ); CREATE TABLE IF NOT EXISTS albums ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(255) NOT NULL, creation_date DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL, user_id INTEGER NOT NULL, FOREIGN KEY (user_id) REFERENCES users(id) ); CREATE TABLE IF NOT EXISTS pictures ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(255) NOT NULL, location TEXT NOT NULL, creation_date DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL, album_id INTEGER NOT NULL, FOREIGN KEY (album_id) REFERENCES albums(id) ); CREATE TABLE IF NOT EXISTS tags ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, picture_id INTEGER NOT NULL, user_id INTEGER NOT NULL, FOREIGN KEY (picture_id) REFERENCES pictures(id), FOREIGN KEY (user_id) REFERENCES users(id) );";
		
		execSql(dbSchema);
	}

	return true;
}

void DatabaseAccess::close()
{
	sqlite3_close(db);
	db = nullptr;
}

void DatabaseAccess::clear()
{
	m_users.clear();
	m_albums.clear();
}

bool DatabaseAccess::execSql(std::string stmt)
{
	char* errMsg = nullptr;
	int res = sqlite3_exec(db, stmt.c_str(), nullptr, nullptr, &errMsg);

	if (res != SQLITE_OK)
	{
		std::cout << "SQL Error: " << errMsg << std::endl;
		return false;
	}

	return true;
}
