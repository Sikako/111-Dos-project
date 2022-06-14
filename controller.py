from PyQt5 import QtWidgets, QtGui, QtCore
from ui import Ui_MainWindow

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.comboBox.addItems(['1','2','3','4','5','6','7','8','9','10'])
        self.setup_control()
        
    def setup_control(self):
        self.ui.changelabel.setText('123')
        self.ui.pushButton.clicked.connect(self.buttonClicked)
    
    def buttonClicked(self):
    	cmd = "cmd = "
    	attacktype = ""
    	target = " target:" + self.ui.lineEdit.text()
    	port = " port:" + self.ui.lineEdit_2.text()
    	host = " host: " + self.ui.comboBox.currentText()
    	if self.ui.checkBox.isChecked():
    		attacktype += "TCP" 
    	if self.ui.checkBox_2.isChecked():
    		attacktype += "UDP"
    	if self.ui.checkBox_3.isChecked():
    		attacktype += "ACK"
    	if self.ui.checkBox_4.isChecked():
    		attacktype += "SMURF"
    	cmd = cmd + target + port + host + attacktype
    	self.ui.changelabel.setText(cmd)
       
if __name__ == '__main__' :
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window =MainWindow()
    window.show()
    sys.exit(app.exec_())
