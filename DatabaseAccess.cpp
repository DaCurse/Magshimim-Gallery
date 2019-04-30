#include "DatabaseAccess.h"

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
		std::string dbSchema = "CREATE TABLE IF NOT EXISTS users ( id INTEGER PRIMARY KEY NOT NULL, name VARCHAR(255) NOT NULL ); CREATE TABLE IF NOT EXISTS albums ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(255) NOT NULL, creation_date DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL, user_id INTEGER NOT NULL, FOREIGN KEY (user_id) REFERENCES users(id) ); CREATE TABLE IF NOT EXISTS pictures ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(255) NOT NULL, location TEXT NOT NULL, creation_date DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL, album_id INTEGER NOT NULL, FOREIGN KEY (album_id) REFERENCES albums(id) ); CREATE TABLE IF NOT EXISTS tags ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, picture_id INTEGER NOT NULL, user_id INTEGER NOT NULL, FOREIGN KEY (picture_id) REFERENCES pictures(id), FOREIGN KEY (user_id) REFERENCES users(id) );";
		
		execSql(dbSchema);
	}

	return true;
}

void DatabaseAccess::close()
{
	sqlite3_close(db);
	db = nullptr;
}

void DatabaseAccess::deleteAlbum(const std::string & albumName, int userId)
{
	std::string deleteAlbumStmt = "DELETE FROM albums WHERE name = '" + albumName + "' AND user_id = " + std::to_string(userId);
	execSql(deleteAlbumStmt);
}

void DatabaseAccess::addPictureToAlbumByName(const std::string & albumName, const Picture & picture)
{
	std::string addPicByAlbumNameStmt = "INSERT INTO pictures (name, location, album_id) VALUES ('" + picture.getName() + "', " + std::to_string(picture.getId()) + ", (SELECT id FROM albums WHERE name = '" + albumName + "'))";
	execSql(addPicByAlbumNameStmt);
}

void DatabaseAccess::removePictureFromAlbumByName(const std::string & albumName, const std::string & pictureName)
{
	std::string removePicByNameStmt = "DELETE FROM pictures WHERE name = '" + pictureName + "' AND album_id = (SELECT id FROM albums WHERE name = '" + albumName + "')";
	execSql(removePicByNameStmt);
}

void DatabaseAccess::tagUserInPicture(const std::string & albumName, const std::string & pictureName, int userId)
{
	std::string tagUserStmt = "INSERT INTO tags (picture_id, user_id) VALUES ((SELECT id FROM pictures WHERE name = '" + pictureName + "' AND album_id = (SELECT id FROM albums WHERE name = '" + albumName  +"')), " + std::to_string(userId) + ")";
	execSql(tagUserStmt);
}

void DatabaseAccess::untagUserInPicture(const std::string & albumName, const std::string & pictureName, int userId)
{
	std::string untagUserStmt = "DELETE FROM tags WHERE picture_id = (SELECT id FROM pictures WHERE name = '" + pictureName + "' AND album_id = (SELECT id FROM albums WHERE name = '" + albumName + "') AND user_id = " + std::to_string(userId) + ")";
	execSql(untagUserStmt);
}

void DatabaseAccess::createUser(User & user)
{
	std::string createUserStmt = "INSERT INTO users (id, name) VALUES (" + std::to_string(user.getId())  + ", '" + user.getName() + "')";
	execSql(createUserStmt);
}

void DatabaseAccess::deleteUser(const User & user)
{
	std::string delUserStmt = "DELETE FROM users WHERE id = " + std::to_string(user.getId()) + "";
	execSql(delUserStmt);
}
