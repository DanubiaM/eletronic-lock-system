import sqlite3


class create_db:
    def __init__(self, db = None):
        self.connection = None
        self.cursor = None

        if db:
            self.open(db)
    
    def open(self, db):
        try:
            self.connection = sqlite3.connect(db)
            self.cursor =  self.connection.cursor()
            print("Connection successful in db.")
        except sqlite3.Error as e:
            print("Connection unsuccessful in db.")

    def create_table(self):
        c = self.cursor
        c.execute(""" CREATE TABLE User
        (
            id integer primary key, 
            password integer NOT NULL,
            status integer NOT NULL
        )""")
        
database = create_db("academy.db")
database.create_table()