from flask import Flask, request, send_from_directory, make_response, redirect, Response, jsonify
from flask_cors import CORS
import boto3
from load_data import load_data
import simplejson
import datetime



import numpy as np
import pandas as pd
from s3fs.core import S3FileSystem


app = Flask(__name__)
CORS(app, origins='*')

bucket_name = 'greenlytics-public'
s3fs = S3FileSystem()
s3boto = boto3.resource('s3')
my_bucket = s3boto.Bucket(bucket_name)


def read_grid():
    keys = []

    for object_summary in my_bucket.objects.filter(Prefix="norrsken/ewd"):
       keys.append(object_summary.key)

    data = []
    for key in keys:
       array = np.load(s3fs.open('greenlytics-public/{}'.format(key)))
       data.append(array)




def test_read(timestamp):
    file = 'greenlytics-public/norrsken/ewd/201909/'+timestamp+'.npy'
    array = np.load(s3fs.open(file))

    summed = [[sum(arr1) for arr1 in arr2] for arr2 in array.tolist()]
    return summed

#def read_grid_for_range(time_start, time_end):



@app.route('/api/get_data', methods=['GET'])
def get_data():
    timestamp = request.args.get('timestamp') # required

    array = test_read(timestamp)
    return make_response(jsonify({'timestamps': ['2019-06-09T07:47Z'], 'grids': [array]}), 200)



@app.route('/api/get_smhi', methods=['GET'])
def get_smhi():

    d_start = datetime.datetime(2019, 9, 8, 12, 0)
    d_end = datetime.datetime(2019, 9, 9, 12, 0)
    data = load_data()
    data = data['Tullinge A']
    mask = (data.index.get_level_values('date') > d_start) & (data.index.get_level_values('date') <= d_end)
    data = data.loc[mask]
    dates = [str(d) for d in data.index.get_level_values('date').tolist()]
    return make_response(simplejson.dumps({'timestamps': dates, 'values': data['value'].tolist()}, ignore_nan=True), 200)





if __name__ == '__main__':
    app.run(debug=True)
