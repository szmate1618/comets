BEGIN TRANSACTION;

INSERT INTO Users VALUES(0, 'placeholder');
INSERT INTO Users VALUES(1, 'placeholder');
INSERT INTO Users VALUES(2, 'placeholder');
INSERT INTO Users VALUES(3, 'placeholder');
INSERT INTO Users VALUES(4, 'placeholder');

INSERT INTO Hulls VALUES(0, 'placeholder', 'placeholder');

INSERT INTO Entities VALUES(0, 1, 0, 'inertial', 'dynamic', 'visible', 'collidable', 0, 0, 0);
INSERT INTO Entities VALUES(1, 2, 0, 'inertial', 'dynamic', 'visible', 'collidable', 10, 0, 0);
INSERT INTO Entities VALUES(2, 3, 0, 'inertial', 'dynamic', 'visible', 'collidable', 10, 10, 0);
INSERT INTO Entities VALUES(3, 4, 0, 'inertial', 'dynamic', 'visible', 'collidable', 0, 10, 0);
INSERT INTO Entities VALUES(4, 1, 0, 'anti_inertial', 'dynamic', 'visible', 'collidable', -10, 0, 0);
INSERT INTO Entities VALUES(5, 1, 0, 'para_inertial', 'dynamic', 'visible', 'collidable', 0, -10, 0);

COMMIT;
