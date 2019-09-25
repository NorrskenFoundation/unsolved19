import requests

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

if __name__ == '__main__':
    url = 'http://localhost:5000/api'

    inv_nodes = {v: k for k, v in nodes.items()}
    skelleftea = inv_nodes[7]
    hamburg = inv_nodes[2]

    time = 6.2

    frm = hamburg
    to = skelleftea
    print('\nTravel from: ', frm, 'to: ', to, 'time: ', time)
    r = requests.post(url, json={'from': frm, 'to': to, 'time': time})
    print('Risk score for shipment:', r.json())

    time = 4.2
    frm = hamburg
    to = skelleftea
    print('\nTravel from: ', frm, 'to: ', to, 'time: ', time)
    r = requests.post(url, json={'from': frm, 'to': to, 'time': time})
    print('Risk score for shipment:', r.json())

    time = 3.2
    frm = skelleftea
    to = hamburg
    print('\nTravel from: ', frm, 'to: ', to, 'time: ', time)
    r = requests.post(url, json={'from': frm, 'to': to, 'time': time})
    print('Risk score for shipment: ', r.json())

    time = 18.2
    frm = inv_nodes[9]
    to = hamburg
    print('\nTravel from: ', frm, 'to: ', to, 'time: ', time)
    r = requests.post(url, json={'from': frm, 'to': to, 'time': time})
    print('Risk score for shipment: ', r.json())

    time = 7.2
    frm = inv_nodes[10]
    to = hamburg
    print('\nTravel from: ', frm, 'to: ', to, 'time: ', time)
    r = requests.post(url, json={'from': frm, 'to': to, 'time': time})
    print('Risk score for shipment: ', r.json())
