import requests
import pandas as pd
import json


def load_data():

    stations = [{'name': 'Adelsö A' , 'id': 97280}, {'name': 'Tullinge A' , 'id': 97100}]
    df = pd.DataFrame()
    for station in stations:
        station_url = "https://opendata-download-metobs.smhi.se/api/version/latest/parameter/14/station/{0}/period/latest-months/data.json".format(station['id'])
        r = requests.get(url = station_url)
        data = r.json()
        station_df = pd.DataFrame(data['value'])
        station_df['date'] = pd.to_datetime(station_df['date'], unit='ms')
        station_df = station_df.set_index('date')
        station_df.index = pd.to_datetime(station_df.index)
        station_df.columns = pd.MultiIndex.from_product([[station['name']], station_df.columns], names=['station', 'data'])
        df = pd.concat([df,station_df], axis=1)

    print(df)
    df.to_csv('smhi.csv')
    return df
