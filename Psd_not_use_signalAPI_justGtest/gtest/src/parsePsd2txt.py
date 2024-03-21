import can
import cantools
import time


db = cantools.db.load_file('MLBevo_Gen2_MLBevo_ICAN_KMatrix_V8.19.00F_20191108_AM.dbc')   #dbc对象
filename = "PSD_A8L_20230829_NO.3-直线-城市道路-无隔离带_Logging_L001.blf"
blf = can.BLFReader(filename)      #blf对象


with open('parsed_data.txt', 'w') as txt_file:
    for msg in blf:
        if msg.arbitration_id  in [1122, 1123, 1124, 879, 884]:
            ID = msg.arbitration_id                        #message id
            time_stamp = msg.timestamp          #blf包中保存的报文时间戳
            can_data = msg.data                             #blf包中保存的数据，直接打印是加密的数字字符码
            dict_data = db.decode_message(msg.arbitration_id, msg.data , allow_truncated=True)    #对数据进行解码,这里关键allow_truncated设置可以在数据缺少的情况下继续解析下一部分
            length = msg.dlc                                      #blf包中保存的报文长度，如8,64    
            data = (ID, dict_data)
            txt_file.write(f'{ID}: {dict_data}\n')   #f-string格式化字符串字面量,f: 格式化字符串的关键字, 字符串前加f, 可插入变量到字符串中, {ID}: 将变量ID的值写到文件中, {dict_data}: 将dict_data的值写到文件中, \n: 每写一次换行一下
            