from flask import Flask
from flask import render_template,request
import json
import mysql.connector

app = Flask(__name__)

# Web dashboard
@app.route("/")
def hello_world():
    #if request.method == "POST":
        #username = request.form['student_id']
        #print("Hello")
    return render_template("index.html") # open file index.html 

# REST API

# API for control esp8266
# url/data_request
@app.route('/data_request', methods=['GET'])
def data_request():
    if request.method == "GET":
        mydb = mysql.connector.connect(
          host="localhost",
          user="root",
          password="12345678",
          database="FIC"
        )
        mycursor = mydb.cursor()
        sql = "SELECT status.id,status.pump,status.fan,parameter.pump_max_temp,parameter.pump_min_temp,parameter.pump_max_humi,parameter.fan_min_temp,parameter.fan_min_humi FROM status INNER JOIN parameter ON status.id = parameter.id"
        mycursor.execute(sql)
        myresult = mycursor.fetchall()
        return myresult,200
    else:
        return {"status" : "404 err"},404




# API for esp8266 send data to server
# url/data_upload
@app.route('/data_upload', methods=['POST'])
def data_upload():
    if request.method == "POST":
        data = json.loads(request.data)

        #extract data
        temperature = float(data["temperature"])
        humidity = float(data["humidity"])
        soil_humidity = float(data["soil_humidity"])
        
        #data base connect
        mydb = mysql.connector.connect(
          host="localhost",
          user="root",
          password="12345678",
          database="FIC"
        )
        mycursor = mydb.cursor()
        #sql
        sql = "INSERT INTO Sensor_data (Temperature,Humidity,Soil_humidity) VALUES (%s, %s, %s)"
        val = (f"{temperature}",f"{humidity}",f"{soil_humidity}")
        mycursor.execute(sql, val)
        #fetch
        mydb.commit()
        #debug sql
        print(mycursor.rowcount, "record inserted.")

        #debug
        # print("------------------------------------------")
        # print(f"temperature = {temperature}")
        # print(f"humidity = {humidity}")
        # print(f"soil_humidity = {soil_humidity}")
        # print("------------------------------------------")
        #debug
        return {"status" : "200 ok"},200
    else:
        return {"status" : "404 err"},404
# if __name__ == '__main__':
#     # run app in debug mode on port 5000
#     app.run(debug=True, port=5000, host='0.0.0.0')
