PRAGMA encoding=utf8;
PRAGMA foreign_keys=ON;

BEGIN TRANSACTION;

--Drop the tables in the reverse order of their creation,
--avoiding to break the foreign key contraints.
DROP TABLE IF EXISTS Entities;
DROP TABLE IF EXISTS Shapes;
DROP TABLE IF EXISTS Users;

CREATE TABLE Users
(
	UserID INTEGER PRIMARY KEY ASC,
	PasswordHash TEXT
);

CREATE TABLE Shapes
(
	ShapeID INTEGER PRIMARY KEY ASC,
	Shape TEXT
);

CREATE TABLE Entities
(
	EntityID INTEGER PRIMARY KEY ASC,
	OwnerID INTEGER references Users(UserID),
	ShapeID INTEGER references Shapes(ShapeID),
	TextureID INTEGER,
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
