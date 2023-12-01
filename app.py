from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/me")
def me_api():
    return {
        "username": "hello",
        "theme": "dark",
        "image": "img",
    }