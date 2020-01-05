PRAGMA encoding=utf8;
PRAGMA foreign_keys=ON;

BEGIN TRANSACTION;

--Drop the tables in the reverse order of their creation,
--avoiding to break the foreign key contraints.
DROP TABLE IF EXISTS LoginEvents;
DROP TABLE IF EXISTS Users;

CREATE TABLE Users
(
	UserID INTEGER PRIMARY KEY ASC,
	UserName TEXT UNIQUE,
	EmailAddress TEXT UNIQUE,
	PasswordHash TEXT
);

CREATE TABLE LoginEvents
(
	LoginEventID INTEGER PRIMARY KEY ASC,
	UserID INTEGER references Users(UserID),
	IPAddress TEXT,
	Timestamp TEXT
);

COMMIT;
