//
//  LocationLabel.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-16.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit

class LocationLabel:SCNNode {
    var mat:SCNMaterial!
    var txtNode:SCNNode!
    
    init(_ textStr:String="Hello World", par:SCNNode) {
        super.init()

        self.txtNode = SCNNode()
        self.addChildNode(self.txtNode)

        print("Create label: \(textStr)")
        
        let labl3d:SCNText = SCNText(string: textStr, extrusionDepth: 0.1)
        //labl3d.font = UIFont (name: "Arial", size: 12)
        labl3d.alignmentMode = CATextLayerAlignmentMode.center.rawValue
        labl3d.font = UIFont.systemFont(ofSize: 1)
        
        self.txtNode.geometry = labl3d

        //Pivot positionfor centering
       
        let bb = self.txtNode.boundingBox
        self.txtNode.pivot = SCNMatrix4MakeTranslation((bb.max.x-bb.min.x)/2, bb.max.y/2, 0)
        
        
        self.txtNode.scale = SCNVector3Make(0.002, 0.002, 0.002)
        
        //-- Material handle
        self.mat = self.txtNode.geometry?.firstMaterial
        
        //-- Material config
        self.mat.lightingModel = .constant
        
        self.mat.diffuse.contents = UIColor.white
        self.mat.emission.contents = UIColor.white

        //let camLook:SCNLookAtConstraint = SCNLookAtConstraint(target: GlobalVars.view?.pointOfView)
        
        let camLook:SCNBillboardConstraint = SCNBillboardConstraint()
        camLook.freeAxes = SCNBillboardAxis.Y
        //camLook.localFront = SCNVector3(0,0,1)
        self.txtNode.constraints = [camLook]
        
       // let line = self.lineBetweenNodeA(nodeApos: self.position , nodeBpos: SCNVector3Zero)
       // self.addChildNode(line)
        
        //self.simdWorldPosition = par.simdWorldPosition// + par.simdPosition*0.01
        let offset:Float = 0.05
        self.position = par.worldPosition * offset
        
        let points: [SCNVector3] = [SCNVector3Zero, par.worldPosition * -offset]

        let path = Path3()

        //let camLook2:SCNBillboardConstraint = SCNBillboardConstraint()
        
        //camLook2.freeAxes = SCNBillboardAxis.Y
       // camLook2.localFront = SCNVector3(0,1,0)
        var nodes: [SCNNode] = []
        for point in points {
            let n = path.continuePath(from: point)!
            nodes.append(n)
        }

        for node in nodes { self.addChildNode(node) }
        
        
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    
    func lineBetweenNodeA(nodeApos: SCNVector3, nodeBpos: SCNVector3) -> SCNNode {
        let positions: [Float32] = [nodeApos.x, nodeApos.y, nodeApos.z, nodeBpos.x, nodeBpos.y, nodeBpos.z]
        let positionData = NSData(bytes: positions, length: MemoryLayout<Float32>.size*positions.count)
        let indices: [Int32] = [0, 1]
        let indexData = NSData(bytes: indices, length: MemoryLayout<Int32>.size * indices.count)

        let source = SCNGeometrySource(data: positionData as Data, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: indices.count, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: MemoryLayout<Float32>.size * 3)
        let element = SCNGeometryElement(data: indexData as Data, primitiveType: SCNGeometryPrimitiveType.line, primitiveCount: indices.count, bytesPerIndex: MemoryLayout<Int32>.size)

        let line = SCNGeometry(sources: [source], elements: [element])
        return SCNNode(geometry: line)
    }
    
}

