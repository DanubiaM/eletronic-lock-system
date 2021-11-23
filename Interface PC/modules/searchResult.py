from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtCore import pyqtSlot
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
import os, sys
import sqlite3

from templates.search_gui import Ui_Search
from templates.searchResult_gui  import Ui_SearchResult

# -------------------Search Result Window
class SearchResult(QDialog):
    def __init__(self,result, *args, **argvs):
        super(SearchResult, self).__init__(*args, **argvs)
        self.ui = Ui_SearchResult()        
        self.ui.setupUi(self)
        print(result)
        #self.ui.output_id.text(result[0])


    def setInput(self, result):
        for i in result:
            print(i)