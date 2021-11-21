import sys
from PyQt5.QtWidgets import QApplication, QDialog
from modules.login import Login

aplicacao = QApplication(sys.argv)
app = QApplication(sys.argv)
if (QDialog.Accepted == True):
    window = Login()
    window.show()
sys.exit(app.exec_())
