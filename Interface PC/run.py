import sys
from PyQt5.QtWidgets import QApplication, QDialog
from modules.login import Login
from modules.mainWindow import MainWindow

aplicacao = QApplication(sys.argv)
app = QApplication(sys.argv)
if (QDialog.Accepted == True):
    window = Login()
    #window = MainWindow()
    window.show()
sys.exit(app.exec_())
