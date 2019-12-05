package com.netlight.Norrsken.domain;

import lombok.AllArgsConstructor;
import lombok.Data;

@AllArgsConstructor
@Data
public class AlarmDefinition {
  final String callbackUrl;
  final Trigger trigger;
}
