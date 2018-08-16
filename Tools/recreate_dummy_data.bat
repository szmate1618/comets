call recreate_empty_db.bat
sqlite3_x86.exe %DB_PATH% ".read load_dummy_data.sql"
