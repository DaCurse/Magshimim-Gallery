#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"

class DatabaseAccess : public IDataAccess
{
	public:
		DatabaseAccess();
		virtual ~DatabaseAccess();

};
