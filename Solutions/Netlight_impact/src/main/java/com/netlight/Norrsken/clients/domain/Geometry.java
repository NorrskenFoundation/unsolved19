package com.netlight.Norrsken.clients.domain;

import lombok.Data;

@Data
public class Geometry {
  final String type;
  final double[] coordinates;
}
