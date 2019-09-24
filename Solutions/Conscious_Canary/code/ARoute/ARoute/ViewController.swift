//
//  ViewController.swift
//  ARoute
//
//  Created by Marcus Gårdman on 2019-09-16.
//  Copyright © 2019 Marcus Gårdman. All rights reserved.
//

import UIKit
import SceneKit
import ARKit

struct GlobalVars {
    static var scene:SCNScene?
    static var cameraNode:SCNNode?
    static var camera:SCNCamera?
    static var view:ARSCNView?
}

var pbrMaterialList:[String:SCNMaterial] = [String:SCNMaterial]()

class ViewController: UIViewController, ARSCNViewDelegate, ARSessionDelegate {

    private var lookForQr:Bool = true
    private var experience:SCNNode?
    private var scene:SCNScene!
    
    @IBOutlet var sceneView: ARSCNView!
    /*
    let updateQueue = DispatchQueue(label: Bundle.main.bundleIdentifier! +
        ".serialSceneKitQueue")
    
    /// Convenience accessor for the session owned by ARSCNView.
    var session: ARSession {
        return sceneView.session
    }*/
    
    var screenCenter: CGPoint {
        let bounds = sceneView.bounds
        return CGPoint(x: bounds.midX, y: bounds.midY)
    }
    
    override var preferredStatusBarStyle : UIStatusBarStyle {
        return UIStatusBarStyle.lightContent
        //return UIStatusBarStyle.default   // Make dark again
    }
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        GlobalVars.view = sceneView
        
        // Set the view's delegate
        sceneView.delegate = self
        
        // Show statistics such as fps and timing information
        sceneView.showsStatistics = true
        
        // Create a new scene
        self.scene = SCNScene(named: "art.scnassets/sky.scn")!
        
        LoadMaterials()
        
        //print(pbrMaterialList)
        /*
        let globe = EarthNode()
        scene.rootNode.addChildNode(globe)
        
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
        
        
        
        let bez = BezierPath()
        bez.position.y=0.1
        scene.rootNode.addChildNode(bez)
        */
        scene.isPaused = false
        
        
        sceneView.session.delegate = self
        
        
        //self.qrScanner = ARKitQRReader()
       
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(handleTap(rec:)))

        //Add recognizer to sceneview
        sceneView.addGestureRecognizer(tap)
        
        
        // Set the scene to the view
        sceneView.scene = scene
    }
    
    func LoadMaterials() {
        
            pbrMaterialList = [String:SCNMaterial]()
            
            let otherScene:SCNScene = SCNScene(named: "art.scnassets/material_test.scn")!
        
            if let pbrNode = otherScene.rootNode.childNode(withName: "pbr", recursively: true) {

                pbrNode.childNodes.forEach({
                    let mat:SCNMaterial = ($0.geometry?.firstMaterial)!
                    let name = mat.name
                    print(name!)
                    pbrMaterialList[name!] = mat
                    //pbrMaterialList.append(($0.geometry?.firstMaterial)!)
                    
                    $0.removeFromParentNode()
                })
            }
            
            if(pbrMaterialList.count == 0 ) {
                let _m = SCNMaterial.material(withDiffuse: UIColor.purple)
                _m.lightingModel = .physicallyBased
                pbrMaterialList["default"] = _m //.append(_m)
            }
        }
    
    
    @objc func handleTap(rec: UITapGestureRecognizer){
        
           DispatchQueue.main.async {
             /*  let cam = self.sceneView.pointOfView!
               let results = self.PhysicsRayCast(origin: cam.worldPosition, direction: cam.worldFront)
               //let prc:[SCNHitTestResult]? = self.PhysicsRayCast(origin: SCNVector3(0,1,0), direction: SCNVector3(0,-1,0))
               if let hit = results.first {
                   //self.ARView.scene.rootNode.addChildNode(self.visualizeSpot(hit.worldCoordinates))
                   //self.ARView.scene.rootNode.addChildNode(self.visualizeRay(hit.worldCoordinates, hit.worldNormal))
                let GLOBE_RADIUS:Float = 0.1
                   var realpos = hit.worldCoordinates + hit.worldNormal.normalized() * GLOBE_RADIUS
                   if(hit.node.name?.starts(with: "Cube-"))! {
                       realpos = hit.node.presentation.worldPosition + hit.localNormal.normalized() * GLOBE_RADIUS
                   }
                   //self.spawnCube(realpos, hit.node)
                    print("create globe at: \(realpos)")
               } else {
                   print(" hit nothing")
               }*/
            
            let touchPoint:CGPoint = self.screenCenter //rec.location(in: self.sceneView) //
            
            //let query:raycastQuery = self.sceneView.raycastQuery(from: <#T##CGPoint#>, allowing: <#T##ARRaycastQuery.Target#>, alignment: <#T##ARRaycastQuery.TargetAlignment#>)
            
            if let rcq = self.sceneView.raycastQuery(from: touchPoint, allowing: .estimatedPlane, alignment: .any) {
                
               
                // Perform the raycast
                let raycast = self.sceneView.session.trackedRaycast(rcq) { results in
                    // Refine object position with raycast update
                    if let result = results.first {
                        let trans = result.worldTransform
                        
                        let pos = SCNVector3(trans.columns.3.x,trans.columns.3.y, trans.columns.3.z);
                        print("Place at: \(pos)")
                        if(self.experience == nil) {
                            self.experience = GlobeExperience() //EarthNode()
                            self.scene.rootNode.addChildNode(self.experience!)
                        }
                        //self.worldGlobe?.position = pos; //
                        self.experience?.simdWorldTransform = trans
                        //self.worldGlobe?.simdPosition.y += 0.1
                        
                    }
                }
                // Stop tracking the raycast
                raycast?.stopTracking()
                
                
                
            }
           }
    }
    
    func PhysicsRayCast(origin:SCNVector3, direction:SCNVector3, maxDistance:Float = -1, layerMask:Int=1)->[SCNHitTestResult]
    {
 
        var mx = maxDistance
        if(maxDistance <= 0) {
            mx = Float(self.sceneView.pointOfView?.camera?.zFar ?? 1000)
        }
        
        let p0 = origin
        let p1 = origin + direction * mx
       // print("maxDistance:\(maxDistance)")
       // print("MaxFloat:\(Float.greatestFiniteMagnitude)")
        
        return self.sceneView.scene.physicsWorld.rayTestWithSegment(from: p0, to: p1, options: [.searchMode: SCNPhysicsWorld.TestSearchMode.closest]) //[SCNPhysicsWorld.TestOption.collisionBitMask :.all]
    }
    
    func setup3D() {
        let skycube = UIImage(named: "textures/office_sky3.jpg")
        sceneView.scene.lightingEnvironment.contents = skycube
        // ARView.scene.background.contents = skycube
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // Create a session configuration
/*
        let config = sceneView.session.configuration as? ARWorldTrackingConfiguration,
                   ARWorldTrackingConfiguration.supportsFrameSemantics(.personSegmentationWithDepth) else {
                       print("People occlusion is not supported on this device.")
                    }*/
                        
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        // Prevent the screen from being dimmed to avoid interuppting the AR experience.
        UIApplication.shared.isIdleTimerDisabled = true

        // Start the `ARSession`.
        let config = ARWorldTrackingConfiguration()
        
        config.planeDetection = [.horizontal, .vertical]
        
        config.environmentTexturing = .automatic
        
        config.wantsHDREnvironmentTextures = true
        
        config.isLightEstimationEnabled = true
        

        // Run the view's session
        sceneView.session.run(config, options: [.resetTracking, .removeExistingAnchors])
        
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        // Pause the view's session
        sceneView.session.pause()
    }

    
    
    
    // MARK: - ARSCNViewDelegate
    
/*
    // Override to create and configure nodes for anchors added to the view's session.
    func renderer(_ renderer: SCNSceneRenderer, nodeFor anchor: ARAnchor) -> SCNNode? {
        let node = SCNNode()
     
        return node
    }
*/
    

    
    func renderer(_ renderer: SCNSceneRenderer, updateAtTime time: TimeInterval) {
       // print(sceneView.pointOfView?.position)
    }
    
    func session(_ session: ARSession, didFailWithError error: Error) {
        // Present an error message to the user
        
    }
    
    func sessionWasInterrupted(_ session: ARSession) {
        // Inform the user that the session has been interrupted, for example, by presenting an overlay
        
    }
    
    func sessionInterruptionEnded(_ session: ARSession) {
        // Reset tracking and/or remove existing anchors if consistent tracking is required
        
    }
}


//TODO:
/*
 - 3D Position when qr code hit
 - Create globe at that position
 - show infographics of product behind globe
 - show material bars %
 - tap on materials
 - hilight path for specific material
 
 
 */
