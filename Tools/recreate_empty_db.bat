call db_path.bat
sqlite3_x86.exe %DB_PATH% ".dump" > backup_dump.sql
sqlite3_x86.exe %DB_PATH% ".read recreate_empty_db.sql"
