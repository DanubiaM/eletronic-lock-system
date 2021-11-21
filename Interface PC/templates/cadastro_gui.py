# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'cadastro_gui.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_cadastro(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(400, 300)
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(50, 20, 211, 21))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(50, 80, 55, 16))
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(50, 110, 55, 16))
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(Dialog)
        self.label_5.setGeometry(QtCore.QRect(50, 140, 55, 16))
        self.label_5.setObjectName("label_5")
        self.btn_cadastrar = QtWidgets.QPushButton(Dialog)
        self.btn_cadastrar.setGeometry(QtCore.QRect(160, 210, 93, 28))
        self.btn_cadastrar.setStyleSheet("background-color: rgb(104, 255, 39);")
        self.btn_cadastrar.setObjectName("btn_cadastrar")
        self.btn_voltar = QtWidgets.QPushButton(Dialog)
        self.btn_voltar.setGeometry(QtCore.QRect(52, 210, 101, 28))
        self.btn_voltar.setStyleSheet("background-color: rgb(255, 114, 101);")
        self.btn_voltar.setObjectName("btn_voltar")
        self.input_id1 = QtWidgets.QLineEdit(Dialog)
        self.input_id1.setGeometry(QtCore.QRect(110, 80, 21, 22))
        self.input_id1.setObjectName("input_id1")
        self.input_id2 = QtWidgets.QLineEdit(Dialog)
        self.input_id2.setGeometry(QtCore.QRect(140, 80, 21, 22))
        self.input_id2.setObjectName("input_id2")
        self.input_senha1 = QtWidgets.QLineEdit(Dialog)
        self.input_senha1.setGeometry(QtCore.QRect(110, 110, 21, 22))
        self.input_senha1.setText("")
        self.input_senha1.setObjectName("input_senha1")
        self.input_senha2 = QtWidgets.QLineEdit(Dialog)
        self.input_senha2.setGeometry(QtCore.QRect(140, 110, 21, 22))
        self.input_senha2.setObjectName("input_senha2")
        self.input_senha3 = QtWidgets.QLineEdit(Dialog)
        self.input_senha3.setGeometry(QtCore.QRect(170, 110, 21, 22))
        self.input_senha3.setObjectName("input_senha3")
        self.input_senha4 = QtWidgets.QLineEdit(Dialog)
        self.input_senha4.setGeometry(QtCore.QRect(200, 110, 21, 22))
        self.input_senha4.setObjectName("input_senha4")
        self.input_status = QtWidgets.QLineEdit(Dialog)
        self.input_status.setGeometry(QtCore.QRect(110, 140, 113, 21))
        self.input_status.setObjectName("input_status")
        self.label_6 = QtWidgets.QLabel(Dialog)
        self.label_6.setGeometry(QtCore.QRect(240, 50, 141, 121))
        self.label_6.setStyleSheet("image: url(:/add/cadastrar.png);")
        self.label_6.setText("")
        self.label_6.setObjectName("label_6")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(-16, -5, 421, 311))
        self.label.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.label.setText("")
        self.label.setObjectName("label")
        self.label.raise_()
        self.label_2.raise_()
        self.label_3.raise_()
        self.label_4.raise_()
        self.label_5.raise_()
        self.btn_cadastrar.raise_()
        self.btn_voltar.raise_()
        self.input_id1.raise_()
        self.input_id2.raise_()
        self.input_senha1.raise_()
        self.input_senha2.raise_()
        self.input_senha3.raise_()
        self.input_senha4.raise_()
        self.input_status.raise_()
        self.label_6.raise_()

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Realizar Cadastro"))
        self.label_2.setText(_translate("Dialog", "CADASTRO DE NOVOS USUARIOS"))
        self.label_3.setText(_translate("Dialog", "ID"))
        self.label_4.setText(_translate("Dialog", "Senha"))
        self.label_5.setText(_translate("Dialog", "Status"))
        self.btn_cadastrar.setText(_translate("Dialog", "Cadastrar"))
        self.btn_voltar.setText(_translate("Dialog", "Voltar"))
        self.input_id1.setPlaceholderText(_translate("Dialog", "0"))
        self.input_id2.setPlaceholderText(_translate("Dialog", "0"))
        self.input_senha1.setPlaceholderText(_translate("Dialog", "0"))
        self.input_senha2.setPlaceholderText(_translate("Dialog", "0"))
        self.input_senha3.setPlaceholderText(_translate("Dialog", "0"))
        self.input_senha4.setPlaceholderText(_translate("Dialog", "0"))
        self.input_status.setPlaceholderText(_translate("Dialog", " 1 - 2 - 3"))
import templates.cadastro


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_cadastro()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
