//
//  GlobeExperience.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-17.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit
class GlobeExperience:SCNNode {
    var showSpots:[LocationSpot]=[]
    var globe:SCNNode!
    
    override init() {
        super.init()
        self.addObjects()
    }
    
    func addObjects() {
        self.globe = EarthNode()
        self.globe.simdPosition.y += 0.1
        self.addChildNode(globe)

        let shadowGeo = SCNPlane(width: 0.3, height: 0.3)
        let shadow = SCNNode(geometry: shadowGeo)
        if let mat:SCNMaterial = shadow.geometry?.firstMaterial {
            mat.lightingModel = .constant
            mat.diffuse.contents = UIImage(named:"art.scnassets/textures/shadow.png")
            //mat.emission.contents = UIColor.red
            mat.blendMode = .multiply
        }
        //shadow.geometry?.firstMaterial?.emission.contents = UIColor.red
        self.addChildNode(shadow)
        
        let sLook:SCNLookAtConstraint = SCNLookAtConstraint(target: globe)
        sLook.localFront = SCNVector3(0,0,1)
        shadow.constraints = [sLook]
        
        
        self.showMapSpots(usecobolt: true)
        
        showMaterials()
        
        
        /*
        let sthlm = LocationSpot(lat:59.3293, lon: 18.0686, label:"Stockholm")
        globe.addChildNode(sthlm)
        


        let london = LocationSpot(lat:51.5074, lon: 0.1278, label:"London")
        globe.addChildNode(london)

        let paris = LocationSpot(lat:48.8566, lon: 2.3522, label:"Paris")
        globe.addChildNode(paris)


        let ny = LocationSpot(lat:40.703931, lon: -73.917825, label:"New York")
        globe.addChildNode(ny)


        let rom = LocationSpot(lat:41.895633, lon: 12.496143, label:"Rome")
        globe.addChildNode(rom)

        let mbuji = LocationSpot(lat:-6.123517, lon: 23.595288, label:"Mbuji")
        globe.addChildNode(mbuji)


        let ponte = LocationSpot(lat:-4.794295, lon:11.861928, label:"Ponte")
        globe.addChildNode(ponte)
*/


        let bez = BezierPath()
        bez.position.y=0.1
        self.addChildNode(bez)
        
        
    }
    
    func showMaterials() {
        
        
        let mats=["Gold","Copper","Clay","Plastic", "Rusty"]
        
        var i:Int = 0
        let radii:Float = 0.15
        for m in mats {
            let mat = RawmatSample(matString: m, radii:0.02)
            self.addChildNode(mat)
            let ang = Float(i) * Float.pi*0.5 / Float(mats.count)
            mat.simdPosition.x = sin(ang) * radii
            mat.simdPosition.z = cos(ang) * radii
            mat.simdPosition.y = 0.025
            i = i + 1
            
        }
        /*
        Stone
        Copper
        Gold
        Clay
        Denim
        Plastic
        */
      
    }
    
    func showMapSpots(usecobolt:Bool=true) {
        
        for s in showSpots {
            s.removeFromParentNode()
        }
        
        showSpots.removeAll()
        
        let jp = Parser()
        if let spots = jp.testParse(mat_cobolt: usecobolt) {
            for spot in spots {
                let l = LocationSpot(place:spot)
                self.globe.addChildNode(l)
                showSpots.append(l)
            }
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
