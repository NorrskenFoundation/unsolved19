# go to http://localhost:7474 and log in
# run this first

:params props: [
    {"name": "Qu\u00e9bec, Quebec, Canada", "lat": 46.81228, "lon": -71.21454, "type": "mine"},
    {"name": "Kolwezi, Lualaba, Democratic Republic of the Congo", "lat": -10.71484, "lon": 25.46674, "type": "mine"},
    {"name": "Shinkolobwe, Haut-Katanga, Democratic Republic of the Congo", "lat": -11.05248, "lon": 26.54665, "type": "mine"},
    {"name": "Rotterdam, South Holland, Netherlands", "lat": 51.9225, "lon": 4.47917, "type": "harbor"},
    {"name": "Casablanca, Casablanca-Settat, Morocco", "lat": 33.58831, "lon": -7.61138, "type": "harbor"},
    {"name": "Bilbao, Basque Country, Spain", "lat": 43.26271, "lon": -2.92528, "type": "harbor"},
    {"name": "Hamburg, Hamburg, Germany", "lat": 53.57532, "lon": 10.01534, "type": "refinery"},
    {"name": "Turku, Finland Proper, Finland", "lat": 60.45148, "lon": 22.26869, "type": "refinery"},
    {"name": "Lysekil, V\u00e4stra G\u00f6taland, Sweden", "lat": 58.27429, "lon": 11.43576, "type": "refinery"},
    {"name": "Skellefte\u00e5 Airport, V\u00e4sterbotten, Sweden", "lat": 64.62477, "lon": 21.07689, "type": "factory"}
]

# then run this

UNWIND $props AS map
CREATE (n)
SET n = map