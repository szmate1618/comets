call db_env_vars.bat
%SQLITE_EXE% %DB_PATH% ".dump" > backup_dump.sql
%SQLITE_EXE% %DB_PATH% ".read recreate_empty_db.sql"
