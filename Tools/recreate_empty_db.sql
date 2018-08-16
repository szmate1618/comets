PRAGMA encoding=utf8;
PRAGMA foreign_keys=ON;

BEGIN TRANSACTION;

DROP TABLE IF EXISTS Users;
CREATE TABLE Users
(
	UserID INTEGER PRIMARY KEY ASC,
	PasswordHash TEXT
);

DROP TABLE IF EXISTS Hulls;
CREATE TABLE Hulls
(
	HullID INTEGER PRIMARY KEY ASC,
	shape TEXT,
	texture TEXT
);

DROP TABLE IF EXISTS Entities;
CREATE TABLE Entities
(
	EntityID INTEGER PRIMARY KEY ASC,
	OwnerID references Users(UserID),
	HullID references Hulls(HullID),
	Engine TEXT, --inertial, anti_intertial, para_inertial, pre_programmed
	Dynamics TEXT, --static_, dynamic
	Visibility TEXT, --visible, invisible
	Collidability TEXT, --collidable, uncollidable
	PositionX REAL,
	PositionY REAL,
	Orientation REAL
	--TODO: Also add velocity, acceleration, friction, etc.
);

COMMIT;
