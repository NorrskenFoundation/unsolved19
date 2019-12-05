//
//  LocationSpot.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-16.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit
import CoreLocation

class LocationSpot:SCNNode {
    var mat:SCNMaterial!
    var pos:CLLocation! //59.3293, longitude: 18.0686)
    var locationManager:CLLocationManager!
    var stringLabel:String="Unnamed"
    override init() {
        super.init()
        
        self.create()
        
        
    }
    
    func create() {
        self.locationManager = CLLocationManager()
        
        self.geometry = SCNSphere(radius: 0.0002)
        //-- Material handle
        self.mat = self.geometry?.firstMaterial
        
        //-- Material config
        self.mat.lightingModel = .constant
        
        self.mat.diffuse.contents = UIColor.red
        self.mat.emission.contents = UIColor.red

        //pos.coordinate.latitude
        self.setPos(lat: 0, lon: 0)
        
    }
    
    init(lat:CLLocationDegrees, lon: CLLocationDegrees, label:String) {
        super.init()
        self.stringLabel = label
        self.create()
        self.setPos(lat: lat, lon: lon)
        
        let labl = LocationLabel(self.stringLabel, par:self)
        self.addChildNode(labl)
    }
    
    init(place:LocSpot) {
        super.init()
        self.stringLabel = place.label
        self.create()
        
        let arr = place.coord.components(separatedBy: ",") //split(separator: ",")
        let latt:CLLocationDegrees = (arr[0] as NSString).doubleValue
        let long:CLLocationDegrees = (arr[1] as NSString).doubleValue
        self.setPos(lat: latt, lon: long)
        
        let labl = LocationLabel(self.stringLabel, par:self)
        self.addChildNode(labl)
    }
    
    
    func setPos(lat:CLLocationDegrees, lon: CLLocationDegrees) {
        self.pos = CLLocation(latitude:lat, longitude:lon)
        self.calcPosFromLatLonRad()
    }
    
    
    //func calcPosFromLatLonRad(lat:Double,lon:Double,radius:Double)->SCNVector3 {
    func calcPosFromLatLonRad(_ radius:Double=0.1) {
        let coord = self.pos.coordinate
        
        let phi   = (90.0 - coord.latitude) * (Double.pi/180)
        let theta = (coord.longitude + 90.0) * (Double.pi/180)

        let x = -((radius) * sin(phi) * cos(theta))
        let z = ((radius) * sin(phi) * sin(theta))
        let y = ((radius) * cos(phi))

        self.position = SCNVector3(x: Float(x), y: Float(y), z: Float(z)) //lat: 59.3293, lon: 18.0686, radius: 0.1)
        
        
        
        
        /*
        self.lookUpLocation { (place) in
            if let p = place {
                if((p.locality != nil) && (p.country != nil)) {
                    let cp = ("\(p.locality!), \(p.country!)")
                    let labl = LocationLabel(cp, par:self)
                    self.addChildNode(labl)
                    //labl.simdPosition += self.simdPosition*0.1
                }
            }
        }
        */
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func lookUpLocation(completionHandler: @escaping (CLPlacemark?)
                    -> Void ) {
        // Use the last reported location.
        if let lastLocation = self.pos {
            let geocoder = CLGeocoder()
                
            // Look up the location and pass it to the completion handler
            geocoder.reverseGeocodeLocation(lastLocation,
                        completionHandler: { (placemarks, error) in
                if error == nil {
                    let firstLocation = placemarks?[0]
                    completionHandler(firstLocation)
                }
                else {
                 // An error occurred during geocoding.
                    completionHandler(nil)
                }
            })
        }
        else {
            // No location was available.
            completionHandler(nil)
        }
    }
}
