# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main_gui.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Main(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(540, 401)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tableWidget = QtWidgets.QTableWidget(self.centralwidget)
        self.tableWidget.setGeometry(QtCore.QRect(-330, 220, 256, 192))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)
        self.table_list = QtWidgets.QTableWidget(self.centralwidget)
        self.table_list.setGeometry(QtCore.QRect(220, 50, 251, 291))
        self.table_list.setObjectName("table_list")
        self.table_list.setColumnCount(2)
        self.table_list.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.table_list.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.table_list.setHorizontalHeaderItem(1, item)
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(220, 20, 251, 21))
        self.label_2.setStyleSheet("color: rgb(0, 0, 0);\n"
"font: 12pt \"MS Shell Dlg 2\";\n"
"")
        self.label_2.setObjectName("label_2")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(-110, 180, 431, 161))
        self.label.setStyleSheet("image: url(:/main/main.png);")
        self.label.setText("")
        self.label.setObjectName("label")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(0, 0, 541, 371))
        self.label_3.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.label_3.setText("")
        self.label_3.setObjectName("label_3")
        self.label_3.raise_()
        self.tableWidget.raise_()
        self.table_list.raise_()
        self.label_2.raise_()
        self.label.raise_()
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setStyleSheet("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 63 10pt \"Bahnschrift SemiBold\";")
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.actionCadastrar = QtWidgets.QAction(MainWindow)
        self.actionCadastrar.setObjectName("actionCadastrar")
        self.actionEditar = QtWidgets.QAction(MainWindow)
        self.actionEditar.setObjectName("actionEditar")
        self.actionProcurar = QtWidgets.QAction(MainWindow)
        self.actionProcurar.setObjectName("actionProcurar")
        self.actionExcluir = QtWidgets.QAction(MainWindow)
        self.actionExcluir.setObjectName("actionExcluir")
        self.toolBar.addAction(self.actionCadastrar)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionEditar)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionProcurar)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionExcluir)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Principal"))
        item = self.table_list.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "Id"))
        item = self.table_list.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "Status"))
        self.label_2.setText(_translate("MainWindow", "USUARIOS CADASTRADOS"))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar"))
        self.actionCadastrar.setText(_translate("MainWindow", "Cadastrar"))
        self.actionEditar.setText(_translate("MainWindow", "Editar"))
        self.actionProcurar.setText(_translate("MainWindow", "Procurar"))
        self.actionExcluir.setText(_translate("MainWindow", "Excluir"))
import main


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_Main()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())