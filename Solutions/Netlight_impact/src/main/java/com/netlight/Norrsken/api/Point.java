package com.netlight.Norrsken.api;

import lombok.AllArgsConstructor;
import lombok.Data;

@AllArgsConstructor
@Data
public class Point {
    final double longitude;
    final double latitude;
    final double intensity;
}
