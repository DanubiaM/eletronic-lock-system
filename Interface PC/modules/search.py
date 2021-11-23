from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys
import sqlite3

from templates.search_gui import Ui_Search
from modules.searchResult import SearchResult
# -------------------Search Window
class Search(QDialog):
    def __init__(self, *args, **argvs):
        super(Search, self).__init__(*args, **argvs)
        self.ui = Ui_Search()
        self.ui.setupUi(self)        
        self.ui.pushButton.clicked.connect(self.searchWindow)
        
        

    def searchWindow(self):
        try:        
                    
            #Loading Data
            self.connection = sqlite3.connect("db/academy.db")    
            self.c = self.connection.cursor()                                 
            query = "SELECT * FROM User WHERE  id = " + self.ui.input_id.text()            
            resultQuery = self.c.execute(query)                      
            row = resultQuery.fetchone()                    
            serachresult = "Usuario encontrado!"+ "\n ID : "+str(row[0])+'\n'+"Status: "+str(row[2])+'\n'
            QMessageBox.information(QMessageBox(), 'Successful', serachresult)
            self.connection.commit() 
            self.c.close()           
            self.connection.close()
                       
            return row

        except Exception:
            QMessageBox.warning(QMessageBox(), 'Error', 'Could not Find User from the database.')
    """
    def mountUser(self ):        
        result = self.searchWindow(self.ui.input_id.text())
        return result

    def actionMenu(self, action):
        result = self.mountUser()
        #Search
        if action == 1:
            searchResult = SearchResult(result)
            searchResult.exec_()
            pass
        #Edit
        if action == 2:
            pass
        #Delete
        if action == 3:
            pass 
    """    