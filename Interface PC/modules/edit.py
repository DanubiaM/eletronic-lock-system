import sqlite3
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys

from templates.edit_gui import Ui_Edit
from modules.search import Search


# -------------------Edit Window
class Edit(QDialog):
    def __init__(self,   *args, **argvs) :
        super(Edit, self).__init__(*args, **argvs)
        self.ui  = Ui_Edit()
        self.ui.setupUi(self)      
        self.ui.btn_Search.clicked.connect(self.searchQuery)                      
        self.ui.btn_editar.clicked.connect(self.updateQuery)
        self.ui.btn_voltar.clicked.connect(self.voltar)
       
        

    def updateQuery(self):  

        id_user = self.ui.input_id1.text()       
        password_user = self.ui.input_senha1.text()       
        status_user = self.ui.input_status.text()

        try:
            self.conn = sqlite3.connect("./Interface PC/db/academy.db")            
            self.c = self.conn.cursor()                  
            self.c.execute("UPDATE User SET id = {}, password = {}, status = {} WHERE id  = {}".format(int(id_user), int(password_user), status_user, int(id_user) ))                             
            self.conn.commit()

            QMessageBox.information(QMessageBox(),"Successful", "Data Update successfully ")


            self.c.close()
            self.conn.close()
        except Exception:
                QMessageBox.warning(QMessageBox(), 'Error', 'Could not update user to the database.')
    
    def searchQuery(self):
        

        
        try:        
                    
            #Loading Data
            self.connection = sqlite3.connect("db/academy.db")    
            self.c = self.connection.cursor()        
                                   
            query = "SELECT * FROM User WHERE  id = " + self.ui.lineEdit.text()            
            resultQuery = self.c.execute(query)                      
            row = resultQuery.fetchone() 
            
            self.ui.input_id1.setText(str(row[0]))
            self.ui.input_senha1.setText(str(row[1]))
            self.ui.input_status.setText(str(row[2]))

            self.connection.commit() 
            self.c.close()           
            self.connection.close()
                      
            
            

        except Exception:
            QMessageBox.warning(QMessageBox(), 'Error', 'Could not Find User from the database.')
                     
         
    """
    def mountUser(sef, userResult):
        userId  = str(userResult[0])
        userPassword = str(userResult [1])
        userStatus = userResult [2]
    
        #slice(start,stop)
        id1 = slice(0,len(userId)//2)
        id2 = slice(len(userId)//2, len(userId))
        
        passw1 = slice(0,len(userPassword)//4)
        passw2 = slice(1,len(userPassword)//2)
        passw3 = slice(2,(len(userPassword) -1 )//1)
        passw4 = slice(len(userPassword)-1, len(userPassword))
        
        print(userPassword[passw1]," +", userPassword[passw2], "+", userPassword[passw3], "+", userPassword[passw4])
        
        

        return userId[id1], userId[id2], userPassword[passw1],userPassword[passw2], userPassword[passw3], userPassword[passw4], userStatus
        
    """
    def voltar(self):
        pass    