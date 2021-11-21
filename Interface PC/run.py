import sys 
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QToolTip

class Windows (QMainWindow):
    def __init__(self):
        super().__init__()

        self.topo = 100
        self.esquerda = 100
        self.largura = 1000
        self.altura = 800
        self.titulo = "Eletronic Lock System"

        botao1 = QPushButton("Conectar", self)
        botao1.move()
        self.CarregarJanela()

    def CarregarJanela(self):
        self.setGeometry(self.esquerda, self.topo, self.largura, self.altura)
        self.setWindowTitle(self.titulo)
        self.show()
    
aplicacao = QApplication(sys.argv)
window = Windows()
sys.exit(aplicacao.exec_())
