package com.netlight.Norrsken.domain;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.ToString;

@ToString
@Data
@AllArgsConstructor
public class Point {
  final double latitude;
  final double longitude;
}
