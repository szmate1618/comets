# Tools
Tools for working with the game data database.
The most important files are the following ones:
- sqlite3_x86.exe  
  The SQLite3 executable.
- db_env_vars.bat  
  Defines an environment variable containing the path and name of the database,
  and an other one containing the name of the SQLite3 executable.
- recreate_empty_db.bat  
  Dumps all existing data into backup_dump.sql, then drops all existing tables and recreates them.
- recreate_dummy_data.bat  
  Calls recreate_empty_db.bat then fills the tables with dummy data for testing.
- db_command_line.bat  
  Opens a command line for the database.
