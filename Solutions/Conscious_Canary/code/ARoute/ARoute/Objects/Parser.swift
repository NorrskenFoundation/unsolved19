//
//  Parser.swift
//  JSONParserTest
//
//  Created by Niclas Jonasson on 2019-09-17.
//  Copyright © 2019 Niclas Jonasson. All rights reserved.
//

import Foundation

class Parser : NSObject {
    override init() {
        
    }

    
    func testParse(mat_cobolt:Bool)->[LocSpot]? {
        
        if(mat_cobolt) {
            do {
            let test = try JSONDecoder().decode([LocSpot].self, from: cobolt)
                print(test);
                return test }
            catch {
                print("Det gick åt helvete");
                print(error);
                return nil
            }
        } else {
        
            do {
            let test = try JSONDecoder().decode([LocSpot].self, from: tantalum)
                print(test);
                return test }
            catch {
                print("Det gick åt helvete");
                print(error);
                return nil
            }
            
        }
        
        
    }
    
    
    
    
    
    let cobolt = """
    [
    {
        "coord": "59.309848,18.081328",
        "label": "Stockholm",
        "spotType": 0,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "51.924419,4.477733",
        "label": "Rotterdamm Harbour",
        "spotType": 1,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "1.248652,104.015781",
        "label": "Singapore",
        "spotType": 1,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "22.601021,113.814851",
        "label": "Foxconn",
        "spotType": 2,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "25.486670,110.570637",
        "label": "Firma X",
        "spotType": 2,
        "flag": {"flag": 2, "text":"Child labour"}
    },
    {
        "coord": "1.248652,104.015781",
        "label": "Singapore",
        "spotType": 1,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "-29.789856,31.006344",
        "label": "Durban",
        "spotType": 1,
        "flag": {"flag": 0, "text":""}
    },
    {
        "coord": "-26.610323,27.947735",
        "label": "Pretoria",
        "spotType": 3,
        "flag": {"flag": 1, "text":"Known to use materials"}
    },
    {
        "coord": "-1.820120,18.357826",
        "label": "Mine",
        "spotType": 4,
        "flag": {"flag": 0, "text":""}
    }
    ]
    """.data(using: .utf8)!;
    
    
    let tantalum = """
    [
       {
           “coord”: “59.309848,18.081328",
           “label”: “Stockholm”,
           “spotType”: 0,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “51.924419,4.477733”,
           “label”: “Rotterdamm Harbour”,
           “spotType”: 1,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “1.248652,104.015781",
           “label”: “Singapore”,
           “spotType”: 1,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “22.601021,113.814851”,
           “label”: “Foxconn”,
           “spotType”: 2,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “35.966170,140.021003",
           “label”: “Firma X”,
           “spotType”: 2,
           “flag”: {“flag”: 2, “text”:“Child labour”}
       },
       {
           “coord”: “31.304061,121.630893”,
           “label”: “Shanghai”,
           “spotType”: 1,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “54.942921,59.881178",
           “label”: “Processor”,
           “spotType”: 3,
           “flag”: {“flag”: 0, “text”:“”}
       },
       {
           “coord”: “-9.987786,38.741244”,
           “label”: “Tanzania harbour”,
           “spotType”: 1,
           “flag”: {“flag”: 2, “text”:“Unknown source of minerals”}
       }
    ]
    """.data(using: .utf8)!
}
