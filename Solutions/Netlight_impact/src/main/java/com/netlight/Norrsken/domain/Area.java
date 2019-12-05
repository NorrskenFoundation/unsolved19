package com.netlight.Norrsken.domain;

import lombok.Data;

@Data
public class Area {
  final Point upperLeft;
  final Point downRight;

  public Area(Point upperLeft, Point downRight) {
    this.upperLeft = upperLeft;
    this.downRight = downRight;
  }

  final boolean surrounds(Point b) {

    double lat = b.getLatitude();
    double lon = b.getLongitude();
    boolean latWithin = lat >= downRight.getLatitude() && lat <= upperLeft.getLatitude();
    boolean lonWithin = lon >= upperLeft.getLongitude() && lon <= downRight.getLongitude();
    boolean result = latWithin && lonWithin;
    System.out.println(
        String.format(
            "Result: %b, Compare p: %s, with area: '%s, %s'", result, b, upperLeft, downRight));
    return result;
  }
}
