import numpy as np
from flask import Flask, request, jsonify
import pickle
from tensorflow.keras.models import load_model
import pandas as pd

from sklearn.preprocessing import StandardScaler, MinMaxScaler

import tensorflow as tf

#from tensorflow.keras.models import *
#from tensorflow.keras.layers import *
#from tensorflow.keras import backend as K



app = Flask(__name__)
autoencoder = load_model('model.h5')

with open('scaler.pkl', 'rb') as f:
    scaler = pickle.load(f)

nodes = {'Bilbao, Basque Country, Spain': 1,
 'Casablanca, Casablanca-Settat, Morocco': 3,
 'Hamburg, Hamburg, Germany': 2,
 'Kolwezi, Lualaba, Democratic Republic of the Congo': 4,
 'Lysekil, Västra Götaland, Sweden': 10,
 'Québec, Quebec, Canada': 8,
 'Rotterdam, South Holland, Netherlands': 6,
 'Shinkolobwe, Haut-Katanga, Democratic Republic of the Congo': 9,
 'Skellefteå Airport, Västerbotten, Sweden': 7,
 'Turku, Finland Proper, Finland': 5,
 'Turku, Southwest Finland, Finland': 0}

@app.route('/api',methods=['POST'])
def predict():
    # Get the data from the POST request.
    data = request.get_json(force=True)    # Make prediction using model loaded from disk as per the data.
    frm = data['from']
    frm = nodes[frm]
    frm = np.eye(11)[frm]
    to = data['to']
    to = nodes[to]
    to = np.eye(11)[to]
    t = np.array([data['time']])
    t = scaler.transform(t.reshape(1, -1))

    print('from: ', frm)
    print('to: ', to)
    print('time: ', t)
    data = [[frm], [to], t]
    print('data is: ', data)
    score = autoencoder.evaluate(data, data)
    output = score[0]
    return jsonify(output)


if __name__ == '__main__':
    app.run(port=5000, debug=True)
