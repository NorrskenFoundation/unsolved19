package com.netlight.Norrsken.clients.domain;

import lombok.Data;
import lombok.ToString;

import java.util.List;

@ToString
@Data
public class EricssonWeatherData {
    final String descirption;
    final List<Point> points;
    final String canvas;
}
