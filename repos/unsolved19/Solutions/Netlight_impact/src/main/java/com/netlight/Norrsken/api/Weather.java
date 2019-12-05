package com.netlight.Norrsken.api;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.List;

@AllArgsConstructor
@Data
public class Weather {
    List<Point> points;
}
