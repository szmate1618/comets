BEGIN TRANSACTION;

INSERT INTO Users
(UserID,	UserName,	EmailAddress,			PasswordHash) VALUES
--bcrypt hash of password 'admin'.
(0,			'admin',	'example@example.com',	'$2y$12$20Fa3j393T3hHm3XrbSrwOzXFhM1HAV77iiEQe5wB.zaOrridSg.C');

COMMIT;
