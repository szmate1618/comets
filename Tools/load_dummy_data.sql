BEGIN TRANSACTION;

INSERT INTO Users VALUES(0, 'placeholder');
INSERT INTO Users VALUES(1, 'placeholder');
INSERT INTO Users VALUES(2, 'placeholder');
INSERT INTO Users VALUES(3, 'placeholder');
INSERT INTO Users VALUES(4, 'placeholder');

INSERT INTO Shapes VALUES(0,
'4 2
0.5 0.5 -0.5 0.5 -0.5 -0.5 0.5 -0.5
1 1 0 1 0 0 1 0
0 3 1 2 1 3' --Note that Unity's backface culling relies on winding order. Counterclockwise faces are culled.
);
INSERT INTO Shapes VALUES(1,'8 6
0.40563535690307617 5.954489707946777
1.7433090209960938 -3.4433088302612305
-0.5190176963806152 5.954489707946777
-1.8566912412643433 -3.4433088302612305
2.2883620262145996 -0.5263512134552002
-2.4017443656921387 -0.5263512134552002
0.7371505498886108 -1.9848299026489258
-0.8505328893661499 -1.9848301410675049
0.5985750555992126 1.0
0.8837865591049194 2.9802322387695312e-08
0.4014253616333008 1.0
0.11621332168579102 0.0
1.0 0.3103873133659363
0.0 0.31038737297058105
0.6692587733268738 0.15519362688064575
0.3307412266731262 0.15519362688064575
1 7 6
4 2 0
6 5 4
1 3 7
4 5 2
6 7 5
');

INSERT INTO Entities VALUES(0, 1, 0, 0, 'inertial', 'dynamic', 'visible', 'collidable', 0, 0, 0);
INSERT INTO Entities VALUES(1, 2, 1, 0, 'inertial', 'dynamic', 'visible', 'collidable', 10, 0, 0);
INSERT INTO Entities VALUES(2, 3, 0, 0, 'inertial', 'dynamic', 'visible', 'collidable', 10, 10, 0);
INSERT INTO Entities VALUES(3, 4, 0, 0, 'inertial', 'dynamic', 'visible', 'collidable', 0, 10, 0);
INSERT INTO Entities VALUES(4, 1, 0, 0, 'anti_inertial', 'dynamic', 'visible', 'collidable', -10, 0, 0);
INSERT INTO Entities VALUES(5, 1, 0, 0, 'para_inertial', 'dynamic', 'visible', 'collidable', 0, -10, 0);

COMMIT;
