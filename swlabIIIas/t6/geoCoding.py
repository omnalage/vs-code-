from flask import Flask, render_template, jsonify
import requests

app = Flask(__name__)

# Your MapTiler API key
API_KEY = 'AIzaSyBay2ZVAM82x4K6uxhqvKXiij_eFDmrB9c'

@app.route('/')
def index():
    return render_template('index_geocoding.html')

@app.route('/geocode')
def geocode():
    # Address to geocode
    address = 'Mumbai, India'
    # Geocoding API URL
    GEOCODE_API_URL = f'https://maps.googleapis.com/maps/api/js?key=AIzaSyAPQe3KmBmzYmlIK4qpU7i83wvuHwN3oVQ&callback=initMap{API_KEY}'

    # Make the request
    response = requests.get(GEOCODE_API_URL)
    data = response.json()

    if data['features']:
        # Get place name and coordinates
        place_name = data['features'][0]['place_name']
        lon, lat = data['features'][0]['geometry']['coordinates']
        return jsonify({'place_name': place_name, 'longitude': lon, 'latitude': lat})
    else:
        return jsonify({'error': 'Address not found'})

if __name__ == '__main__':
    app.run(debug=True)
