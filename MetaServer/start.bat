REM If venv is already activated, a new activate, and consequently this whole script would fail.
REM This `cmd.exe /c` is a workaround for that issue.
cmd.exe /c activate.bat
set FLASK_APP=metaserver.py
flask run
