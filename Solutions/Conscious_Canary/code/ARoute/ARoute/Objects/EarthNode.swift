//
//  EarthNode.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-16.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit

class EarthNode:SCNNode {
    var mat:SCNMaterial!
    
    override init() {
        super.init()
        
        self.geometry = SCNSphere(radius: 0.1)
        //-- Material handle
        self.mat = self.geometry?.firstMaterial
        
        //-- Material config
        self.mat.lightingModel = .physicallyBased
        self.mat.diffuse.contents = UIImage(named:"art.scnassets/textures/earth/earthmap4k.jpg")
        self.mat.emission.contents = UIImage(named:"art.scnassets/textures/earth/emission.jpg")
        self.mat.emission.intensity = 0.1
        self.mat.normal.contents = UIImage(named:"art.scnassets/textures/earth/normal.png")
        self.mat.specular.contents = UIImage(named:"art.scnassets/textures/earth/specular.jpg")
        
        self.mat.clearCoat.contents = UIImage(named:"art.scnassets/textures/earth/earthcloudmap.png")
        self.mat.clearCoat.wrapS = SCNWrapMode.repeat
        self.mat.clearCoat.wrapT = SCNWrapMode.mirror
        
        let cloudAni = CABasicAnimation(keyPath: "contentsTransform")

        cloudAni.duration = 360;
        cloudAni.fromValue = CATransform3DConcat(CATransform3DMakeTranslation(0, 0, 0), CATransform3DMakeScale(1,1,1))
        cloudAni.toValue   = CATransform3DConcat(CATransform3DMakeTranslation(CGFloat(360*Double.pi/180), 0, 0), CATransform3DMakeScale(1,1,1))
        cloudAni.repeatCount = .greatestFiniteMagnitude //FLT_MAX;
        
        self.mat.clearCoat.addAnimation(cloudAni, forKey: "earthcloudmap")

        
        //self.addRotationAction()
        
    }
    
    func addRotationAction() {
        let rot = SCNAction.rotateBy(x: 0, y: CGFloat(360*Double.pi/180), z: 0, duration: 80) //SCNAction.rotate(by: CGFloat(360*Double.pi/180), around: SCNVector(0,1,0), duration:8)
        
        let repeatAction = SCNAction.repeatForever(rot)
        
        self.runAction(repeatAction)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
