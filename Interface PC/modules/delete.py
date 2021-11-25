import sqlite3
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys

from templates.delete_gui import Ui_Delete
from modules.search import Search


# -------------------Delete Window
class Delete(QDialog):
    def __init__(self,   *args, **argvs) :
        super(Delete, self).__init__(*args, **argvs)
        self.ui  = Ui_Delete()
        self.ui.setupUi(self)
        self.ui.btn_deletar.clicked.connect(self.queryDelete)

    def queryDelete(self):
        try:      
            
            self.connection = sqlite3.connect("./Interface PC/db/academy.db")             
            self.c = self.connection.cursor()   
                                      
            query = "DELETE from User WHERE  id = " + self.ui.input_id.text()   
                      
            resultQuery = self.c.execute(query)             
            self.connection.commit() 
            QMessageBox.information(QMessageBox(),'Successful','Deleted User {} From Table Successful'.format(self.ui.input_id.text()))
            self.c.close()           
            self.connection.close()
            self.close()
            
            return resultQuery
        except Exception:
            QMessageBox.warning(QMessageBox(), 'Error', 'Could not Delete student from the database.')  