#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"

class DatabaseAccess : public IDataAccess
{
	public:
		DatabaseAccess();
		virtual ~DatabaseAccess();

		virtual bool open();
		virtual void close();
		virtual void clear();

		virtual const std::list<Album> getAlbums();
		virtual const std::list<Album> getAlbumsOfUser(const User& user);
		virtual void createAlbum(const Album& album);
		virtual void deleteAlbum(const std::string& albumName, int userId);
		virtual bool doesAlbumExists(const std::string& albumName, int userId);
		virtual Album openAlbum(const std::string& albumName);
		virtual void closeAlbum(Album& pAlbum);
		virtual void printAlbums();

		virtual void addPictureToAlbumByName(const std::string& albumName, const Picture& picture);
		virtual void removePictureFromAlbumByName(const std::string& albumName, const std::string& pictureName);
		virtual void tagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId);
		virtual void untagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId);

		virtual void printUsers();
		virtual User getUser(int userId);
		virtual void createUser(User& user);
		virtual void deleteUserAlbums(const User& user);
		virtual void deleteUser(const User& user);
		virtual bool doesUserExists(int userId);


		virtual int countAlbumsOwnedOfUser(const User& user);
		virtual int countAlbumsTaggedOfUser(const User& user);
		virtual int countTagsOfUser(const User& user);
		virtual float averageTagsPerAlbumOfUser(const User& user);

		virtual User getTopTaggedUser();
		virtual Picture getTopTaggedPicture();
		virtual std::list<Picture> getTaggedPicturesOfUser(const User& user);

};
