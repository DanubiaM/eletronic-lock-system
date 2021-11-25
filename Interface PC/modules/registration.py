import sqlite3
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys

from templates.cadastro_gui import Ui_cadastro

# -------------------Registration Window
class Cadastrar(QDialog):
    def __init__(self,  *args, **argvs) :
        super(Cadastrar, self).__init__(*args, **argvs)
        self.ui  = Ui_cadastro()
        self.ui.setupUi(self)
        self.ui.btn_cadastrar.clicked.connect(self.addQuery)
        self.ui.btn_voltar.clicked.connect(self.voltar)
        

    def addQuery(self):   

        id_user = self.ui.input_id1.text()       
        id_user += self.ui.input_id2.text()

        password_user = self.ui.input_senha1.text()
        password_user += self.ui.input_senha2.text()
        password_user += self.ui.input_senha3.text()
        password_user += self.ui.input_senha4.text()

        status_user = self.ui.input_status.text()

        #Maximum value is 99        
        if any([int(self.ui.input_id1.text()) > 99, int(self.ui.input_id2.text()) > 99, int(self.ui.input_senha1.text()) > 99, int(self.ui.input_senha2.text()) > 99 , int(self.ui.input_senha3.text()) >99, int(self.ui.input_senha4.text()) > 99])  : 
            QMessageBox.warning(QMessageBox(), 'Error', 'Cada campo deve ter o valor máximo de 99 .')
            
        

        try:
            self.conn = sqlite3.connect("./Interface PC/db/academy.db")  
            self.c = self.conn.cursor()                                      

            if id_user == "" or password_user == "" or status_user == "":               
                QMessageBox.information(QMessageBox(),"Unsuccess", "Please, check the data entries! ")
            else:       
            
                self.c.execute("INSERT INTO User (id, password, status) VALUES ('{}','{}','{}')".format(int(id_user), int(password_user), int(status_user) ))
                QMessageBox.information(QMessageBox(),"Successful", "Data registered successfully ")

            self.conn.commit()
            self.c.close()
            self.conn.close()
        except Exception:
                QMessageBox.warning(QMessageBox(), 'Error', 'Could not add user to the database.')
    
        
    def voltar(self):
        self.close()    