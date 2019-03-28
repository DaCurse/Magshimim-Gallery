#pragma once
#include <io.h>
#include "IDataAccess.h"
#include "sqlite3.h"

#define DB_FILENAME "gallerydb.sqlite"

class DatabaseAccess : public IDataAccess
{
	public:
		DatabaseAccess() = default;
		~DatabaseAccess() = default;

		bool open() override;
		void close() override;
		void clear() override;

		const std::list<Album> getAlbums() override;
		const std::list<Album> getAlbumsOfUser(const User& user) override;
		void createAlbum(const Album& album) override;
		void deleteAlbum(const std::string& albumName, int userId) override;
		bool doesAlbumExists(const std::string& albumName, int userId) override;
		Album openAlbum(const std::string& albumName) override;
		void closeAlbum(Album& pAlbum) override;
		void printAlbums() override;

		void addPictureToAlbumByName(const std::string& albumName, const Picture& picture) override;
		void removePictureFromAlbumByName(const std::string& albumName, const std::string& pictureName) override;
		void tagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId) override;
		void untagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId) override;

		void printUsers() override;
		User getUser(int userId) override;
		void createUser(User& user) override;
		void deleteUserAlbums(const User& user) override;
		void deleteUser(const User& user) override;
		bool doesUserExists(int userId) override;


		int countAlbumsOwnedOfUser(const User& user) override;
		int countAlbumsTaggedOfUser(const User& user) override;
		int countTagsOfUser(const User& user) override;
		float averageTagsPerAlbumOfUser(const User& user) override;

		User getTopTaggedUser() override;
		Picture getTopTaggedPicture() override;
		std::list<Picture> getTaggedPicturesOfUser(const User& user) override;

	private:
		sqlite3* db;
		std::list<Album> m_albums;
		std::list<User> m_users;

		bool execSql(std::string stmt);


};
