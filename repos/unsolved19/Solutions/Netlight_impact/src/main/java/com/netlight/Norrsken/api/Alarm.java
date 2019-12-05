package com.netlight.Norrsken.api;

import com.netlight.Norrsken.clients.domain.Point;
import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Alarm {
  final String description;
  final Point point;
}
