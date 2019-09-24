//
//  pbrMaterials.swift
//  BlockBuildAR
//
//  Created by Marcus Gårdman on 2018-04-12.
//  Copyright © 2018 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit


public enum MaterialTypes {
    case empty
    case occluder
    case bamboo
    case rusty
    case plaster
    case metal
    case brick
    case secondpass
}

class pbrMaterials {
    
    static func get(type:MaterialTypes) -> SCNMaterial {
        
        switch type {
        case .bamboo:
            return pbrMaterials.bamboo()
        case .occluder:
            return pbrMaterials.occluder()
        case .secondpass:
            return pbrMaterials.lightReciver()
        case .rusty:
            return pbrMaterials.rusty()
        case .metal:
            return pbrMaterials.metal()
        case .plaster:
            return pbrMaterials.plaster()
        case .brick:
            return pbrMaterials.brick()
        default:
            return pbrMaterials.empty()
        }
        
    }
    
    static private func empty() -> SCNMaterial {
        let pbr = SCNMaterial()
        pbr.lightingModel = .physicallyBased;
        
        return pbr
    }
    
    static private func occluder() -> SCNMaterial {
        let pbr = SCNMaterial()
        pbr.lightingModel = .physicallyBased
        pbr.writesToDepthBuffer = true;
        pbr.colorBufferWriteMask = SCNColorMask(rawValue: 0)
        return pbr
    }
    
    static private func lightReciver() -> SCNMaterial {
        let pbr = SCNMaterial()
        pbr.lightingModel = .physicallyBased
        pbr.diffuse.contents = UIColor.white
        
        pbr.blendMode = .multiply
        return pbr
    }
    
    
    static private func brick() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "brick/blocksrough")
        
        return pbr
    }
    
    static private func bamboo() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "bamboo/bamboo-wood-semigloss")
        
        
        //pbr.roughness.contents = UIColor.gray
        //pbr.metalness.contents = UIColor.gray
        return pbr
    }
    
    static private func plaster() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "plaster/Plaster17", suffix: "jpg")
        
        
        //pbr.roughness.contents = UIColor.gray
        //pbr.metalness.contents = UIColor.gray
        return pbr
    }
    
    static private func metal() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "titan/Titanium-Scuffed")
        
        
        pbr.roughness.contents = UIColor.black //white = blurry, black=clear
        pbr.metalness.contents = UIColor.white //white=full reflection, black=no reflection
        //pbr.normal.contents = pbrMaterials.getTexOrColor(named: "titan/normal_map.jpg")
        
        return pbr
    }
    
    static private func gold() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "gold/gold-Scuffed")
        
        
        pbr.roughness.contents = UIColor.black //white = blurry, black=clear
        pbr.metalness.contents = UIColor.white //white=full reflection, black=no reflection
        //pbr.normal.contents = pbrMaterials.getTexOrColor(named: "titan/normal_map.jpg")
        
        return pbr
    }
    
    static private func rusty() -> SCNMaterial {
        let pbr = pbrMaterials.getDefaultPbr(textureId: "rusty/rustediron2")
        
        
        pbr.roughness.contents = UIColor(red: 0.1, green: 0.1, blue: 0.1, alpha:1)
        pbr.metalness.contents = pbrMaterials.getTexOrColor(named: "rusty/rustediron2-metal.png")
        return pbr
    }
    
    static private func getDefaultPbr(textureId:String, suffix:String="png")->SCNMaterial {
        
        let pbr = pbrMaterials.empty()
        
        pbr.diffuse.contents = pbrMaterials.getTexOrColor(named: "\(textureId)-albedo.\(suffix)")
        pbr.normal.contents = pbrMaterials.getTexOrColor(named: "\(textureId)-normal.\(suffix)")
        pbr.ambientOcclusion.contents = pbrMaterials.getTexOrColor(named: "\(textureId)-ao.\(suffix)")
        pbr.roughness.contents = pbrMaterials.getTexOrColor(named: "\(textureId)-roughness.\(suffix)")
        pbr.metalness.contents = pbrMaterials.getTexOrColor(named: "\(textureId)-metal.\(suffix)")
        return pbr;
    }
    
    static public func getTexOrColor(named:String, color:UIColor=UIColor.black)->Any {
        
        let fullname = "art.scnassets/textures/pbr/\(named)"
        
        
        print("looking for file: \(fullname)")
        //return UIImage(named:"art.scnassets/textures/\(named)") ?? color
        var surface:Any
        if let tex = UIImage(named: fullname) {
            print("Found it!")
            surface = tex
        } else {
            print("Nope, no luck...")
            surface = color
        }
        return surface
    }
}
