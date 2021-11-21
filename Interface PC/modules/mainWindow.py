from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys

from templates.main_gui import Ui_Main
from modules.registration import Cadastrar
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
