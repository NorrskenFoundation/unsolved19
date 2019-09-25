# norrskenunsolved19

## Intro

Shipments of raw materials are tracked from mine, to harbor, to refinery, and finally to factory. Transport modes and distances between locations (nodes) are used to calculate CO2 impact. A machine learning model (stacked autoencoder with multi modality) uses features from the transport transactions to determine whether observed anomalies have occurred. These are flagged as suspicious and require further investigation.

Model runs in python notebook but backend server is ~currently broken~ working after we found a bug in the current version of Tensorflow and upgraded to the beta release.

## Transaction details

The data contains information about shipments of raw material originating from a mine which could potentially produce conflict minerals. From the mine the shipment continues to a harbor, then a refinery, and finally arrives at the factory. Depending on carrier, transport mode, distance, order of transport node, different timestamps and durations are expected. A model is trained with normal data and subsequently used to find anomalies when exposed to new shipments.

## Data

`transactions_id.csv` used to train model with good shipments

`transactions_id_flipped.csv` contains shipments where transports have unexptected order

`transactions_bad.csv` contains shipments with unexpectedly slow transports

## Train and use the model

0. Run the notebook `pip install jupyter && jupyter notebook anomalydetector.ipynb` and run all cells to train the model
1. Run `python server.py`
2. Run `python client.py`

(Tip: you can also just open up: https://github.com/northvolt/norrskenunsolved19/blob/master/anomalydetector.ipynb and look at the results from the Notebook)

## Use Neo4j to graph

0. `cd api`
1. `make tf`
2. `make neo4j`
1. `make init`
2. `make run`

# Team members
Marcus Ulmefors<br>
Martin Hwasser<br>
Anthony Clerc<br>
Landon Mossburg<br>