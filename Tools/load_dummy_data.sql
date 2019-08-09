BEGIN TRANSACTION;

INSERT INTO Users
(UserID,	PasswordHash) VALUES
(0,			'placeholder'),
(1,			'placeholder'),
(2,			'placeholder'),
(3,			'placeholder'),
(4,			'placeholder');

--Fill table Shapes.

INSERT INTO Entities
(EntityID,	OwnerID,	ShapeID,	TextureID,	Engine,			Dynamics,	Visibility,	Collidability,	PositionX,	PositionY,	Orientation) VALUES
(0,			1,			2,			0,			'inertial',		'dynamic',	'visible',	'collidable',	0,			0,			0),
(1,			2,			1,			1,			'inertial',		'dynamic',	'visible',	'collidable',	10,			0,			0),
(2,			3,			2,			0,			'inertial',		'dynamic',	'visible',	'collidable',	10,			10,			0),
(3,			4,			0,			0,			'inertial',		'dynamic',	'visible',	'collidable',	0,			10,			0),
(4,			1,			0,			0,			'anti_inertial','dynamic',	'visible',	'collidable',	-10,		0,			0),
(5,			1,			3,			0,			'para_inertial','dynamic',	'visible',	'collidable',	0,			-10,		0),
(6,			1,			5,			0,			'inertial',		'dynamic',	'visible',	'collidable',	20,			0,			0);

COMMIT;
