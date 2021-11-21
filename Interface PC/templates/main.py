from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys

from main_gui import Ui_Main
from login_gui import Ui_LoginAcademy
from cadastro_gui import Ui_cadastro


# -------------------Registration Window
class Cadastrar(QDialog):
    def __init__(self,  *args, **argvs) :
        super(Cadastrar, self).__init__(*args, **argvs)
        self.ui  = Ui_cadastro()
        self.ui.setupUi(self)

# -------------------Main Window
class MainWindow(QMainWindow):
    def __init__(self, *args, **argvs):
        super(MainWindow, self).__init__(*args, **argvs)
        self.ui = Ui_Main()
        self.ui.setupUi(self)
        self.ui.actionCadastrar.triggered.connect(self.registration)

    #Registration
    def registration(self):
        addUser = Cadastrar()
        addUser.exec_()
        #MainWindow.hide(self) hidden Cadastrar window


# -------------------Login Window
class Login(QDialog):
    def __init__(self, *args, **argvs):
        super(Login, self).__init__(*args, **argvs)
        self.ui = Ui_LoginAcademy()
        self.ui.setupUi(self)
        self.ui.btnLogin.clicked.connect(self.login)
    
    #Realizar login
    def login(self):
        admin = "01"
        senha = "1234"
        user  = self.ui.input_id1.text()
        user  += self.ui.input_id2.text()
        password = self.ui.input_senha1.text()
        password += self.ui.input_senha2.text()
        password += self.ui.input_senha3.text()
        password += self.ui.input_senha4.text()

        if admin == user and senha == password:
            QMessageBox.information(QMessageBox(),"Sucessful Login", "Login realizado com sucesso! Bem Vindo!")
            self.window = MainWindow()
            self.window.show()
        else:
            QMessageBox.information(QMessageBox(),"Unsucessful Login", "Erro: Verifique sua senha ou ID")




# -------------------Execute application
app = QApplication(sys.argv)
if (QDialog.Accepted == True):
    window = Login()
    window.show()
sys.exit(app.exec_())
