from flask import Flask, render_template, jsonify, request
import requests

app = Flask(__name__)

API_KEY = 'AIzaSyBay2ZVAM82x4K6uxhqvKXiij_eFDmrB9c'

@app.route('/')
def index():
    return render_template('index_weather.html')

@app.route('/weather')
def weather():
    location = request.args.get('location', 'finland')
    WEATHER_API_URL = f'https://api.maptiler.com/weather/latest.json?key={API_KEY}'

    response = requests.get(WEATHER_API_URL)
    data = response.json()

    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True)
