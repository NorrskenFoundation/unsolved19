//
//  BezierPath.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-17.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit

class BezierPath:SCNNode {
    override init() {
        super.init()

        // Material colors
       let path = UIBezierPath()
        path.move(to:CGPoint())
        path.addQuadCurve(to: CGPoint(x: 10, y: 0), controlPoint: CGPoint(x: 5, y: 20))
        path.addLine(to:CGPoint(x: 9.9, y: 0))
        path.addQuadCurve(to:CGPoint(x: 0.1, y: 0), controlPoint: CGPoint(x: 5, y: 19.8))
        
        let shape = SCNShape(path: path, extrusionDepth: 1)
        
        shape.firstMaterial?.diffuse.contents = UIColor.blue
        let shapeNode = SCNNode(geometry: shape)
        shapeNode.pivot = SCNMatrix4MakeTranslation(5, 0, 0)
        shapeNode.eulerAngles.y = Float(-Double.pi/4)
        
        shapeNode.scale = SCNVector3(0.01,0.01,0.01)
        
        self.addChildNode(shapeNode)
        
        let modifier = "uniform float progress;\n #pragma transparent\n vec4 mPos = u_inverseModelViewTransform * vec4(_surface.position, 1.0);\n _surface.transparent.a = clamp(1.0 - ((mPos.x + 50.0) - progress * 200.0) / 50.0, 0.0, 1.0);"
        shape.shaderModifiers = [ SCNShaderModifierEntryPoint.surface: modifier ]
        shape.setValue(0.0, forKey: "progress")

        SCNTransaction.begin()
        SCNTransaction.animationDuration = 10
        shape.setValue(1.0, forKey: "progress")
        SCNTransaction.commit()
        
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
