//
//  locSpot.swift
//  JSONParserTest
//
//  Created by Niclas Jonasson on 2019-09-17.
//  Copyright © 2019 Niclas Jonasson. All rights reserved.
//

import Foundation

struct LocSpot : Decodable {
    let coord: String
    let label : String
    let spotType : Int
    let flag : Flag
}

struct Flag : Decodable {
    let flag : Int
    let text : String
}


let json = "[{\"coord\": \"59.309848,18.081328\",\"label\": \"Stockholm\",\"spotType\": \"0\",\"flag\": {\"flag\": 0, \"text\":\"\"}},{\"coord\": \"51.924419,4.477733\",\"label\": \"Rotterdamm Harbour\",\"spotType\": \"1\",\"flag\": {\"flag\": 0, \"text\":\"\"}},{\"coord\": \"1.248652,104.015781\",\"label\": \"Singapore\",\"spotType\": \"1\",\"flag\": {\"flag\": 0, \"text\":\"\"}},{\"coord\": \"22.601021,113.814851\",\"label\": \"Foxconn\",\"spotType\": \"2\",\"flag\": {\"flag\": 0, \"text\":\"\"}}]";
/*
{
    \"coord\": \"25.486670,110.570637\",
    \"label\": \"Firma X\",
    \"spotType\": \"2\",
    \"flag\": {\"flag\": 2, \"text\":\"Child labour\"}
    },
{
    \"coord\": \"1.248652,104.015781\",
    \"label\": \"Singapore\",
    \"spotType\": \"1\",
    \"flag\": {\"flag\": 0, \"text\":\"\"}
    },
{
    \"coord\": \"29.789856,31.006344\",
    \"label\": \"Durban\",
    \"spotType\": \"1\",
    \"flag\": {\"flag\": 0, \"text\":\"\"}
    },
{
    \"coord\": \"-26.610323,27.947735\",
    \"label\": \"Pretoria\",
    \"spotType\": \"3\",
    \"flag\": {\"flag\": 1, \"text\":\"Known to use materials\"}
    },
{
    \"coord\": \"-1.820120,18.357826\",
    \"label\": \"Mine\",
    \"spotType\": \"4\",
    \"flag\": {\"flag\": 0, \"text\":\"\"}
    }
]"
*/
