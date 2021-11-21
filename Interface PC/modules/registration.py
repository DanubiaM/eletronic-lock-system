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
