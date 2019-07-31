import glob
import os
import subprocess


all_files = glob.glob('..\Shapes\*')
shape_files = glob.glob('..\Shapes\*-*.shp')

diff = len(all_files) - len(shape_files)
assert diff == 0,\
	f"Warning: {diff} file(s) in the shape file folder do(es) not follow the shape file naming convention."

for fullpath in shape_files:
	path, filename = os.path.split(fullpath)
	shape_id = filename.split('-', 1)[0]
	shape_name = filename.split('-', 1)[1] #Curently unused.
	with open(fullpath, 'r') as shape_file:
		shape = shape_file.read()
		insert_statement = f'INSERT INTO Shapes VALUES ({shape_id},\n\'{shape}\');'
		subprocess.run([os.environ['SQLITE_EXE'], os.environ['DB_PATH'], insert_statement], check = True)
