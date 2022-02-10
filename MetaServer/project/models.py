from datetime import datetime

from werkzeug.security import generate_password_hash, check_password_hash

from project import db


#For the better or worse, we are using the same naming convention here
#as in the database.
class User(db.Model):
	__tablename__ = 'Users'
	ID = db.Column('UserID', db.Integer, primary_key=True)
	Username = db.Column(db.String, unique=True)
	EmailAddress = db.Column(db.String, unique=True)
	PasswordHash = db.Column(db.String)
	LoginEvents = db.relationship('LoginEvent', backref='User', lazy='dynamic')

	def __repr__(self):
		return f"<User({ID},{Username},{EmailAddress},{PasswordHash})>"

	def set_password(self, password):
		self.PasswordHash = generate_password_hash(password)

	def check_password(self, password):
		return check_password_hash(self.PasswordHash, password)

class LoginEvent(db.Model):
	__tablename__ = 'LoginEvents'
	LoginEventID = db.Column(db.Integer, primary_key=True)
	UserID = db.Column(db.Integer, db.ForeignKey('Users.UserID'))
	IPAddress = db.Column(db.String)
	Timestamp = db.Column(db.DateTime, index=True, default=datetime.utcnow)

	def __repr__(self):
		return f"<LoginEvent({LoginEventID},{UserID},{IPAddress},{Timestamp})>"
