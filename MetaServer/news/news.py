import glob
import os
import datetime


class Post:
	def __init__(self, title, content, creation_time, modification_time):
		self.title = title
		self.content = content
		self.creation_time = creation_time
		self.modification_time = modification_time

class News:
	parent_directory_path = os.path.dirname(os.path.realpath(__file__))
	parent_directory_name = os.path.basename(parent_directory_path)
	posts_folder_name = 'posts'
	posts_folder_path = os.path.join(parent_directory_path, posts_folder_name)

	def __init__(self):
		self.last_fetch_time = datetime.datetime.min
		self.fetch_interval = datetime.timedelta(seconds = 30)
		self.news_metadata = {}
		self.old_news_metadata = {}
		self.news = {}

	@staticmethod
	def is_post_file(dir_entry):
		return os.path.isfile(dir_entry.path) and os.path.splitext(dir_entry.path)[1] == '.txt'

	@staticmethod	
	def create_post_from_file(dir_entry):
		title = os.path.basename(dir_entry.path)
		with open(dir_entry.path, 'r') as file:
			 content = file.read()
		creation_time = datetime.datetime.fromtimestamp(dir_entry.stat().st_ctime).isoformat()
		modification_time = datetime.datetime.fromtimestamp(dir_entry.stat().st_mtime).isoformat()
		return Post(title, content, creation_time, modification_time)
	
	def fetch_news_metadata (self):
		self.old_news_metadata = self.news_metadata
		self.news_metadata = { os.path.getctime(f.path): f for f in os.scandir(self.posts_folder_path) if self.is_post_file(f) }
	
	def fetch_news (self):
		if datetime.datetime.utcnow() - self.last_fetch_time < self.fetch_interval:
			return

		self.last_fetch_time = datetime.datetime.utcnow()
		self.fetch_news_metadata ()
		
		for creation_time in self.news_metadata:
			if (not creation_time in self.old_news_metadata or
				self.news_metadata[creation_time].stat().st_mtime > self.old_news_metadata[creation_time].stat().st_mtime):
				self.news[creation_time] = self.create_post_from_file(self.news_metadata[creation_time])
				
		for creation_time in self.news:
			if not creation_time in self.news_metadata:
				del self.news_metadata[creation_time]
	def get_news(self):
		self.fetch_news()
		return [self.news[k] for k in sorted(self.news.keys(), reverse = True)]
