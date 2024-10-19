from flask import Flask, render_template, jsonify
import requests

app = Flask(__name__)

API_KEY = 'AIzaSyBay2ZVAM82x4K6uxhqvKXiij_eFDmrB9c'  

@app.route('/')
def index():
    return render_template('index_geolocation.html')

@app.route('/geolocation')
def geolocation():
    GEOLOCATION_API_URL = f'https://maps.googleapis.com/maps/api/js?key=AIzaSyAPQe3KmBmzYmlIK4qpU7i83wvuHwN3oVQ&callback=initMap{API_KEY}'

    try:
        response = requests.get(GEOLOCATION_API_URL)

        # Check if the response is successful (status code 200)
        if response.status_code != 200:
            return jsonify({'error': f'API request failed with status code {response.status_code}'})
        
        data = response.json()

        # Return the geolocation data
        return jsonify(data)
    
    except requests.exceptions.RequestException as e:
        return jsonify({'error': f'Failed to connect to the API: {str(e)}'})
    except requests.exceptions.JSONDecodeError as e:
        return jsonify({'error': f'Failed to parse JSON: {str(e)}'})

if __name__ == '__main__':
    app.run(debug=True)
