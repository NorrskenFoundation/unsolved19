//
//  RawmatSample.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-17.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit

class RawmatSample:SCNNode {
    init(mat:MaterialTypes, radii:CGFloat=0.05) {
        super.init()
        
        self.geometry = SCNSphere(radius: radii)
        //-- Material handle
        self.geometry?.firstMaterial = pbrMaterials.get(type: mat)
        
        self.simdPosition.y += Float(radii*0.5)
        
        
    }
    
    init(matString:String, radii:CGFloat=0.05) {
        super.init()
        
        self.geometry = SCNSphere(radius: radii)
        //-- Material handle
        self.geometry?.firstMaterial = pbrMaterialList[matString]
        
        self.simdPosition.y += Float(radii*0.5)
        
        
    }
    
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
