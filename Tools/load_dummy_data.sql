BEGIN TRANSACTION;

INSERT INTO Users
(UserID,	PasswordHash) VALUES
(0,			'placeholder'),
(1,			'placeholder'),
(2,			'placeholder'),
(3,			'placeholder'),
(4,			'placeholder');

--Fill table Shapes.

INSERT INTO CollisionBehaviors
(ShapeID,	Condition,				Action,		Parameter1,	Parameter2, Parameter3) VALUES
(8,			'on_collision_take',	'explode',	0,			-1,			-1),
(7,			'on_collision_take',	'explode',	4,			8,			7),
(6,			'on_collision_take',	'explode',	4,			7,			6);

INSERT INTO Entities
(EntityID,	OwnerID,	ShapeID,	TextureID,	Engine,				Dynamics,	Visibility,	Collidability,	PositionX,	PositionY,	Orientation) VALUES
(0,			1,			2,			8,			'inertial',			'dynamic',	'visible',	'collidable',	0,			0,			0),
(1,			2,			1,			2,			'inertial',			'dynamic',	'visible',	'collidable',	10,			0,			0),
(2,			3,			2,			8,			'inertial',			'dynamic',	'visible',	'collidable',	10,			10,			0),
(3,			4,			0,			1,			'inertial',			'dynamic',	'visible',	'collidable',	0,			10,			0),
(4,			1,			0,			1,			'anti_inertial',	'dynamic',	'visible',	'collidable',	-10,		0,			0),
(5,			1,			3,			3,			'para_inertial',	'dynamic',	'visible',	'collidable',	0,			-10,		0),
(6,			1,			5,			4,			'inertial',			'dynamic',	'visible',	'collidable',	20,			0,			0),
(7,			2,			5,			4,			'inertial',			'dynamic',	'visible',	'collidable',	25,			0,			0),
(8,			0,			6,			5,			'inertial',			'dynamic',	'visible',	'collidable',	45,			-20,		0),
(9,			0,			7,			6,			'inertial',			'dynamic',	'visible',	'collidable',	45,			0,			0),
(10,		0,			8,			7,			'inertial',			'dynamic',	'visible',	'collidable',	45,			20,			0),
(11,		0,			9,			9,			'inertial',			'dynamic',	'visible',	'collidable',	-25,		0,			0);

COMMIT;
