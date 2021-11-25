from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys
import sqlite3

from templates.main_gui import Ui_Main
from modules.registration import Cadastrar
from modules.search import Search
from modules.searchResult import SearchResult
from modules.edit import Edit
from modules.delete import Delete



# -------------------Main Window
class MainWindow(QMainWindow):
    def __init__(self, *args, **argvs):
        super(MainWindow, self).__init__(*args, **argvs)
        self.ui = Ui_Main()
        self.ui.setupUi(self)
        self.loadData()
        self.ui.actionCadastrar.triggered.connect(self.registration)
        self.ui.actionEditar.triggered.connect(self.edit)
        self.ui.actionPesquisar.triggered.connect(self.search)
        self.ui.actionExcluir.triggered.connect(self.delete)
        self.ui.actionAtualizar.triggered.connect(self.loadData)
    #InputDataList
    def inputData(self):
        return self.ui.table_list.currentRow()

    #Registration
    def registration(self):
        addWindow = Cadastrar()
        addWindow.exec_()
        #MainWindow.hide(self) hidden Cadastrar window

    #Edit
    def edit(self):     
        #valorId = self.ui.table_list.item(self.inputData(), 0)         
        editWindow = Edit()
        editWindow.exec_()   
        
    #Search
    def search(self):
        searchWindow = Search()
        searchWindow.exec_()    

        
    #Delete
    def delete(self):
        deleteWindow = Delete()             
        deleteWindow.exec_()       
        
    def loadData(self):
        try:
                       
            #Loading Data
            self.connection = sqlite3.connect("./Interface PC/db/academy.db")                       
            self.c = self.connection.cursor()                             
            query = "SELECT * FROM User" 
            result = self.c.execute(query) 
            self.connection.commit()         
            
               
            self.ui.table_list.setRowCount(0)
            for row_number, row_data in enumerate(result):
                self.ui.table_list.insertRow(row_number)
                for column_number, data in enumerate(row_data):
                    self.ui.table_list.setItem(row_number, column_number,QTableWidgetItem(str(data)))
            
            self.c.close()
            self.connection.close()
        except sqlite3.OperationalError:            
            #os.mkdir('db')
            QMessageBox.warning(QMessageBox(), 'Error', 'Could not add user to the database.')
            
        #finally:
            #self.connection = sqlite3.connect("db/academy.db")
            #self.connection = sqlite3.connect("academy.db")
           
        #    QMessageBox.warning(QMessageBox(), 'Error', 'Could not add user to the database.')
    

