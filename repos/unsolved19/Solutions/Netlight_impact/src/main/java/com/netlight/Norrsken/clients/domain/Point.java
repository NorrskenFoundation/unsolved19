package com.netlight.Norrsken.clients.domain;

import lombok.Data;

@Data
public class Point {
    final String type;
    final Geometry geometry;
    final Properties properties;
}
