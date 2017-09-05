#ifndef __US_DATABASE_CLIENT_MANAGER_HPP__
#define __US_DATABASE_CLIENT_MANAGER_HPP__

// #ifndef __US_DATA_MANAGER_HPP__
// #include "us_data_manager.hpp"
// #endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

struct st_mysql;

namespace unispace
{

	namespace us_database_client_manager
	{

		//_US_DATA_MANAGER_DLL
		mongoc_client_t*
		create_mongodb_client(const char* host,
			unsigned short port,
			const char* user,
			const char* passwd);

		//_US_DATA_MANAGER_DLL
		void release_mongodb_client(mongoc_client_t* client);

		//_US_DATA_MANAGER_DLL
		st_mysql* create_mysql_client(const char *host,
			const char *user,
			const char *passwd,
			const char *db,
			unsigned int port,
			const char *unix_socket,
			unsigned long clientflag);

		//_US_DATA_MANAGER_DLL
		void release_mysql_client(st_mysql* client);

	};

}

#endif //!__US_DATABASE_CLIENT_MANAGER_HPP__