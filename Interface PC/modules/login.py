from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys
import sqlite3
import glob
import serial

from templates.login_gui import Ui_LoginAcademy
from modules.mainWindow import MainWindow

# -------------------Login Window
class Login(QDialog):
    def __init__(self, *args, **argvs):
        super(Login, self).__init__(*args, **argvs)
        self.ui = Ui_LoginAcademy()
        self.ui.setupUi(self)
        self.ui.btnEnviar.setEnabled(False)
        self.ui.btnReceber.setEnabled(False)
        self.ui.btnLogin.clicked.connect(self.login)       
        self.ui.comboBox_COMS.addItems(self.loadPort())
        self.ui.btnConectar.clicked.connect(self.testCommunication)
        self.ui.btnEnviar.clicked.connect(self.sendData)
    
    #Realizar login
    def login(self):
        #admin = "01"
        #senha = "1234"
            user  = self.ui.input_id1.text()
            user  += self.ui.input_id2.text()
            password = self.ui.input_senha1.text()
            password += self.ui.input_senha2.text()
            password += self.ui.input_senha3.text()
            password += self.ui.input_senha4.text()

        #if admin == user and senha == password:
        #    QMessageBox.information(QMessageBox(),"Sucessful Login", "Login realizado com sucesso! Bem Vindo!")
        #    self.window = MainWindow()
        #    self.window.show()
        #else:
        #    QMessageBox.information(QMessageBox(),"Unsucessful Login", "Erro: Verifique sua senha ou ID")
        
       # try:        
                    
            #Loading Data
            self.connection = sqlite3.connect("./Interface PC/db/academy.db")    
            self.c = self.connection.cursor()                                 
            query = "SELECT * FROM User WHERE  id = {} and password = {}".format(int(user), int(password))             
            resultQuery = self.c.execute(query)                      
            row = resultQuery.fetchone()
            
            if (row[2] == 3):
                self.window = MainWindow()
                self.window.show()
            elif ([row[2] == 0]):
                QMessageBox.warning(QMessageBox(), 'Error', 'Acesso não liberado!\n Por favor, verique sua mensalidade.')
            else:
                QMessageBox.information(QMessageBox(), 'Successful', "Acesso liberado.\n Bem-vindo! ")    
                #ENVIA DADO PARA LIBERAR ACESSO              
           
            self.connection.commit() 
            self.c.close()           
            self.connection.close()
                       
            

       # except Exception:
        #    QMessageBox.warning(QMessageBox(), 'Error', 'Usuário não encontrado.')

    def loadPort(self):        
        """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
        """
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
            
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
            
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')            
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        
        return result
    
    def testCommunication(self):
        try:
            #print(self.ui.comboBox_COMS.currentText())
            serial.Serial('{}'.format(self.ui.comboBox_COMS.currentText()),9600)
            self.ui.btnReceber.setEnabled(True)
            self.ui.btnEnviar.setEnabled(True)
            self.ui.comboBox_COMS.setEnabled(False)
            self.ui.btnConectar.setText("Desconectar")
        except:
            QMessageBox.warning(QMessageBox(), 'Error', 'Conexão não estabelecida')

    def sendData(self):
        #try:
            ser = serial.Serial('{}'.format(self.ui.comboBox_COMS.currentText()), baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)          
            #Loading Data
            self.connection = sqlite3.connect("./Interface PC/db/academy.db")                       
            self.c = self.connection.cursor()                             
            query = "SELECT * FROM User" 
            resultQuery = self.c.execute(query) 
                    
            #Data: IFMTID;SENHA;STATUS;# Example: IFMT;01;0545;3;#
            user=""
            print(enumerate(resultQuery))
            for i in resultQuery: 
                user+="IFMT"               
                for data in i:                  
                  user += str(data)
                  user+=";"
                user = user[:-1]
                user+="#"
            
            print(user)
            ser.write(user.encode())
            self.c.close()
            self.connection.close()
        #except sqlite3.OperationalError:            
            #os.mkdir('db')
        #    QMessageBox.warning(QMessageBox(), 'Error', 'Could not add user to the database.')