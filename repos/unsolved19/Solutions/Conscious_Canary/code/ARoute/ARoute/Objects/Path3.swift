//
//  Path3.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-17.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import Foundation
import SceneKit

infix operator =?: AssignmentPrecedence //assign only if nonnil
func =?<T>(lhs:inout T,rhs:T?) { lhs = (rhs ?? lhs) }

public class Path3 {
    internal var points: [SCNVector3] = []
    
    public convenience init() {
        self.init(startingPoint:SCNVector3Zero)
    }
    
    public init(startingPoint:SCNVector3) {
        self.points.append(startingPoint)
    }
    
    public func continuePath(from point:SCNVector3) -> SCNNode? {
        let lastPoint = points.last!
        let geo = makeRect(startPoint: lastPoint, endPoint: point)
        geo.firstMaterial!.isDoubleSided = true
        
        points.append(point)
        return SCNNode(geometry:geo)
    }
    
    public static func path(points: [SCNVector3], color: UIColor?, width: Float?) -> [SCNNode] {
        let path = Path3(startingPoint: points[0])
        path.color =? color
        path.width =? width
        var restOfPoints = points; restOfPoints.removeFirst();
        var results: [SCNNode] = []
        for point in restOfPoints {
            results.append(path.continuePath(from: point)!)
        }
        return results
    }
    
    public var width: Float = 0.00015
    public var color = UIColor.white
    
    private func makeRect(startPoint:SCNVector3,endPoint:SCNVector3) -> SCNGeometry {
        let firstPoint = SCNVector3Make(startPoint.x, startPoint.y, startPoint.z + width)
        let secondPoint = SCNVector3Make(startPoint.x, startPoint.y, startPoint.z - width)
        let thirdPoint = SCNVector3Make(endPoint.x, endPoint.y, endPoint.z + width)
        let fourthPoint = SCNVector3Make(endPoint.x, endPoint.y, endPoint.z - width)
        let points = [firstPoint,secondPoint,thirdPoint,fourthPoint]
        
        let indices: [UInt16] = [
            1,0,2,
            1,2,3,
            ]
        let geoSource = SCNGeometrySource(vertices: points)
        let geoElement = SCNGeometryElement(indices: indices, primitiveType: .triangles)
        
        let geo = SCNGeometry(sources: [geoSource], elements: [geoElement])
        geo.firstMaterial?.diffuse.contents = self.color
        return geo
    }
    
}

