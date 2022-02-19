REM If venv is already activated, a new activate, and consequently this whole script would fail.
REM This `call activate.bat` is a workaround for that issue.
call activate.bat
set FLASK_APP=metaserver.py
set SECRET_KEY=default_secret_key_do_not_use_in_production
flask run
