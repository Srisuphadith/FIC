from flask import Flask
from flask import render_template,request
import json
app = Flask(__name__)

#web dashboard
@app.route("/" ,methods=["GET", "POST"])
def hello_world():
    if request.method == "POST":
        #username = request.form['student_id']
        print("Hello")
    return render_template("index.html") # open file index.html 

#REST API

#API for control esp8266
@app.route('/data_request', methods=['GET'])
def data_request():
    if request.method == "GET":
         return {"sw_status" : 0,},200
    else:
        return {"status" : "404 err"},404

#API for esp8266 send data to server
@app.route('/data_upload', methods=['POST'])
def data_upload():
    if request.method == "POST":
        data = json.loads(request.data)
        print(data)
        return data,200
    else:
        return {"status" : "404 err"},404