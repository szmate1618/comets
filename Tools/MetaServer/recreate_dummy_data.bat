call recreate_empty_db.bat
%SQLITE_EXE% %DB_PATH% ".read load_dummy_data.sql"
timeout /t 3
